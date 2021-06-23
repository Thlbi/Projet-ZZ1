
/*main.h*/
/*15 juin 2021*/
#ifndef main_gard
#define main_gard

#include<SDL2/SDL.h>
#include "kruskal.h"
#include "dijsktra.h"
#include <math.h>

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
void afficheEcranIntelligement(SDL_Renderer*,int**,int);
int min(int , int);
int main(int ,char**);

#endif
