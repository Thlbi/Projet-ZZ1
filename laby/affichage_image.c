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


void afficherImageBrouillard2(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture, int pos_x, int pos_y)
{
        int i1,j1,j;
        int * voisin = malloc(9*sizeof(int));
	int x=pos_x/taille_cell;
	int y=pos_y/taille_cell;

	
	for (j=0;j<9;j++)
		voisin[j]=-1;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        if (tab[x][y] & FLAG_N)
                voisin[0]=x+P*y-P;
        if (tab[x][y] & FLAG_S)
                voisin[1]=x+P*y+P ;
        if (tab[x][y] & FLAG_O)
                voisin[2]=x+P*y -1;
        if (tab[x][y] & FLAG_E)
                voisin[3]=x+P*y+1;
	
	if (y>0){
		if (x>0){
			if (((tab[x][y] & FLAG_O) && (tab[x-1][y] & FLAG_N )) || ((tab[x][y] & FLAG_N) && (tab[x][y-1] & FLAG_O)))
				voisin[5]=x+P*y-P-1;
		}
		if (x<P-1){
			if (((tab[x][y] & FLAG_N) && (tab[x+1][y-1] & FLAG_E )) || ((tab[x][y] & FLAG_E) && (tab[x][y-1] & FLAG_N)))
				voisin[6]=x+P*y-P+1;
		}
	}

	if (y<N-1){
		if (x>0){
			if (((tab[x][y] & FLAG_O) && (tab[x-1][y] & FLAG_S )) || ((tab[x][y] & FLAG_S) && (tab[x][y+1] & FLAG_O)))
				voisin[7]=x+P*y+P-1;
		}
		if (x<P-1){
			if (((tab[x][y] & FLAG_S) && (tab[x][y+1] & FLAG_E )) || ((tab[x][y] & FLAG_E) && (tab[x+1][y] & FLAG_S)))
				voisin[8]=x+P*y+P+1;
		}
	}

	voisin[4]=x+P*y;
	
	for (j=0; j<9; j++)
        {
                if (voisin[j]!=-1)
                {
                        x=tab[voisin[j]%P][voisin[j]/P];
                        i1=(voisin[j]%P); //coordonee colonne du noeud
                        j1=(voisin[j]/P); // coordonee ligne du noeud
        		affichage_texture(texture,window,renderer,x,i1,j1,taille_cell);
		}
        }
	free(voisin);
	
	SDL_Texture *texture_brouillard = load_texture_from_image("fog.png",renderer);
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
}


void afficherImageBrouillard(SDL_Renderer *renderer,SDL_Window *window,int **tab,int taille_cell,SDL_Texture* texture, int pos_x, int pos_y)
{
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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
	SDL_Texture *texture_brouillard = load_texture_from_image("fog.png",renderer);
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
}


void peindreMap(SDL_Texture * texture, SDL_Window* window ,SDL_Renderer *renderer, int noeuds, int taille_cell, int ** laby)
{
	//printf("peindre case %d %d %d \n",noeuds%P,noeuds/P,laby[noeuds%P][noeuds/P]);
        affichage_texture(texture,window, renderer, laby[noeuds%P][noeuds/P], noeuds%P, noeuds/P, taille_cell);
}

void point_minimap(SDL_Renderer * renderer, int taille_cell, int pos_x, int pos_y)
{
	SDL_Rect rectangle;
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	
	rectangle.x=pos_x;
	rectangle.y=pos_y;
	rectangle.h=rectangle.w=taille_cell/2;

	SDL_RenderFillRect(renderer, &rectangle);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
}

