/*SDL_ttf.c*/
/*15 juin 2021*/
/*gcc SDL_ttf.c -o prog -Wall -Wextra -lSDL2 -lSDL2_ttf -lm -g*/
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 
#include<stdlib.h>

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


int main ()
{


   if (SDL_Init(SDL_INIT_VIDEO) == -1)
   {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            return EXIT_FAILURE;
      }
   SDL_Window *window;
      int width = 1900;
      int height = 1000;
        window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

   if (window == 0)
      {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
         /* on peut aussi utiliser SDL_Log() */
      }
      SDL_SetWindowTitle(window, "Hello");
      SDL_Renderer *renderer;

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == 0)
   {
   	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   }

TTF_Font* font = NULL;                    
font = TTF_OpenFont("./fonts/Pacifico.ttf", 65);      
if (font == NULL) end_sdl(0, "Can't load font", window, renderer);

TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);   

SDL_Color color = {20, 0, 40, 255};                         
SDL_Surface* text_surface = NULL;                          
text_surface = TTF_RenderText_Blended(font, "Hello World !", color);
if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

SDL_Texture* text_texture = NULL;                                  
text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
SDL_FreeSurface(text_surface);                                     

SDL_Rect pos = {0, 0, 0, 0};                                      
SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);      
SDL_RenderCopy(renderer, text_texture, NULL, &pos);             
SDL_DestroyTexture(text_texture);                              

   SDL_Event event;
   int running=1;
      while (running)
      {
         while (SDL_PollEvent(&event))
         {
                  switch (event.type)
                  {
                     case SDL_WINDOWEVENT:
                     switch (event.window.event)
                     {
                        case SDL_WINDOWEVENT_CLOSE:
                           running = 0;
                           break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                           width = event.window.data1;
                           height = event.window.data2;
                           break;
                        case SDL_WINDOWEVENT_EXPOSED:
                           break;
                     }
                     break;
                  	case SDL_QUIT:
                     	running = 0;
                     	break;
         			}
      	}
		SDL_RenderPresent(renderer);               	
		SDL_Delay(150);
		
		}
   end_sdl(1, "Normal ending", window, renderer);
}
                                     


