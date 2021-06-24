#ifndef _gard_kruskal_
#define _gard_kruskal_

#include "tas.h"
#include "graph_aretes_tab.h"

#define N 93
#define P 95

graph_t * kruskal(graph_t * graph,int noeuds, int nb_aretes,int * cours,double p);

graph_t * Fisher(graph_t * graph, int nb_aretes);

void  generation(graph_t * graph);

int ** tableau_ligne(graph_t *,int );

#endif
