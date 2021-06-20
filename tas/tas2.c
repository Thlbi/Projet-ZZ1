#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

#define TAILLE 6

/*
 *On implémente le tas comme un tableau
 */
void init_tas_min(tas_t * tas,int valeur){
	int rang_val=tas->rang_dernier;
	int pere;

	tas->tab[rang_val]=valeur;
	tas->rang_dernier+=1;

	while ((rang_val>0) && (valeur < tas->tab[(rang_val-1)/2]))
	{
		pere=tas->tab[rang_val];
		tas->tab[rang_val]=tas->tab[(rang_val-1)/2];
		rang_val=(rang_val-1)/2;
		tas->tab[rang_val]=pere;
	}

/*	for (int i=0;i<tas->rang_dernier;i++){
		printf("%d \n",tas->tab[i]);
	}
*/
}


void percolation(tas_t * t,int rang){
	int valeur=t->tab[rang];
	int aux;
	int fin=1;
	
	while (fin)
     	{
		if (2*rang + 1<=(t->rang_dernier) && t->tab[2*rang +1]<=t->tab[2*rang +2] && t->tab[2*rang +1]<valeur){
			aux=t->tab[rang];
			t->tab[rang]=t->tab[2*rang +1];
			rang=2*rang +1;
			t->tab[rang]=aux;
		}
		else if (2*rang + 2<=(t->rang_dernier) && t->tab[2*rang +2]<t->tab[2*rang +1] && t->tab[2*rang +2]<valeur) 		
		{
			aux=t->tab[rang];
			t->tab[rang]=t->tab[2*rang +2];
			rang=2*rang +2;
			t->tab[rang]=aux;
		}
		else
			fin=0;
	}
}

/*  int k = noeud;
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
*/
void tri_par_tas(tas_t * t){
	
	while(t->rang_dernier>0)
	{
		int aux=t->tab[0];

		t->tab[0]=t->tab[t->rang_dernier-1];
		t->tab[t->rang_dernier-1]=aux;
		t->rang_dernier+=-1;
		percolation(t,0);
	}
	t->rang_dernier=t->taille;
}

	/*int i;

	for (i=taille/2;i>0;i--){
        	percolation(t,i,taille);
   	}
	for (i=taille;i>1;i--){
		//échanger tab[i] et tab[1]
       		percolation(t,1,i-1);
   	}
}
*/



void affichage(tas_t *tas){
	for (int i=0;i<tas->taille;i++)
		printf("%d  ",tas->tab[i]);
	printf("\n");
}


int main(){
	int taille=6;
	int valeur;

        tas_t * t=(tas_t *)malloc(sizeof(tas_t));

	if (t!=NULL){
		t->taille=taille;
		t->rang_dernier=0;
		t->tab=(int *)malloc(sizeof(int));

		if(t->tab!=NULL){
			for (int i=0;i<taille;i++){
				//printf("rentrer valeur\n");
				//scanf("%d %*c\n",&valeur);
				valeur= i+1;
				init_tas_min(t,valeur);
			}
			affichage(t);
			tri_par_tas(t);
			affichage(t);
		}
	}

	free(t->tab);
	free(t);

	return 0;
}
             

