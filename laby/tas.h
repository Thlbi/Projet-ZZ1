#ifndef _Tri_gard_
#define _Tri_gard_

#include<stdio.h>
#include<stdlib.h>

#include "graph_aretes_tab.h"

typedef struct tri{
	int noeud;
	int distance;
}tri_t;

typedef struct tab_tas{
	int distance;
	int indice_noeud;
} tab_tas_t;

typedef  tri_t typetas;
typedef struct tas
{
	int taille_max;
	typetas * tab;
	int taille;
}tas_t;

tas_t * init_tas(int t);
void liberer(tas_t* tas);
void ajouter_tas_min(tas_t * tas,int noeud,int distance);
void percolation_bas_tas_min(tas_t *tas, int indice);

#endif
