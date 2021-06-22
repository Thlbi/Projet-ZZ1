#include "balek.h"

// gcc balek.c -o prog -Wextra -Wall $(sdl2-config --cflags --libs) -lSDL2_image

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer)
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

  if (!ok) {                
         exit(EXIT_FAILURE);
  }
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


void play_with_background(SDL_Texture *my_background, SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_background, NULL, NULL,&source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              


  SDL_RenderCopy(renderer, my_background,&source,&destination); 
               
}
/*
void play_with_elve_N(SDL_Texture* my_eleve,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y) {
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 0.25;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x = pos_x;    
     destination.y = window_dimensions.h-destination.h;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
}

void play_with_elve_S(SDL_Texture* my_eleve,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y) {
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 0.25;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x = pos_x;    
     destination.y = window_dimensions.h-destination.h;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
}
*/
void play_with_elve_O(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y) {
     SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

     SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
     SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;
    float zoom = 4;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=7*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=3*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=2*offset_x;
    state[2].y=0;
    state[2].w=offset_x;
    state[2].h = offset_y;

    state[3].x=1*offset_x;
    state[3].y=0;
    state[3].w=offset_x;
    state[3].h = offset_y;

    state[4].x=0;
    state[4].y=0;
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=3*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=2*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=1*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=7*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.x=destination.x-(window_dimensions.w/(32*nb_images_animation));
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }           
}       
void play_with_elve_E(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y) {
     SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

     SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
     SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;
    float zoom = 4;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=0;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=4*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=5*offset_x;
    state[2].y=0;
    state[2].w=offset_x;
    state[2].h = offset_y;

    state[3].x=6*offset_x;
    state[3].y=0;
    state[3].w=offset_x;
    state[3].h = offset_y;

    state[4].x=7*offset_x;;
    state[4].y=0;
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=4*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=5*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=6*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=7*offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=4*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.x=destination.x+(window_dimensions.w/(32*nb_images_animation));
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }           
}


int main(int argc, char **argv){
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    SDL_DisplayMode screen;

    SDL_GetCurrentDisplayMode(0, &screen);



    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w*0.6, screen.h *0.6, SDL_WINDOW_RESIZABLE);

    if (window == 0)
        {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
         /* on peut aussi utiliser SDL_Log() */
        }
    SDL_SetWindowTitle(window, "Anim Laby");

 
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    SDL_Texture* texture_elve = NULL;
    SDL_Texture* texture_elve_reverse = NULL;
    SDL_Texture* bg_texture = NULL;

  

    texture_elve = load_texture_from_image("Elve_lign.png",window,renderer);
    if (texture_elve == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    
    texture_elve_reverse = load_texture_from_image("Elve_ligne_reverse.png",window,renderer);
    if (texture_elve_reverse == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    bg_texture = load_texture_from_image("background.png",window,renderer);
    if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    play_with_elve_O(texture_elve_reverse,bg_texture,window,renderer,100,100);




    end_sdl(1, "Normal ending", window, renderer);
    IMG_Quit();
    return EXIT_SUCCESS;
}

