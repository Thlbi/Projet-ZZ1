#include <SDL2/SDL_image.h>
#include<stdio.h>
                    

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface* my_image = NULL;
    SDL_Texture* my_texture = NULL;
    SDL_Texture* bg_texture = NULL;
    my_image = IMG_Load(file_image_name);
    
    //if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer,my_texture,bg_texture);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    //if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer,my_texture,bg_texture);

    return my_texture;
  }

/*
void play_with_texture_(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
			   SDL_Texture *my_texture2,
                           SDL_Window *window,
                           SDL_Renderer *renderer
			   ) {
  SDL_Rect
    source = {0},                  // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},      // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};            // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,      // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

  float zoom = 1;                // facteur de zoom
  int offset_x = source.w / 2,   // La largeur d'une vignette de l'image
      offset_y = source.h / 4;   // La hauteur d'une vignette de l'image
  SDL_Rect state[400];           // Tableau qui stocke les vignettes dans le bon ordre pour l'animation
*/
  /* construction des différents rectangles autour de chacune des vignettes de la planche */
  /*int i = 0;
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
  
  SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}
*/


void play_with_texture_vaisseau(SDL_Texture * texture_vaisseau,
                           SDL_Window *window,
                           SDL_Renderer *renderer,
			   int position_x)
{
	SDL_Rect 
       	   source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(texture_vaisseau, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 0.5;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x = window_dimensions.w - source.w * zoom ;     // La destination est au milieu de la largeur de la fenêtre
     destination.y = window_dimensions.h-source.h * zoom;

     SDL_RenderCopy(renderer, texture_vaisseau,     // Préparation de l'affichage  
                    &source,
                    &destination);            
     SDL_RenderPresent(renderer);             
     SDL_Delay(1000);                         

     SDL_RenderClear(renderer);               // Effacer la fenêtre
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture_meteore = NULL;
    SDL_Texture* texture_meteore2 = NULL;
    SDL_Texture* texture_meteore3 = NULL;
    SDL_Texture* texture_vaisseau = NULL;
    SDL_Texture* texture_vaisseau2 = NULL;
    SDL_Texture* texture_vaisseau3 = NULL;
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


  texture_meteore = load_texture_from_image("buttons.png",window,renderer);
  texture_meteore2 = load_texture_from_image("buttons.png",window,renderer);
  texture_meteore3 = load_texture_from_image("buttons.png",window,renderer);
  texture_vaisseau = load_texture_from_image("redfighter0001.png",window,renderer);
  texture_vaisseau2 = load_texture_from_image("redfighter0005.png",window,renderer);
  texture_vaisseau3 = load_texture_from_image("redfighter0009.png",window,renderer);
  bg_texture = load_texture_from_image("'Nebula Aqua-Pink.png'",window,renderer);


  //play_with_texture_(texture_meteore,texture_meteore2,texture_meteore3,texture_vaisseau,texture_vaisseau2,texture_vaisseau3,bg_texture,window,renderer);
  play_with_texture_vaisseau(texture_vaisseau,window,renderer,10);

  IMG_Quit();
  return EXIT_SUCCESS;
}


