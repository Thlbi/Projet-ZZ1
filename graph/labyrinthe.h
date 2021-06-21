#ifndef _gard_laby_
#define _gard_laby_

#include "graph.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



#define N 10
#define P 10
#define TAILLE (N*P)
typedef enum
{
    FLAG_N = 1,
    FLAG_S = 2,
    FLAG_E = 4,
    FLAG_O = 8
} flag_t;
void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
int **tableau_aretes(arete_t *A);
void generer_couple_2(graph_t *graph);
void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab);
void creation_SDL(int** tab);
graph_t * ordonner_Fisher(graph_t *c);
void liberer(int **tab);
#endif

