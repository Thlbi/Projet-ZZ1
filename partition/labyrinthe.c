#include <stdio.h>
#include "labyrinthe.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage_image.h"

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


/*
 *tableau contenant les valeurs déterminant quels sont les murs à créer
 */
int ** tableau_aretes(aretes_t *A){
	int ** tab=malloc(N*sizeof(int *));
	int x;

	if (!tab)
		exit(EXIT_FAILURE);

	for (int i=0;i<N;i++){
		tab[i]=malloc(P*sizeof(int ));
		for (int j=0;j<P;j++){
			tab[i][j]=0;
		}
	}
	while (A!=NULL){
		x=A->coord1;
		while ((A!=NULL) && (A->coord1==x)){
		       if (A->coord2==x+1){
			       tab[(int)x/P][x%P]+=4;
			       tab[(int)x/P][(x%P)+1]+=8;
		       	}
			else{
			       tab[(int)x/P][x%P]+=2;
			       tab[((int)x/P)+1][x%P]+=1;
			}
			A=A->suiv;
		}
	}
	//Nord=1,sud=2,est=4,ouest=8;
	return tab;
}


/*
 *Affichage du labyrinthe avec des dessins, mais intelligemment
 */
void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab,int taille_cell){
        int i1,j1,x,noeud=0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);

        for (int i=0;i<N;i++){
		for (int j=0;j<P;j++){
			x=tab[i][j];
                	i1=(noeud%P)+1;
                	j1=((int)noeud/P)+1;

			if (x%2!=1){
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,j1*taille_cell+50,(i1+1)*taille_cell+50,j1*taille_cell+50); //mur au nord
				}
			if ((x!=2) && (x!=3) && (x!=6) && (x!=7) && (x!=10) && (x!=11) && (x!=14) && (x!=15))
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,(j1+1)*taille_cell+50,(i1+1)*taille_cell+50,(j1+1)*taille_cell+50); //mur au sud
			if ((x!=4) && (x!=5) && (x!=6) && (x!=7) && (x!=12) && (x!=13) && (x!=14) && (x!=15)) 
				SDL_RenderDrawLine(renderer,(i1+1)*taille_cell+50,j1*taille_cell+50,(i1+1)*taille_cell+50,(j1+1)*taille_cell+50); //mur à l'est
			if (x<8)
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,j1*taille_cell+50,i1*taille_cell+50,(j1+1)*taille_cell+50); //mur à l'ouest
			
			noeud+=1;
		
		}
	}

        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
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


int ** labyrinthe_arbo(){
	partition_t *t=creer(TAILLE);
        int **tab;
	couple_t *c=init_couple();
        aretes_t *cour;
        aretes_t *A=NULL;
        aretes_t *nouv;
        int classe1,classe2;

        generer_couple_poids1(c,TAILLE);
   //   graph_couple(c);
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
     // graph_kruskal(A);
	tab=tableau_aretes(A);
	return tab;
}

