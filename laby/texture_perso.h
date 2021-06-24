#ifndef _gard_balek_
#define _gard_balek_



#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include "affichage_image.h"
#include "kruskal.h"

void play_with_elve_N(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_with_elve_N_l(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_with_elve_S(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_with_elve_S_l(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_with_elve_O(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_with_elve_E(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom);
void play_standstill(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_l(SDL_Texture* texture_elve,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);


#endif
