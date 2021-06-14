#include <SDL2/SDL.h>
#include <stdio.h>
#include<stlib.h>

int minimum(int a, int b)
{
	if (a>=b)
		return b;
	else return a;
} 

void diago(SDL_Renderer *renderer,int taille,int longueur, int largeur)

{
	 int min= minimum(longeur,largeur);
    SDL_Rect rect;
    int i; 
    SDL_Color couleur = {0, 255, 255, 255};
	 
	 for (i=0;i<400;i++)
	 {
    SDL_SetRenderDrawColor(renderer,0,255,255,255);
    rect.x = i;
    rect.y = i;
    rect.w = 1;
    rect.h = taille;
	 SDL_RenderFillRect(renderer, &rect );
        
    }
	 for (i=900;i<400;i--)
	 {
    	SDL_SetRenderDrawColor(renderer,0,255,255,255);
    	rect.x = i;
    	rect.y = i;
    	rect.w = 1;
    	rect.h = taille;
	 	SDL_RenderFillRect(renderer, &rect );
        
    }
}
int main()
{
 SDL_Window *window;
    int width = 900;
    int height = 600;
    int taille = 10;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (window == 0)
    {   
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        /* on peut aussi utiliser SDL_Log() */
    }   
    SDL_SetWindowTitle(window, "Des morts et des bulles");
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */

    if (renderer == 0)
    {   
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
	 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	 SDL_RenderClear(renderer);
    diago(renderer,taille);
    SDL_RenderPresent(renderer);
	 SDL_Delay(20000);
	 SDL_DestroyWindow(window);
}
