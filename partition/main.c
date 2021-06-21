#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partition_a.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <time.h>
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage_image.h"

int main(){
	srand(time(0));
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Window * window;

  	int taille_cell;

  	if (SDL_Init(SDL_INIT_VIDEO) == -1){
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        	exit(EXIT_FAILURE);
   	}
   	SDL_DisplayMode screen;
   	SDL_GetCurrentDisplayMode(0, &screen);

   	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h,SDL_WINDOW_RESIZABLE);
   	if (window == 0) {
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   	}
   	SDL_SetWindowTitle(window, "Labyrinthe");

   	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   	if (renderer == 0){
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   	}

   	if (screen.w/N<screen.h/P){
        	taille_cell=(screen.w/N)+10;
   	}
   	else
        	taille_cell=(screen.h/P)+10;

	texture=init_textures(renderer);
	
	int ** tab=labyrinthe_arbo();

	afficherEcranIntelligemment(renderer,tab,taille_cell);
	afficherImage(renderer,window,tab,taille_cell,texture);

	return 0;
}
