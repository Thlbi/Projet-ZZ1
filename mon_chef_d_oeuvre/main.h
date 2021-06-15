/*main.h*/
/*15 juin 2021*/
#ifndef main_gard
#define main_gard

#include<SDL2/SDL.h>
#include "grille.h"
#include "affichage.h"

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
int main();

#endif
