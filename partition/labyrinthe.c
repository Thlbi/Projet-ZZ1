#include<stdio.h>
#include"labyrinthe.h"
#include <stdlib.h>

couple_t * ordonner_Fisher(couple_t *c){
	couple_t *c_ordre=malloc(sizeof(couple_t));
        aretes_t *cour=c->suiv;
        aretes_t **prec;
	aretes_t **prec_ordre=&c_ordre->suiv;
	int nb_aretes=0;
	int iter=0,iter2;
	int random;

        c_ordre->nb_noeud=c->nb_noeud;
        c_ordre->suiv=NULL;

        while(cour!=NULL){
                nb_aretes+=1;
		cour=cour->suiv;
	}
	while (iter!=nb_aretes){
		iter+=1;
		iter2=0;
		random=rand()%nb_aretes;
		cour=c->suiv;
		prec=&c->suiv;

                while (iter2!=random){
                        iter2+=1;
			cour=cour->suiv;
			prec=&(*prec)->suiv;
		}
                *prec=cour->suiv;
		if (cour!=NULL)
			free(cour);
		*prec_ordre=allouer(cour->coord1,cour->coord2,cour->poids);
		(*prec_ordre)->suiv=NULL;
		prec_ordre=&(*prec_ordre)->suiv;
        }
        return (c_ordre);
}


void labyrinthe_arbo(int taille){
	partition_t *t=creer(taille);
        couple_t *c=init_couple();
        aretes_t *cour;
        aretes_t *A=NULL;
        aretes_t *nouv;
        int classe1,classe2;

        generer_couple(c,taille);
        graph_couple(c);
        c=ordonner_Fisher(c); //pour ordonner aléatoirement la forêt arborescente
        cour=c->suiv;


        while (cour!=NULL){
                classe1=recuperer_classe(t,cour->coord1,taille);
                classe2=recuperer_classe(t,cour->coord2,taille);

                if (classe1!=classe2){
			fusion(t,cour->coord1,cour->coord2,taille);
                        nouv=allouer(cour->coord1,cour->coord2,cour->poids);
                        nouv->suiv=A;
                        A=nouv;
                }
                cour=cour->suiv;
        }
        graph_kruskal(A);
}

