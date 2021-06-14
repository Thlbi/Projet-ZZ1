#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


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





void draw(SDL_Renderer *renderer, int width,int height, int taille)
{
    SDL_Rect rectangle; 
    SDL_SetRenderDrawColor(renderer,                                
                              0, 0, 120,                               // mode Red, Green, Blue (tous dans 0..255)
                              255);                                   // 0 = transparent ; 255 = opaque
    rectangle.x = 0;                                                    // x haut gauche du rectangle
    rectangle.y = 0;                                                    // y haut gauche du rectangle
    rectangle.w = width;                                                  // sa largeur (w = width)
    rectangle.h = width;                                                  // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 26, 168, 43, 255);
    SDL_RenderDrawLine(renderer,
                          0, 0,                                       // x,y du point de la première extrémité
                          width, height);                                  // x,y seconde extrémité
    SDL_RenderDrawLine(renderer,
                          width, 0,                                       // x,y du point de la première extrémité
                          0, height);
}








int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;


    
    int width=1400,height=700,taille=10;


  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
  /* Création de la fenêtre de gauche */
  window = SDL_CreateWindow(
      "Fenêtre à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      width  , height,                              // largeur = 300  , hauteur = 400
      SDL_WINDOW_RESIZABLE);                 // redimensionnable


  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

/*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
  draw(renderer,width,height,taille);                                                     // appel de la fonction qui crée l'image  
  SDL_RenderPresent(renderer);                                        // affichage
  SDL_Delay(5000);                                                    // Pause exprimée en ms

  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}