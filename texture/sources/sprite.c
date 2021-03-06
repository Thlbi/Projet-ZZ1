
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
             source = {0},                    // Rectangle d??finissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle d??finissant la fen??tre, on n'utilisera que largeur et hauteur
             destination = {0},               // Rectangle d??finissant o?? la zone_source doit ??tre d??pos??e dans le renderer
             state = {0};                     // Rectangle de la vignette en cours dans la planche 

       SDL_GetWindowSize(window,              // R??cup??ration des dimensions de la fen??tre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(my_texture,           // R??cup??ration des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

       /* Mais pourquoi prendre la totalit?? de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous int??resse
       float zoom = 2;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien r??gl??e
           offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien r??gl??e


       state.x = 0 ;                          // La premi??re vignette est en d??but de ligne
       state.y = 3 * offset_y;                // On s'int??resse ?? la 4??me ligne, le bonhomme qui court
       state.w = offset_x;                    // Largeur de la vignette
       state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;       // Largeur du sprite ?? l'??cran
       destination.h = offset_y * zoom;       // Hauteur du sprite ?? l'??cran

       destination.y =                        // La course se fait en milieu d'??cran (en vertical)
         (window_dimensions.h - destination.h) /2;

       int speed = 9;
       for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
         destination.x = x;                   // Position en x pour l'affichage du sprite
         state.x += offset_x;                 // On passe ?? la vignette suivante dans l'image
         state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de d??but de ligne

         SDL_RenderClear(renderer);           // Effacer l'image pr??c??dente avant de dessiner la nouvelle
         SDL_RenderCopy(renderer, my_texture, // Pr??paration de l'affichage
                        &state,
                        &destination);  
         SDL_RenderPresent(renderer);         // Affichage
         SDL_Delay(80);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fen??tre avant de rendre la main
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
	my_texture=load_texture_from_image("../img/player-spritemap-v9.png",window,renderer);
	play_with_texture(my_texture,window,renderer);
	SDL_DestroyTexture(my_texture);
	end_sdl(1, "Chargement de l'image impossible", window, renderer);
   IMG_Quit(); 
}
