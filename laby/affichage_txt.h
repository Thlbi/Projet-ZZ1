#ifndef _gard_text_
#define _gard_text_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void affichage_txt(SDL_Window *window,SDL_Renderer *renderer);
void affichage_txt_pause(SDL_Window *window,SDL_Renderer *renderer);
void affichage_txt_perdu(SDL_Window *window,SDL_Renderer *renderer);
void timer(SDL_Window * window,SDL_Renderer * renderer, int timer);
#endif
