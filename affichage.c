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


void play_with_texture_vaisseau(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer,int pos_x) 
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

     float zoom = 0.25;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x = pos_x;     // La destination est au milieu de la largeur de la fenêtre
     destination.y = window_dimensions.h-destination.h;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
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

  bg_texture = load_texture_from_image("redfighter0005.png",window,renderer);
  if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer,my_texture,bg_texture);

  //play_with_texture_1(my_texture,window,renderer);
  play_with_texture_vaisseau(bg_texture,window,renderer,1000);
  //play_with_texture_3(bg_texture,window,renderer);
  //play_with_texture_4(bg_texture,window,renderer);
  //play_with_texture_5(my_texture,bg_texture,window,renderer);
  //play_with_texture_6(my_texture,bg_texture,window,renderer);
  
  IMG_Quit();
  return EXIT_SUCCESS;
}

