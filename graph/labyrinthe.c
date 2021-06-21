#include"labyrinthe.h"








void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer) {   
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



void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab){
	int i1,j1,x,y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

	for (int i=0;i<=N;i++){
		for (int j=0;j<=P;j++){
            x=tab[i][j];
            
            if((x & FLAG_N)!=0){

            }
            





			SDL_SetRenderDrawColor(renderer,0,0,0,0);
			SDL_RenderDrawLine(renderer,i*100+100,j*100+100,N*100+100,j*100+100);
			SDL_RenderDrawLine(renderer,i*100+100,j*100+100,i*100+100,P*100+100);
		}
	}

	
	while (A!=NULL){
		x=A->coord1;
		y=A->coord2;

		j1=y%P;
		i1=(int)y/P;
		SDL_SetRenderDrawColor(renderer,255,255,255,0);

		if (x==y-1){
			SDL_RenderDrawLine(renderer,(i1+1)*100,(j1+1)*100,(i1+2)*100,(j1+1)*100);
		}
		else
			SDL_RenderDrawLine(renderer,(i1+1)*100,(j1+1)*100,(i1+1)*100,(j1+2)*100);
		
		A=A->suiv;
	}

        SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
}




void creation_SDL(arete_t *A){
   if (SDL_Init(SDL_INIT_VIDEO) == -1){
 	   fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	   exit(EXIT_FAILURE);
   }
   SDL_Window *window;
   int width = 1900;
   int height = 1000;
   
   window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_RESIZABLE);
   if (window == 0) {
 	   fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   }
   SDL_SetWindowTitle(window, "Labyrinthe");
   
   SDL_Renderer *renderer;
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   if (renderer == 0){
 	   fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   }
   afficherEcran(renderer, A);
}



int **tableau_aretes(arete_t *A){
    int **tab=malloc(N*sizeof(int *));
    for(int i=0;i<N;i++){
        tab[j]=malloc(P*sizeof(int ));
        for (int j=0;j<P;j++){
            tab[i][j]=0;
        }
    }  
    //N=1 S=2 E=4 O=8
    while (A!=NULL){
		x=A->sommet1;
        while((A!=NULL)&&(A->sommet1==x)){
            y=A->sommet2;
            if(y==x+1){
                tab[(int)x/P][x%P]+=4;
                tab[(int)x/P][(x+1)%P]+=8;
            }
            else{
                tab[(int)x/P][x%P]+=2;
                tab[(int)x/P+1][x%P]+=1;
            }
        A=A->suiv;
        }

    return tab;
}




graph_t * ordonner_Fisher(graph_t *c){
	graph_t *c_ordre=malloc(sizeof(graph_t));
    arete_t *cour=c->suiv;
    arete_t **prec;
	arete_t **prec_ordre=&c_ordre->suiv;
	int nb_arete=0;
	int iter;
	int random;

        c_ordre->Nb_Noyau=c->Nb_Noyau;
        c_ordre->suiv=NULL;

        while(cour!=NULL){
                nb_arete+=1;
		cour=cour->suiv;
	}
	while (nb_arete!=0){
		iter=0;
		random=rand()%nb_arete;
		nb_arete-=1;
		cour=c->suiv;
		prec=&c->suiv;

                while (iter!=random){
                        iter+=1;
			cour=cour->suiv;
			prec=&(*prec)->suiv;
		}
                *prec=cour->suiv;
		*prec_ordre=cour;
		(*prec_ordre)->suiv=NULL;
		prec_ordre=&(*prec_ordre)->suiv;
        }
        return (c_ordre);
}

void generer_couple_2(graph_t *graph){
		int x;	
        int taille=graph->Nb_Noyau;
        srand(time(0));
		for (int i=0;i<taille;i++){
			for (int j=0;j<taille;j++){
				x=rand()%3;
				if (x==1){
                    if((abs(i-j)==1)||(abs(i-j)%P)){
                    ajouter_arete(graph,i,j,1);
                    }
				}
			}
		}
}


int main(){
    graph_t *grap=initgraph(10);
    generer_couple_2(graph);
    ordonner_Fisher(graph);
    arete_t *A=kruskal(graph);
    creation_SDL(A);


}




