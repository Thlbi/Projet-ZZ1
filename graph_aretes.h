#ifndef _gard_graph_aretes_
#define _gard_graph_aretes_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>
#include "partition.h"

typedef struct aretes
{
	int un;
	int deux;
	struct aretes * suiv;
}aretes_t;


typedef struct graph
{
	int noeuds;
	aretes_t * liste;
}graph_t;


graph_t * creer_couple(int n);
void remplir_couple(graph_t *);

void affiche_graph_couple(graph_t *,int);

void partition_connexe(partition_t *,graph_t *);

void affiche_graph2(graph_t *,partition_t *, int, int);

void ajouter_aretes(graph_t *, int, int);

aretes_t * liberer_aretes(aretes_t *);

int main();
#endif
