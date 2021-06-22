#ifndef _gard_affichage_image
#define _gard_affichage_image

void affichage_texture(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int x,int coord_colonne,int coord_ligne,int taille_cell);
SDL_Texture * init_textures(SDL_Renderer * renderer);
void afficherImage(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture);

#endif
