#ifndef gard_aff
#define gard_aff

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define HAUTEUR_MET  15
#define PIXEL 5

void end_sdl2(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer);

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer);

void play_with_texture_vaisseau(SDL_Texture * texture_vaisseau,SDL_Window *window,SDL_Renderer *renderer,int position_x);

void background(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);

void play_with_meteore(SDL_Texture * texture_meteore,SDL_Window * window,SDL_Renderer * renderer,int position_x,int position_y);

void affichage_texte(int victoire,SDL_Window *window,SDL_Renderer *renderer);


#endif
