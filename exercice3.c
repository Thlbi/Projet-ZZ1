#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void afficherEcran(SDL_Renderer *renderer,int width,int height,int taille){
	SDL_Rect rect;

	int iW,iH,i;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	/*for (i=0;i<width;i++)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		rect.x=i;
		rect.y=i;
		rect.w=1;
		rect.h=taille;
		
		SDL_RenderFillRect(renderer,&rect);
		
		rect.x=width-i;
		SDL_RenderFillRect(renderer,&rect);
	}*/
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawLine(renderer, 0,0,width,height);
	SDL_RenderDrawLine(renderer,width,0,0,height);

	/* afficher à l'ecran */
	
	SDL_RenderPresent(renderer);
}


int main()
{
	SDL_Window *window;
	int width=700, height=700,taille=10;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE);

        if (window == 0)
        {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        }


	SDL_Renderer * renderer;
	renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	if (renderer == 0) {
     	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}

	afficherEcran(renderer,width,height,taille);
	SDL_Delay(5000);
	int running=1;
	SDL_Event
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
