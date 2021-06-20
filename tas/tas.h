#ifndef _Tri_gard_
#define _Tri_gard_

#include<stdio.h>
#include<stdlib.h>
typedef struct tas
{
	int taille_max;
	int * tab;
	int taille;
}tas_t;

tas_t * init_tas(int t);
void liberer(tas_t* tas);
tas_t * ajouter_tas_max(tas_t * tas,int x);
tas_t * ajouter_tas_min(tas_t * tas,int x);
tas_t * percolation_bas_tas_min(tas_t *tas, int indice);
tas_t * construire(tas_t * tas, int *t, int pos);
tas_t* tri_par_tas(int *t ,int n);
void affichage(tas_t* tas);
int main();


#endif
