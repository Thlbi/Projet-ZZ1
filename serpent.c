/***15 juin 2021 serpent.c***/
/*** compile avec gcc serpent.c -o prog -Wall -Wextra -lSDL2 -lm****/
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

void dessin(SDL_Renderer* renderer,int frame)
{
	int x=50,y=50,x1,y1,z;

	for (int i=0; i<17;i++)
	{
		if (17-frame>=i)
		{
			z=rand()%30;
			x1=(x+z)%1500;      
			y1=(y+30-z)%800;
		}

  		SDL_SetRenderDrawColor(renderer,30*i, 50, i,255);   
  		SDL_RenderDrawLine(renderer, x,y,x1,y1);
		SDL_RenderPresent(renderer);
		x=x1;
		y=y1;
		SDL_Delay(10);
	}
  	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

int main ()
{
	srand(time(0));
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
       	 	return EXIT_FAILURE;
    	}
	SDL_Window *window;
    	int width = 1500;
    	int height = 800;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

	if (window == 0)
    	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    	}
    	SDL_SetWindowTitle(window, "serpent");
    	SDL_Renderer *renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    	if (renderer == 0)
    	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    	}
	SDL_Event event;
	int running=1;
   	while (running)
    	{
		for (int i=0;i<18;i++)
		{

			dessin(renderer,i);
			SDL_Delay(100);
  			SDL_RenderClear(renderer);
		}
        	while (SDL_PollEvent(&event))
        	{
            		switch (event.type)
            		{
            			case SDL_WINDOWEVENT:
                			switch (event.window.event)
                			{
                				case SDL_WINDOWEVENT_CLOSE:
                    					printf("appui sur la croix\n");
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
                			printf("on quitte\n");
					running = 0;
            		}
        	}
		SDL_Delay(1);
    	}
	end_sdl(1, "Normal ending", window, renderer);
}
