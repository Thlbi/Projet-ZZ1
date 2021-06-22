#include"labyrinthe.h"

//gcc *.c -o prog -Wall -Wextra $(sdl2-config --cflags --libs) -lSDL2_image


int **tableau_aretes(arete_t *A){
    int **tab=malloc(N*sizeof(int *));
	int x;
	int y;
    for(int i=0;i<N;i++){
        tab[i]=malloc(P*sizeof(int ));
        for (int j=0;j<P;j++){
            tab[i][j]=0;
        }
    }  
    //N=1 S=2 E=4 O=8
    while (A!=NULL){
		x=A->sommet1;
        while((A!=NULL)&&(A->sommet1==x)){
            y=A->sommet2;
			//printf("s1:%d,s2:%d\n",x,y);
            if(y==x+1){
                tab[x/P][x%P]+=4;
                tab[x/P][(x+1)%P]+=8;
            }
            else{
                tab[x/P][x%P]+=2;
                tab[x/P+1][x%P]+=1;
            }
        A=A->suiv;
        }
	}
    return tab;
}
void liberer(int **tab){
	for(int i=0;i<N;i++){
		free(tab[i]);
	}
	free(tab);
}

void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab,SDL_DisplayMode *screen){
	int j=0;
	int i=0;
	int x;
	int Taille_case= 50; 

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);

	for (i=0;i<N;i++){
		for (j=0;j<P;j++){
            x=tab[i][j];

            //cleaprintf("valeur:%d\n",x);
            if(!(x & FLAG_N)){
				SDL_RenderDrawLine(renderer,100+j*Taille_case,100+i*Taille_case,j*Taille_case+150,100+i*Taille_case); //x1 y1 x2 y2 
            }
            if((x & FLAG_S)!=2){
				SDL_RenderDrawLine(renderer,100+j*Taille_case,150+i*Taille_case,j*Taille_case+150,150+i*Taille_case);
            }            
            if((x & FLAG_E)!=4){
				SDL_RenderDrawLine(renderer,150+j*Taille_case,i*Taille_case+100,150+j*Taille_case,i*Taille_case+150);
            }
            if((x & FLAG_O)!=8){
				SDL_RenderDrawLine(renderer,100+j*50,i*50+100,100+j*50,150+i*50);
            }
			printf("\n");
		}
	}

    SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
}


void creation_SDL(int **tab){

	SDL_DisplayMode screen;
	SDL_Renderer * renderer;
	SDL_Window * window;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());       
    	exit(EXIT_FAILURE);
  	}




   	SDL_GetCurrentDisplayMode(0, &screen);

   	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h,SDL_WINDOW_RESIZABLE);
   	if (window == 0) {
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   	}
   	SDL_SetWindowTitle(window, "Labyrinthe");

   	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   	if (renderer == 0){
        	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
   	}
   
   afficherEcranIntelligemment(renderer,tab,&screen);
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
		//printf("generer couple\n");
		int x1;
		int x2;	
        int taille=graph->Nb_Noyau;
		for (int i=0;i<taille;i++){

			x1=1;//rand()%3
			x2=1;//rand()%3
			if ((x1) &&((i+1)/P==i/P)){
				arete_t *nouv=malloc(sizeof(arete_t));
                nouv->sommet1=i;
    			nouv->sommet2=i+1;
				nouv->poids=1;
				nouv->suiv=graph->suiv;
				graph->suiv=nouv;
				//printf("s1:%d,s2:%d\n",i,i+1);

            }
			if ( (x2) && (i+P<taille) ){
				arete_t *nouv=malloc(sizeof(arete_t));
                nouv->sommet1=i;
    			nouv->sommet2=i+N;
				nouv->poids=1;
				nouv->suiv=graph->suiv;
				graph->suiv=nouv;
				//printf("s1:%d,s2:%d\n",i,i+N);
			}
		}
	}








