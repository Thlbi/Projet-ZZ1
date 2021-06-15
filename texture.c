#include <SDL2/SDL_image.h>
                           
void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer,SDL_Texture* my_texture,SDL_Texture* bg_texture) 
{
  char msg_formated[255];
  int l;

  if (!ok) {
         strncpy(msg_formated, msg, 250);
         l = strlen(msg_formated);
         strcpy(msg_formated + l, " : %s\n");

         SDL_Log(msg_formated, SDL_GetError());
  }

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                           
  if (window != NULL)   SDL_DestroyWindow(window);                               
  SDL_Quit();

  if (my_texture!=NULL) SDL_DestroyTexture(my_texture);
  if (bg_texture!=NULL) SDL_DestroyTexture(bg_texture);

  if (!ok) {
         exit(EXIT_FAILURE);
  }
}


SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface* my_image = NULL;
    SDL_Texture* my_texture = NULL;
    SDL_Texture* bg_texture = NULL;
    my_image = IMG_Load(file_image_name);
    
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer,my_texture,bg_texture);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer,my_texture,bg_texture);

    return my_texture;
  }


void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur,my_texture,bg_texture
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  SDL_RenderPresent(renderer);                  // Affichage
  SDL_Delay(2000);                              // Pause en ms

  SDL_RenderClear(renderer);                    // Effacer la fenêtre
}


void play_with_texture_2(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) 
{
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 1.5;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h*zoom;         // La destination est un zoom de la source
     destination.x =
       (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
     destination.y =
         (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
     SDL_RenderPresent(renderer);             
     SDL_Delay(1000);                         

     SDL_RenderClear(renderer);               // Effacer la fenêtre
}


void play_with_texture_3(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) {
  SDL_Rect
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w,
                   &source.h);                    // Récupération des dimensions de l'image

  /* On décide de déplacer dans la fenêtre         cette image */
  float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée

  int nb_it = 200;                                // Nombre d'images de l'animation
  destination.w = source.w * zoom;                // On applique le zoom sur la largeur
  destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
  destination.x =
      (window_dimensions.w - destination.w) / 2;  // On centre en largeur
  float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

  for (int i = 0; i < nb_it; ++i) {
    destination.y =
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                     (1 + cos(10.0 * i / nb_it * 2 *
                              M_PI)));            // hauteur en fonction du numéro d'image

    SDL_RenderClear(renderer);                    // Effacer l'image précédente

    SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
    SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
    SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
    SDL_Delay(30);                                // Pause en ms
  }
  SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}


void play_with_texture_4(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) {
       SDL_Rect
             source = {0},                    // Rectangle définissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
             destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
             state = {0};                     // Rectangle de la vignette en cours dans la planche

       SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

       /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 2;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           offset_y = source.h;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 ;                          // La première vignette est en début de ligne
       state.y = 0;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = offset_x;                    // Largeur de la vignette
       state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
       destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

       destination.y =                        // La course se fait en milieu d'écran (en vertical)
         (window_dimensions.h - destination.h) /2;

       int speed = 9;
       for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
         destination.x = x;                   // Position en x pour l'affichage du sprite
         state.x += offset_x;                 // On passe à la vignette suivante dans l'image
         state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne

         SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
         SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                        &state,
                        &destination);
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}


void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur,my_texture,bg_texture
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
}


void play_with_texture_5(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
  SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

  int nb_images = 40;                         //  Il y a 18 vignette dans la ligne qui nous intéresse
  int nb_images_animation =nb_images;    //
  float zoom = 2;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 4,                // La largeur d'une vignette de l'image
      offset_y = source.h / 5;                // La hauteur d'une vignette de l'image
  SDL_Rect state[40];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

  /* construction des différents rectangles autour de chacune des vignettes de la planche */
  int i = 0;
  for (int y = 0; y < source.h ; y += offset_y) {
    for (int x = 0; x < source.w; x += offset_x) {
      state[i].x = x;
      state[i].y = y;
      state[i].w = offset_x;
      state[i].h = offset_y;
      ++i;
    }
  }
  state[14] = state[13];                      // state[14 à 16] la même image, le monstre ne bouge pas
  state[15] = state[16];
  for(; i< nb_images_animation ; ++i){                  // reprise du début de l'animation en sens inverse
    state[i] = state[39-i];
  }

  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
  destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite
  i = 0;
  for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
    play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                          window, renderer);
    SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                   my_texture, &state[i], &destination);
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(100);            // Pause en ms
  }
  
  SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}


void play_with_texture_6(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
  SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

  int nb_images = 16;                         //  Il y a 18 vignette dans la ligne qui nous intéresse
  int nb_images_animation = nb_images;    //
  float zoom = 3;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 8,                // La largeur d'une vignette de l'image
      offset_y = source.h / 4;                // La hauteur d'une vignette de l'image
  SDL_Rect state[40];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

  /* construction des différents rectangles autour de chacune des vignettes de la planche */
  int i = 0;
  for (int y = 0; y < source.h ; y += offset_y) {
    for (int x = 0; x < source.w; x += offset_x) {
      state[i].x = x;
      state[i].y = 0;
      state[i].w = offset_x;
      state[i].h = offset_y;
      ++i;
    }
  }
  state[14] = state[13];                      // state[14 à 16] la même image, le monstre ne bouge pas
  state[15] = state[16];
  for(; i< nb_images_animation ; ++i){                  // reprise du début de l'animation en sens inverse
    state[i] = state[39-i];
  }

  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
  destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite
  i = 0;
  for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
    play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                          window, renderer);
    SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                   my_texture, &state[i], &destination);
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(100);            // Pause en ms
  }
  
  SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* my_texture = NULL;
    SDL_Texture* bg_texture = NULL;

    SDL_DisplayMode screen;


  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué
    exit(EXIT_FAILURE);
  }


  SDL_GetCurrentDisplayMode(0, &screen);


  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w*0.6 ,
                            screen.h *0.6 ,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer,my_texture,bg_texture);

  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer,my_texture,bg_texture);



  my_texture = load_texture_from_image("labyrinthe.gif",window,renderer);
  if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer,my_texture,bg_texture);

  bg_texture = load_texture_from_image("player-spritemap-v9.png",window,renderer);
  if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer,my_texture,bg_texture);

  //play_with_texture_1(my_texture,window,renderer);
  //play_with_texture_2(my_texture,window,renderer);
  //play_with_texture_3(my_texture,window,renderer);
  //play_with_texture_4(my_texture,window,renderer);
  //play_with_texture_5(my_texture,bg_texture,window,renderer);
  play_with_texture_6(my_texture,bg_texture,window,renderer);
  
  IMG_Quit();
  return EXIT_SUCCESS;
}


