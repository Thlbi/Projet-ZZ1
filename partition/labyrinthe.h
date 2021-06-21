#include "partition_a.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define N 5
#define P 5
#define TAILLE (N*P)

void labyrinthe_arbo();
couple_t * ordonner_Fisher(couple_t *c);
void afficherEcran(SDL_Renderer *renderer,aretes_t *A);
void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
void creation_SDL(aretes_t *A);
