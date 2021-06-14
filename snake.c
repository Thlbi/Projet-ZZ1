/***14 juin 2021 snake.c***/
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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

void dessin1(SDL_Renderer* renderer)
{
	SDL_Rect rectangle;
  	SDL_SetRenderDrawColor(renderer,50, 50, 0,255);    
	for (int i=0; i<5;i++)
	{
  		rectangle.x = 140+20*pow(-1,i);        
  		rectangle.y = 90*i;         
  		rectangle.w = 50;        
  		rectangle.h = 80;         
	
  		SDL_RenderDrawRect(renderer, &rectangle);
	}
  	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void dessin2(SDL_Renderer* renderer)
{
	SDL_Rect rectangle;

  	SDL_SetRenderDrawColor(renderer,50, 50, 0,255);   
  	for (int i=0; i<5;i++)
	{
  		rectangle.x = 140-20*pow(-1,i);        
  		rectangle.y = 90*i;         
  		rectangle.w = 50;        
  		rectangle.h = 80;         
	
  		SDL_RenderDrawRect(renderer, &rectangle);
	} 
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
int main ()
{

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
       	 	return EXIT_FAILURE;
    	}
	SDL_Window *window;
    	int width = 900;
    	int height = 600;
    	int taille = 0;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

	if (window == 0)
    	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        	/* on peut aussi utiliser SDL_Log() */
    	}
    	SDL_SetWindowTitle(window, "snake");
    	SDL_Renderer *renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    	if (renderer == 0)
    	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    	}
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
            		break;
        	}
		dessin1(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(200);
  		SDL_RenderClear(renderer);
		dessin2(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(200);
  		SDL_RenderClear(renderer);
    	}
	end_sdl(1, "Normal ending", window, renderer);
}
