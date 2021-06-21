#ifndef _gard_kruskal_
#define _gard_kruskal_

#include "tas.h"
#include "graph_aretes_tab.h"

#define N 4
#define P 5

graph_t * kruskal(graph_t * graph,int noeuds, int nb_aretes,int * cours);

graph_t * Fisher(graph_t * graph, int nb_aretes);

int  generation(graph_t * graph, int n, int p);

int ** tableau_ligne(graph_t *,int );

#endif
