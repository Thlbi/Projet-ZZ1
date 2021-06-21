#include <stdio.h>
#include "labyrinthe.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


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


int max(int x,int y){
	int max;

	if (x>y)
		max=x;
	else
		max=y;
	return max;
}

/*
 *Affiche le labyrinthe arborescent avec des rectangles 
 */
void afficherEcran(SDL_Renderer *renderer,aretes_t *A,partition_t *t){
	int i1,j1,i2,j2,x,y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

	for (int i=0;i<=N;i++){
		for (int j=0;j<=P;j++){
			SDL_SetRenderDrawColor(renderer,0,0,0,0);
			SDL_RenderDrawLine(renderer,i*100+100,j*100+100,N*100+100,j*100+100);
			SDL_RenderDrawLine(renderer,i*100+100,j*100+100,i*100+100,P*100+100);
		}
	}

	
	while (A!=NULL){
		x=A->coord1;
		y=A->coord2;

		j1=x%P;
		i1=(int)x/P;
		j2=y%P;
		i2=(int)y/P;
		SDL_SetRenderDrawColor(renderer,255,0,255,0);

		if (x==y-1){
			printf("%d %d %d %d %d\n",x,i1,i2,j1,j2);
			SDL_RenderDrawLine(renderer,(i1+1)*100,(j1+1)*100,(i2+1)*100,(j2+1)*100);
		}
		else
			SDL_RenderDrawLine(renderer,(i1+1)*100,(j1+1)*100,(i2+1)*100,(j2+1)*100);
		
		A=A->suiv;
	}

        SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
}


/*
 *permet d'ordonner les aretes selon l'algorithme de Fisher-Yate
 */
couple_t * ordonner_Fisher(couple_t *c){
	couple_t *c_ordre=malloc(sizeof(couple_t));
        aretes_t *cour=c->suiv;
        aretes_t **prec;
	aretes_t **prec_ordre=&c_ordre->suiv;
	int nb_aretes=0;
	int iter;
	int random;

        c_ordre->nb_noeud=c->nb_noeud;
        c_ordre->suiv=NULL;

        while(cour!=NULL){
                nb_aretes+=1;
		cour=cour->suiv;
	}
	while (nb_aretes!=0){
		iter=0;
		random=rand()%nb_aretes;
		nb_aretes-=1;
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


void creation_SDL(aretes_t *A,partition_t *t){
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
   afficherEcran(renderer, A,t);
}


void labyrinthe_arbo(){
	partition_t *t=creer(TAILLE);
        couple_t *c=init_couple();
        aretes_t *cour;
        aretes_t *A=NULL;
        aretes_t *nouv;
        int classe1,classe2;

        generer_couple_poids1(c,TAILLE);
        graph_couple(c);
        c=ordonner_Fisher(c); //pour ordonner aléatoirement la forêt arborescente
        cour=c->suiv;


        while (cour!=NULL){
                classe1=recuperer_classe(t,cour->coord1,TAILLE);
                classe2=recuperer_classe(t,cour->coord2,TAILLE);

                if (classe1!=classe2){
			fusion(t,cour->coord1,cour->coord2,TAILLE);
                        nouv=allouer(cour->coord1,cour->coord2,cour->poids);
                        nouv->suiv=A;
                        A=nouv;
                }
                cour=cour->suiv;
        }
        graph_kruskal(A);
	creation_SDL(A,t);
}

