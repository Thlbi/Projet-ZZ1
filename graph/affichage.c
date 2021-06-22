#include "affichage.h"




void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer){
  char msg_formated[255];
  int l;

  if (!ok) {                             
         strncpy(msg_formated, msg, 250);
         l = strlen(msg_formated);           
         strcpy(msg_formated + l, " : %s\n");

         SDL_Log(msg_formated, SDL_GetError());
  }

  if (renderer != NULL) SDL_DestroyRenderer(renderer);
  if (window != NULL)   SDL_DestroyWindow(window);

  SDL_Quit();

  if (!ok) {                
         exit(EXIT_FAILURE);
  }
}

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}



void afficherEcranIntelligemment_2(SDL_Texture* texture_lab,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int **tab){
	int j=0;
	int i=0;
	int x;
    int zoom=1;
	int Taille_case= 50; 
    SDL_Rect source = {0},destination = {0};                 
             
    SDL_QueryTexture(texture_lab, NULL, NULL,&source.w, &source.h);

    int nb_images = 8*6;
    int k=0;                          
    int offset_x = source.w/8;
    int offset_y = source.h/6;   
    SDL_Rect state[TAILLE];

    destination.w = offset_x * zoom;  //taille image largeur
    destination.h = offset_y * zoom; //taille image hauteur
    destination.x=50;             //position image x
    destination.y=50;             //position image y



	for (i=0;i<N;i++){
		for (j=0;j<P;j++){
            x=15-tab[i][j];
            switch(x){
                case 0:
                    state[k].x=6*offset_x;
                    state[k].y=5*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 1:
                    state[k].x=2*offset_x;
                    state[k].y=5*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 2:
                    state[k].x=4*offset_x;
                    state[k].y=1*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 3:
                    state[k].x=0*offset_x;
                    state[k].y=1*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 4:
                    state[k].x=3*offset_x;
                    state[k].y=3*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 5:
                    state[k].x=2*offset_x;
                    state[k].y=3*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 6:
                    state[k].x=4*offset_x;
                    state[k].y=0*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 7:
                    state[k].x=2*offset_x;
                    state[k].y=0*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 8:
                    state[k].x=4*offset_x;
                    state[k].y=4*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 9:
                    state[k].x=2*offset_x;
                    state[k].y=4*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 10:
                    state[k].x=6*offset_x;
                    state[k].y=0*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 11:
                    state[k].x=5*offset_x;
                    state[k].y=0*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 12:
                    state[k].x=6*offset_x;
                    state[k].y=1*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 13:
                    state[k].x=5*offset_x;
                    state[k].y=1*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 14:
                    state[k].x=1*offset_x;
                    state[k].y=0*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                case 15:
                    state[k].x=7*offset_x;
                    state[k].y=5*offset_y;
                    state[k].w=offset_x;
                    state[k].h = offset_y;
                break;
                default:
                break;              
            }
            k=k+1; 
		}
	}

    SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    for(i=0;i<TAILLE;++i){
        destination.x=50+(offset_x*zoom)*(i%P); 
        destination.y=50+(offset_y*zoom)*(i/N);
        SDL_RenderCopy(renderer,texture_lab, &state[i], &destination);
    } 
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}