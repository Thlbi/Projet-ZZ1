/* Tas.h 17 juin*/

#ifndef TAS_H
#define TAS_H



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tas{
	int taille_max;
	int * tab ;
	int taille;
} tas_t;

tas_t * initas(int taille);
void liberer_tas(tas_t *tas);
int ajouter(int x,tas_t* tas );
int retirer(tas_t * tas);
void perlocate_down(tas_t * tas,int i);
void tamiser(int* tas,int noeud,int n);
void triParTas(int* tas,int taille);

#endif