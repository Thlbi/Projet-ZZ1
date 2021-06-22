#ifndef _gard_affichage_
#define _gard_affichage_



#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include "labyrinthe.h"

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );
void afficherEcranIntelligemment_2(SDL_Texture* texture_lab,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int **tab);

/*
0=5 6
1=5 2
2=1 4
3=1 0
4=3 3
5 = 3 2  ligne colonne (y x)
6=0 4
7=0 2
8=4 4
9=4 2
10=0 6
11=0 5
12=1 6
13=1 5
14=0 1
15=5 7
*/
#endif