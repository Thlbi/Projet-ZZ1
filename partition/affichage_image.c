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


/*
 *affiche les textures du labyrinthes en fonction de la position des murs autour de la case
 */
void affichage_texture(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int x,int coord_colonne,int coord_ligne) {
  SDL_Rect source = {0},  // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0}, // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0}, // Rectangle définissant où la zone_source doit être déposée dans le renderer
    state = {0};

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);
  float zoom = 1.5;                             // valeur du zoom pour l'affichage final
  int offset_x = source.w / 14,                // La largeur d'une vignette de l'image 14
      offset_y = source.h / 9.4;                // La hauteur d'une vignette de l'image 9.4 
 	state.w = offset_x;
  	state.h = offset_y;
  
  switch (x){
  	case 6 :
  		state.x = 140;
  		state.y = 15;
		break;
  	case 10 :
  		state.x = 265;
  		state.y = 15;
		break;
 
  	case 5 :
  		state.x = 140;
  		state.y = 140;
		break;
  
  	case 9 :
  		state.x = 265;
  		state.y = 140;
		break;

  	case 3 :
  		state.x = 10;
  		state.y = 0;
		break;

  	case 12 :
  		state.x = 10;
  		state.y = 137;
		break;

  	case 15 :
  		state.x = 1160;
  		state.y = 10;
		break;
  
  	case 7 :
  		state.x = 525;
  		state.y = 265;
		break;
  
  	case 11 :
  		state.x = 645;
  		state.y = 265;
		break;

  	case 13 :
  		state.x = 522;
  		state.y = 392;
		break;
  
  	case 14 :
  		state.x = 647;
  		state.y = 397;
		break;
  
  	case 2 :
  		state.x = 1034;
  		state.y = 266;
		break;
  
  	case 1 :
  		state.x = 1161;
  		state.y = 265;
		break;

  	case 8 :
  		state.x = 1161;
  		state.y = 393;
		break;
  
  	case 4 :
  		state.x = 1036;
  		state.y = 393;
 		break;
	case 0 :
  		state.x = 0;
  		state.y = 265;
 		break;
  }

 /* construction des différents rectangles autour de chacune des vignettes de la planche */

  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = 10+coord_colonne*(source.h / 9.4)*zoom; // Position en x pour l'affichage du sprite
  destination.y = 10+coord_ligne*(source.h / 9.4)*zoom;  // Position en y pour l'affichage du sprite
  SDL_RenderCopy(renderer,my_texture,&state, &destination);   // Préparation de l'affichage

}



SDL_Texture * init_textures(SDL_Renderer* renderer) {

    SDL_Texture* my_texture = NULL;

    my_texture = load_texture_from_image("road.png",renderer);
    if (my_texture==NULL) exit(EXIT_FAILURE);

    return my_texture;
}

void afficherImage(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture){
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        for (int i=0;i<N;i++){
                for (int j=0;j<P;j++){
                        x=tab[i][j];
                        i1=(noeud%P)+1; //coordonee colonne du noeud
                        j1=((int)noeud/P)+1; // coordonee ligne du noeud

  			printf("%d ",x);
  			affichage_texture(texture,window,renderer,x,i1,j1);

                        noeud+=1;
                        }
                }

        SDL_RenderPresent(renderer);
        SDL_Delay(20000);
        SDL_RenderClear(renderer);
}

