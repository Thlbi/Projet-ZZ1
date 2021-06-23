#ifndef _gard_kruskal_
#define _gard_kruskal_

#include "tas.h"
#include "graph_aretes_tab.h"

#define N 30
#define P 45
#define TAILLE (N*P)
#define ND_DEP 25
#define ND_ARRIVEE 0
graph_t * kruskal(graph_t * graph,int noeuds, int nb_aretes,int * cours,double p);

graph_t * Fisher(graph_t * graph, int nb_aretes);

void  generation(graph_t * graph);

int ** tableau_ligne(graph_t *,int );

#endif
