#ifndef _gard_balek_
#define _gard_balek_



#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include "affichage_image.h"
#include "kruskal.h"

void play_with_background(SDL_Texture *my_background, SDL_Window *window, SDL_Renderer *renderer,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_N(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_N_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_S(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_S_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_O(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_with_elve_E(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_standstill(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);
void play_standstill_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom,int **tab, int taille_cell,SDL_Texture *texture_fin,int noeud_arrive);


#endif
