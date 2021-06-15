#ifndef gard_aff
#define gard_aff

#include <SDL2/SDL_image.h>

void end_sdl2(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer,SDL_Texture* my_texture,SDL_Texture* bg_texture);
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void play_with_texture_vaisseau(SDL_Texture * texture_vaisseau,SDL_Window *window,SDL_Renderer *renderer,int position_x);
void afficherEcran(int ** grille,SDL_Window * window,SDL_Renderer *renderer,int position);

#endif
