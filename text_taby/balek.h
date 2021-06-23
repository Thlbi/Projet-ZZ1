#ifndef _gard_balek_
#define _gard_balek_



#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

typedef struct camera{
    float x;
    float y;
}Camera_t;


void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer );
void defineClip(SDL_Rect * clip,int pos_x,int pos_y, SDL_Rect window_dimensions,float zoom,int largeur_perso,int hauteur_perso);
void play_with_background(SDL_Texture *my_background, SDL_Window *window, SDL_Renderer *renderer,float zoom);
void play_with_elve_N(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_with_elve_N_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_with_elve_S(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_with_elve_S_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_with_elve_O(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_with_elve_E(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom,SDL_Rect* clip,SDL_Rect window_dimensions);
void play_standstill_1(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_1_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_2(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_2_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_3(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_3_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_4(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);
void play_standstill_4_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom);


#endif