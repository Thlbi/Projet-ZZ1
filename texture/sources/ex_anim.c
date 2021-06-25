
// Animation perso Juin 17 dernière modif


#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
// gcc ex_anim.c -o ex_anim -Wextra -Wall $(sdl2-config --cflags --libs) -lSDL2_image // pour la compilation 







void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer) {                           // renderer à fermer
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

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
} 
void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  // On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre 

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination); 
               
}



void play_with_texture(SDL_Texture *bg_texture,
                           SDL_Texture *my_texture,
                           SDL_Texture *my_texture2,
                           SDL_Texture *my_texture3,
                           SDL_Window *window,
                           SDL_Renderer *renderer) {
  SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer


    SDL_Rect
    source2 = {0},                             // Rectangle définissant la zone de la texture à récupérer
                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination2 = {0};

    SDL_Rect source3 = {0},  destination3 = {0};


  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h);


  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h); 

  SDL_QueryTexture(my_texture2, NULL, NULL, &source2.w,&source2.h);
  SDL_QueryTexture(my_texture3, NULL, NULL, &source3.w,&source3.h);

  int nb_images = 9;                         //  Il y a 6 vignette dans la ligne qui nous intéresse
  int nb_images_animation = 4*nb_images;    // 
  float zoom = 1.5;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 9,                // La largeur d'une vignette de l'image
      offset_y = source.h / 3;                // La hauteur d'une vi  SDL_RenderClear(renderer); les vignettes dans le bon ordre pour l'animation
  SDL_Rect state[9];  // construction des différents rectangles autour de chacune des vignettes de la planche 
  int i = 0;                                   
  for (int x = 0; x < source.w; x += offset_x) {
    state[i].x = x;
    state[i].y = 0;
    state[i].w = offset_x;
    state[i].h = offset_y;
      ++i;
  }

  float zoom2=0.2;

  float zoom3=0.5;

  SDL_Rect state2[1];
   int offset_x2 = source.w , offset_y2 = source.h ;

  state2[0].x=0;
  state2[0].y=0;
  state2[0].w = offset_x2;
  state2[0].h = offset_y2;
                          
  destination.w = offset_x * zoom3;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom3;            // Hauteur du sprite à l'écran
  destination.x = 400; // Position en x pour l'affichage du sprite
  destination.y = 300;  // Position en y pour l'affichage du sprite


  destination2.w = offset_x * zoom;
  destination2.h = offset_y * zoom;
  destination2.x = 600;
  destination2.y = 300;

  destination3.w = offset_x2*zoom2;
  destination3.h = offset_x2*zoom2;
  destination3.x = 0;
  destination3.y = 100;

  i = 0;
  for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {

    play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                          window, renderer);
    
    SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                   my_texture, &state[i], &destination);
    
    SDL_RenderCopy(renderer,my_texture2, &state[i],&destination2);

    SDL_RenderCopy(renderer,my_texture3, &state2[0],&destination3);

    destination3.x =destination3.x + (window_dimensions.w/nb_images_animation);
    
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer); //Affichage
    
             
    SDL_Delay(100); // Pause en ms
                          
  }

  SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main 
  SDL_DestroyTexture(my_texture);
  SDL_DestroyTexture(bg_texture);
  SDL_DestroyTexture(my_texture2);
    
  }

  SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
  }


int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;


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
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);



  SDL_Texture* my_texture;
  my_texture = load_texture_from_image("../../img/zombie_tilesheet.png",window,renderer);
  if (my_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);  

  SDL_Texture* bg_texture;
  bg_texture = load_texture_from_image("../../img/backgroundColorDesert.png",window,renderer);
  if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);  


  SDL_Texture* my_texture2;
  my_texture2 = load_texture_from_image("../../img/female_tilesheet.png",window,renderer);
  if (my_texture2 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer); 

  SDL_Texture* my_texture3;
  my_texture3 = load_texture_from_image("../../img/spaceShips_007.png",window,renderer);
  if (my_texture3 == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer); 


 play_with_texture(bg_texture,
                           my_texture,
                           my_texture2,
                           my_texture3,
                           window,
                           renderer);
  
  
  end_sdl(1, "Normal ending", window, renderer);
  IMG_Quit();
  return EXIT_SUCCESS;

}






