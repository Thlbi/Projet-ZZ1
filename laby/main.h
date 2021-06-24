
/*main.h*/
/*15 juin 2021*/
#ifndef main_gard
#define main_gard

#include<SDL2/SDL.h>
#include "kruskal.h"
#include "dijsktra.h"
#include "DFS.h"
#include <math.h>

typedef enum {
	FLAG_N=1,
	FLAG_S=2,
	FLAG_E=4,
	FLAG_O=8
}flag_t;

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
void afficheEcranIntelligement(SDL_Renderer*,int**,int);
void chemin(SDL_Renderer *,int, int, int, int *);
int min(int , int);
int main(int ,char**);

#endif
