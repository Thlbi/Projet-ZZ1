/***15 juin 2021 serpent.c***/
/*** compile avec gcc serpent.c -o prog -Wall -Wextra -lSDL2 -lm****/
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "serpent.h"

#define NB_SERPENT 1
#define NB_CASE 10

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

void dessin(SDL_Renderer* renderer,cellule_t ** tab,int numero_serpent,int aleat)
{
	int x=600,y=200,x1,y1,z=0,i=0;
	cellule_t ** prec=tab;

	while (*prec!=NULL)
	{
		if (aleat) z=rand()%13;
		if (z>9) z=-z;
		x1=x+(*prec)->x+z;
		y1=y+(*prec)->y-z;
		(*prec)->x+=z;
		(*prec)->y-=z;
		prec=&(*prec)->suiv;

  		SDL_SetRenderDrawColor(renderer,30*i, 50, i,255);   
  		SDL_RenderDrawLine(renderer, x,y,x1,y1);

		x=x1;
		y=y1;
		i=i+1;
	}
  	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

cellule_t * allouer(int num,int coord_x,int coord_y)
{
        cellule_t * nouv=(cellule_t *)malloc(sizeof(cellule_t));
        if(nouv!=NULL)
   {
      nouv->num_serpent=num;
      nouv->x=coord_x;
      nouv->y=coord_y;
        }
        return nouv;
}

void adj_cell(cellule_t **prec,cellule_t *nouv)
{
                *prec=nouv;
}

void SuppCell(cellule_t **prec)
{
        cellule_t * cour=*prec;
        *prec=(*prec)->suiv;
        free(cour);
}

void init_serpent(cellule_t ** tab,int numero_serpent)
{
        int x=50+50*numero_serpent,y=50+50*numero_serpent,x1,y1,z;
	cellule_t ** prec=tab;
	cellule_t * nouv;

        for (int i=0; i<17;i++)
        {
                if (17-NB_CASE>=i)
                {
                        z=rand()%30;
                        x1=(x+z)%1500;
                        y1=(y+30-z)%800;
			nouv=allouer(i,x1,y1);
			adj_cell(prec,nouv);
			prec=&nouv->suiv;
                }
        }
}

int main ()
{
	cellule_t * tab;
	int i;
	
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
	for (i=0;i<NB_SERPENT;i++)
	{
		init_serpent(&tab,i);
	}
	SDL_Event event;
	dessin(renderer,&tab,i,0);
	SDL_Delay(100);

	int running=1;
   	while (running)
    	{
		SDL_RenderClear(renderer);
		for (i=0;i<NB_SERPENT;i++)
		{
			dessin(renderer,&tab,i,1);
			SDL_RenderPresent(renderer);
		}

        	while (SDL_PollEvent(&event))
        	{
            		switch (event.type)
            		{
            			case SDL_WINDOWEVENT:
                			switch (event.window.event)
                			{
                				case SDL_WINDOWEVENT_CLOSE:
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
            		}
        	}
		SDL_Delay(100);
    	}
	end_sdl(1, "Normal ending", window, renderer);
	for (int i=0;i<NB_SERPENT;i++){
		while (tab!=NULL){
			SuppCell(&tab);
		}
	}
}
