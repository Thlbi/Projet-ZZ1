#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "labyrinthe.h"

/*
 *chargement des textures
 */
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Renderer *renderer)
{
    SDL_Surface* my_image = NULL;
    SDL_Texture* my_texture = NULL;
    my_image = IMG_Load(file_image_name);

    if (my_image == NULL) exit(EXIT_FAILURE);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL) exit(EXIT_FAILURE);

    return my_texture;
}


void affichage_texture(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer) {
/*  SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

  float zoom = 3;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 8,                // La largeur d'une vignette de l'image
      offset_y = source.h / 4;                // La hauteur d'une vignette de l'image

  *//* construction des différents rectangles autour de chacune des vignettes de la planche */
/*
  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
  destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite
  int i = 0;
  for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
    play_with_texture_1_1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                          window, renderer);
    SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                   my_texture, &state[i], &destination);
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(100);            // Pause en ms
  }

  SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
*/}



SDL_Texture * init_textures(SDL_Renderer* renderer) {

    SDL_Texture* my_texture = NULL;

    my_texture = load_texture_from_image("road.png",renderer);
    if (my_texture==NULL) exit(EXIT_FAILURE);

    return my_texture;
}

void afficherEcranImages(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture){
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        for (int i=0;i<N;i++){
                for (int j=0;j<P;j++){
                        x=tab[i][j];
                        i1=(noeud%P)+1;
                        j1=((int)noeud/P)+1;

                        affichage_texture(texture,window,renderer);

                        noeud+=1;
                        }
                }

        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        SDL_RenderClear(renderer);
}

