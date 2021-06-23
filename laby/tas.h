#ifndef _Tri_gard_
#define _Tri_gard_

#include<stdio.h>
#include<stdlib.h>

typedef struct p {
	int val;
	int poids;
}poids_t;

typedef poids_t typetas;
typedef struct tas
{
	int taille_max;
	typetas * tab;
	int taille;
}tas_t;

tas_t * init_tas(int t);
void liberer(tas_t* tas);
tas_t * ajouter_tas_max(tas_t * tas,typetas x);
tas_t * ajouter_tas_min(tas_t * tas,typetas x,int * indice_valeur);
tas_t *  percolation_haut_min(tas_t *, int rang);
tas_t * percolation_bas_tas_min(tas_t *tas, int indice,int * indice_valeur);
tas_t * percolation_bas_tas_max(tas_t *tas, int indice);
tas_t * construire_tas_min(tas_t * tas, typetas *t, int pos);
tas_t * construir_tas_max(tas_t * tas, typetas *t, int pos);
tas_t* tri_par_tas(typetas *t ,int n);
int  plusgrand(typetas,typetas);
/*void affichage(tas_t* tas);*/

#endif
