#ifndef _gard_affichage_image
#define _gard_affichage_image

#include "kruskal.h"
#include "main.h"

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Renderer *renderer);
void affichage_texture(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int x,int coord_colonne,int coord_ligne,int taille_cell);
void afficherImage(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture);
void afficherImageBrouillard(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture, int pos_x, int pos_y);

void point_minimap(SDL_Renderer * renderer, int taille_cell, int pos_x, int pos_y);

void affichage_fin(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int coord_colonne,int coord_ligne,int taille_cell);
void peindreMap(SDL_Texture * texture, SDL_Window* window ,SDL_Renderer *renderer, int noeuds, int taille_cell, int ** laby);

#endif
