#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

#define TAILLE 6

/*
 *On implémente le tas comme un tableau
 */
void init_tas(tas_t * tas,int valeur){
	int * tab= tas->tab;
	tab[tas->rang_dernier]=valeur;
	tas->rang_dernier=1;
	//printf("%d\n",tab[tas->rang_dernier]);
}


void percolation(tas_t * t,int noeud,int n){
   //(* descend tab[nœud] à sa place, sans dépasser l'indice n *)
   int k = noeud;
   int j = 2*k;
   int * tab=t->tab;
   while (j <= n){
   	if ((j < n) && (tab[j] < tab[j+1])){
        	j = j+1;
      	}
      	if (tab[k] < tab[j]){
         	//échanger tab[k] et tab[j]
         	k = j;
         	j = 2*k;
	}
	else{
         	j = n+1;
	}
   }
}

void tri_par_tas(tas_t * t,int taille){
	int i;

	for (i=taille/2;i>0;i--){
        	percolation(t,i,taille);
   	}
	for (i=taille;i>1;i--){
		//échanger tab[i] et tab[1]
       		percolation(t,1,i-1);
   	}
}


int main(){
	int taille=6;
	int valeur;

        tas_t * t=(tas_t *)malloc(sizeof(tas_t));

	if (t!=NULL){
		t->taille=taille;
		t->rang_dernier=0;
		t->tab=(int *)malloc(sizeof(int));
		int * tab=t->tab;

		if(t->tab!=NULL){
			for (int i=0;i<taille;i++){
				//printf("rentrer valeur");
				valeur= i;
				init_tas(t,valeur);
			}
			tri_par_tas(t,taille);
		}
		for (int i=0;i<taille;i++){
			printf("%d\n",tab[i]);
		}
	}

	return 0;
}
             

