#ifndef _gard_kruskal_
#define _gard_kruskal_

#include "tas.h"
#include "graph_aretes_tab.h"

graph_t * kruskal(graph_t * graph,int noeuds, int nb_aretes,int * cours);

graph_t * Fisher(graph_t * graph, int nb_aretes);

int  generation(graph_t * graph, int n, int p);

int main();

#endif
