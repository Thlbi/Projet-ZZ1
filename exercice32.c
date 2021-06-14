#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/*gcc exercice2.c -o prog $(sdl2-config  --cflags --libs)*/
/************************************/



int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  
  int longueur=1500;
  int i;

  SDL_Window *window_1 = NULL,               // Future fenêtre de gauche
      *window_2 = NULL;                      // Future fenêtre de droite

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  for (i=0;i<(longueur/100);i++){
  	window_1 = SDL_CreateWindow("diagonale descendante", 100*i, 50*i,400, 300,SDL_WINDOW_RESIZABLE);

  	if (window_1 == NULL) {
    	SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    	SDL_Quit();
    	exit(EXIT_FAILURE);
  	}
  }
  /* Création de la fenêtre de droite */
  for (i=0;i<(longueur/100);i++){
  	window_2 = SDL_CreateWindow("diag montante",longueur-100*i, 50*i,500, 300,0);

  	if (window_2 == NULL) {
   	 /* L'init de la SDL : OK
       	fenêtre 1 :OK
       	fenêtre 2 : échec */
    	SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
	}
  }
  SDL_Delay(2000);
  SDL_DestroyWindow(window_1);
  SDL_DestroyWindow(window_2);

  SDL_Quit();
  return 0;
 }
 (on ne sait pas encore arrêter un programme suite à un évènement…
