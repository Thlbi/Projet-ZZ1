#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage_image.h"

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
void affichage_texture(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int x,int coord_colonne,int coord_ligne,int taille_cell) {
  SDL_Rect source = {0},  // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0}, // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0}, // Rectangle définissant où la zone_source doit être déposée dans le renderer
    state = {0};

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);
  float zoom = (float)taille_cell/(float)109;                // valeur du zoom pour l'affichage final
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
  		state.x = 139;
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
  		state.y = 143;
		break;

  	case 15 :
  		state.x = 1162;
  		state.y = 13;
		break;
  
  	case 7 :
  		state.x = 522;
  		state.y = 271;
		break;
  
  	case 11 :
  		state.x = 649;
  		state.y = 271;
		break;

  	case 13 :
  		state.x = 522;
  		state.y = 398;
		break;
  
  	case 14 :
  		state.x = 650;
  		state.y = 399;
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
  		state.y = 398;
		break;
  
  	case 4 :
  		state.x = 1036;
  		state.y = 398;
 		break;
	case 0 :
  		state.x = 0;
  		state.y = 265;
 		break;
  	case 22 :
  		state.x = 140;
  		state.y = 15;
		break;
  	case 26 :
  		state.x = 265;
  		state.y = 15;
		break;
 
  	case 21 :
  		state.x = 139;
  		state.y = 140;
		break;
  
  	case 25 :
  		state.x = 265;
  		state.y = 140;
		break;

  	case 19 :
  		state.x = 10;
  		state.y = 0;
		break;

  	case 28 :
  		state.x = 10;
  		state.y = 143;
		break;

  	case 31 :
  		state.x = 1162;
  		state.y = 13;
		break;
  
  	case 23 :
  		state.x = 522;
  		state.y = 271;
		break;
  
  	case 27 :
  		state.x = 649;
  		state.y = 271;
		break;

  	case 29 :
  		state.x = 522;
  		state.y = 398;
		break;
  
  	case 30 :
  		state.x = 650;
  		state.y = 399;
		break;
  
  	case 18 :
  		state.x = 1034;
  		state.y = 266;
		break;
  
  	case 17 :
  		state.x = 1161;
  		state.y = 265;
		break;

  	case 24 :
  		state.x = 1161;
  		state.y = 398;
		break;
  
  	case 20 :
  		state.x = 1036;
  		state.y = 398;
 		break;
	case 16 :
  		state.x = 0;
  		state.y = 265;
 		break;
	}

 /* construction des différents rectangles autour de chacune des vignettes de la planche */

  destination.w = offset_x * zoom+1;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom+1;            // Hauteur du sprite à l'écran
  destination.x = 1+coord_colonne*(source.h / 9.4)*zoom; // Position en x pour l'affichage du sprite
  destination.y = 1+coord_ligne*(source.h / 9.4)*zoom;  // Position en y pour l'affichage du sprite
  SDL_RenderCopy(renderer,my_texture,&state, &destination);   // Préparation de l'affichage

}


void affichage_fin(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int coord_colonne,int coord_ligne,int taille_cell) {
  SDL_Rect source = {0},  // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0}, // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0}, // Rectangle définissant où la zone_source doit être déposée dans le renderer
    state = {0};

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,&window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);
  float zoom = (float)taille_cell/(float)16.1;                // valeur du zoom pour l'affichage final
  int offset_x = source.w / 56,                // La largeur d'une vignette de l'image 56
      offset_y = (float)source.h / (float)12;                // La hauteur d'une vignette de l'image 11
  	state.x = 0;
  	state.y = source.h-3*offset_y-3;
 	state.w = offset_x;
  	state.h = offset_y;
  destination.w = offset_x * zoom+1;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom+1;            // Hauteur du sprite à l'écran
  destination.y = 1+coord_colonne*(source.w / 56)*zoom; // Position en x pour l'affichage du sprite
  destination.x = coord_ligne*(source.w / 56)*zoom+6;  // Position en y pour l'affichage du sprite
  SDL_RenderCopy(renderer,my_texture,&state, &destination);   // Préparation de l'affichage
}


void print_sewer(SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer,int coord_colonne,int coord_ligne,int taille_cell) {

  SDL_Rect source = {0},window_dimensions = {0},destination = {0},state = {0};

  SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,&source.w, &source.h);
  state.x = 0;
  state.y = 0;
  state.w = source.w;
  state.h = source.h;
  float zoom = (float)taille_cell/(float)460; 
  destination.w = source.w * zoom;            // Largeur du sprite à l'écran
  destination.h = source.h * zoom;            // Hauteur du sprite à l'écran
  destination.y =5+coord_ligne*source.w*zoom; // Position en ligne pour l'affichage du sprite
  destination.x = coord_colonne*source.w*zoom+5;  // Position en colonne pour l'affichage du sprite
  printf("%d %d \n",destination.x,destination.y);
  SDL_RenderCopy(renderer,my_texture,&state, &destination);   // Préparation de l'affichage
}


void afficherImage(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture){
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        for (int i=0;i<N;i++){
                for (int j=0;j<P;j++){
                        x=tab[j][i];
                        i1=(noeud%P); //coordonee colonne du noeud
                        j1=((int)noeud/P); // coordonee ligne du noeud

  			affichage_texture(texture,window,renderer,x,i1,j1,taille_cell);
			noeud+=1;
                        }
                }
}


void afficherImageBrouillard(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture, int pos_x, int pos_y)
{
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
	SDL_Texture *texture_sewer = load_texture_from_image("sewer.png",renderer);
  	if (texture_sewer==NULL) exit(EXIT_FAILURE);

        for (int i=0;i<N;i++){
                for (int j=0;j<P;j++){
                        x=tab[j][i];
                        i1=(noeud%P); //coordonee colonne du noeud
                        j1=((int)noeud/P); // coordonee ligne du noeud

  			affichage_texture(texture,window,renderer,x,i1,j1,taille_cell);
  			if (x>15){
				print_sewer(texture_sewer,window,renderer,i1,j1,taille_cell);
			}
                        noeud+=1;
                }
        }
	/*SDL_Texture *texture_brouillard = load_texture_from_image("fog.png",renderer);
    	if (texture_brouillard==NULL) exit(EXIT_FAILURE);
        
  	SDL_Rect source={0},window_dimensions = {0},destination = {0};
	SDL_QueryTexture(texture_brouillard, NULL, NULL,&source.w, &source.h);
  	SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);
  	destination.w = 101*taille_cell;
  	destination.h = 91*taille_cell;
  	destination.y = pos_y-45*taille_cell;
  	destination.x = pos_x-50*taille_cell;
  	SDL_RenderCopy(renderer,texture_brouillard,&source,&destination);

	SDL_DestroyTexture(texture_brouillard);
*/}


void peindreMap(SDL_Texture * texture, SDL_Window* window ,SDL_Renderer *renderer, int noeuds, int taille_cell, int ** laby)
{
        affichage_texture(texture,window, renderer, laby[noeuds%P][noeuds/P], noeuds%P, noeuds/P, taille_cell);
}


