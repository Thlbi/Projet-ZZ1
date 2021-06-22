#ifndef _Tri_gard_
#define _Tri_gard_

#include<stdio.h>
#include<stdlib.h>

#include "graph_aretes_tab.h"


typedef aretes_t typetas;
typedef struct tas
{
	int taille_max;
	typetas * tab;
	int taille;
}tas_t;

tas_t * init_tas(int t);
void liberer(tas_t* tas);
tas_t * ajouter_tas_min(tas_t * tas,typetas x);
void percolation_bas_tas_min(tas_t *tas, int indice);
void affichage(tas_t* tas);

#endif
