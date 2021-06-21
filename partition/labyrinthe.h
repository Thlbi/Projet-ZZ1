#ifndef _gard_labyrinthe
#define _gard_labyrinthe
#include "partition_a.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "affichage_image.h"

#define N 20 //nbr lignes
#define P 35 //nbr colonnes
#define TAILLE (N*P)
#define ARG_P 0.5

int ** labyrinthe_arbo();
couple_t * ordonner_Fisher(couple_t *c);
void afficherEcran(SDL_Renderer *renderer,aretes_t *A);
void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab,int taille_cell);
void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);

#endif
