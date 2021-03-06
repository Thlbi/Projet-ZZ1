/*image.c*/
/*17 juin 2021*/
#include <SDL2/SDL_image.h>        
#include <SDL2/SDL.h>
#include <math.h>

/*gcc fade.c -o fade -Wall -Wextra -g -lSDL2 -lSDL2_image */
void end_sdl(char ok, char const* msg, SDL_Window* window,  SDL_Renderer* renderer) 
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
                                      
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
	 SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme ??l??ment transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;  
}
void play_with_texture(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
  SDL_Rect 
        source = {0},                             // Rectangle d??finissant la zone de la texture ?? r??cup??rer
        window_dimensions = {0},                  // Rectangle d??finissant la fen??tre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer

  SDL_GetWindowSize(                                
      window, &window_dimensions.w,                 
      &window_dimensions.h);                      // R??cup??ration des dimensions de la fen??tre
  SDL_QueryTexture(my_texture, NULL, NULL,         
                   &source.w,                       
                   &source.h);                    // R??cup??ration des dimensions de l'image

  /* On d??cide de d??placer dans la fen??tre         cette image */
  float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affich??e

  int nb_it = 200;                                // Nombre d'images de l'animation
  destination.w = source.w * zoom;                // On applique le zoom sur la largeur
  destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
  destination.x =                                   
      (window_dimensions.w - destination.w) / 2;  // On centre en largeur
  float h = window_dimensions.h - destination.h;  // hauteur du d??placement ?? effectuer

  for (int i = 0; i < nb_it; ++i) {
    destination.y =
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                     (1 + cos(10.0 * i / nb_it * 2 *
                              M_PI)));            // hauteur en fonction du num??ro d'image

    SDL_RenderClear(renderer);                    // Effacer l'image pr??c??dente

    SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacit?? va passer de 255 ?? 0 au fil de l'animation
    SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Pr??paration de l'affichage
    SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
    SDL_Delay(30);                                // Pause en ms
  }                                                 
  SDL_RenderClear(renderer);                      // Effacer la fen??tre une fois le travail termin??
}

int main()
{
if (SDL_Init(SDL_INIT_VIDEO) == -1) 
   {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            return EXIT_FAILURE;
      }   
   SDL_Window *window;
      int width = 900;
      int height =900;

   window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height, SDL_WINDOW_RESIZABLE);

   if (window == 0)
      {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
         /* on peut aussi utiliser SDL_Log() */
      }   
      SDL_SetWindowTitle(window, "Image");
      SDL_Renderer *renderer;

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
      if (renderer == 0)
      {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      }   

   SDL_Texture* my_texture = NULL;         
	my_texture=load_texture_from_image("../img/sun.png",window,renderer);
	play_with_texture(my_texture,window,renderer);
	SDL_DestroyTexture(my_texture);
	end_sdl(1, "Chargement de l'image impossible", window, renderer);
   IMG_Quit(); 
}
