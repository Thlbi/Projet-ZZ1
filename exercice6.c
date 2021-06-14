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
                              120, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                              255);                                   // 0 = transparent ; 255 = opaque
    
    rectangle.x = 200;                                                    // x haut gauche du rectangle
    rectangle.y = 200;                                                    // y haut gauche du rectangle
    rectangle.w = 600;                                                  // sa largeur (w = width)
    rectangle.h = 600;                                                  // sa hauteur (h = height)

    SDL_RenderDrawRect(renderer, &rectangle);


    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}

void draw2(SDL_Renderer *renderer, int width,int height, int taille)
{
    SDL_Rect rectangle; 

    
    SDL_SetRenderDrawColor(renderer,                                
                              0, 0, 120,                               // mode Red, Green, Blue (tous dans 0..255)
                              255);      
                                                          // 0 = transparent ; 255 = opaque
    rectangle.x = 0;                                                    // x haut gauche du rectangle
    rectangle.y = 0;                                                    // y haut gauche du rectangle
    rectangle.w = 400;                                                  // sa largeur (w = width)
    rectangle.h = 400;                                                  // sa hauteur (h = height)

    SDL_RenderDrawRect(renderer, &rectangle);

    /*
    SDL_RenderDrawLine(renderer,
                          0, 0,                                       // x,y du point de la première extrémité
                          width, height);                                  // x,y seconde extrémité
    */

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}






int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;

    SDL_Event event;

    int continuer = 1;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }


  SDL_GetCurrentDisplayMode(0, &screen);

  int width=screen.w,height=screen.h,taille=10;

  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w*0.66 ,
                            screen.h*0.66 ,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);


/*********************************************************************************************************************/
  /*                            On dessine dans le renderer                                                   */
  
  draw(renderer,width,height,taille);                                                     // appel de la fonction qui crée l'image  
  SDL_RenderPresent(renderer);                                        // affichage                                                  // Pause exprimée en ms
  while (continuer)
  {
    SDL_PollEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer=0;

        break;
    }
      draw2(renderer,width,height,taille);
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
      SDL_RenderClear(renderer);
      draw(renderer,width,height,taille);
      SDL_RenderPresent(renderer);
      SDL_Delay(100);
      SDL_RenderClear(renderer);

  }

  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}