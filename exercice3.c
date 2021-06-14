#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int main()
{
	SDL_Window** tab =malloc (10*(sizeof(SDL_Window *)));
	int width=1920/5, height=1080/5;
	int x=0;
	int y=0;

	for (int i=0;i<5;i++)
	{
		tab[i] = SDL_CreateWindow("window", x,y,width, height,SDL_WINDOW_RESIZABLE);
		x+=width;
		y+=height;

        	if (tab[i] == 0)
       	 	{
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        	}	
		SDL_Delay(300);

	}

	x=0;
	y=800;
	for (int i=5;i<10;i++)
	{
		tab[i] = SDL_CreateWindow("window", x,y,width, height,SDL_WINDOW_RESIZABLE);
		x+=width;
		y-=height;
	
	        if (tab[i] == 0)
        	{
        		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
       	 	}
		SDL_Delay(300);
	}
	SDL_Delay(2000);
	for (int i=0;i<10;i++)
	{
		SDL_DestroyWindow(tab[i]);
		SDL_Delay(300);
	}
	free(tab);
	SDL_Quit();
}
