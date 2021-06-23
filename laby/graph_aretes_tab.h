#ifndef _gard_graph_aretes_tab_
#define _gard_graph_aretes_tab_

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
	int valuation;
	int etiqdji;
}aretes_t;


typedef struct graph
{
	int noeuds;
	int nb_aretes;
	aretes_t * liste;
}graph_t;

/*int plusgrand(aretes_t, aretes_t);*/

graph_t * creer_graph(int n,int);

void remplir_couple(graph_t *);

void affiche_graph_couple(graph_t *,int,int);

void partition_connexe(partition_t *,graph_t *,int);

void affiche_graph2(graph_t *,partition_t *, int, int,int);

#endif
