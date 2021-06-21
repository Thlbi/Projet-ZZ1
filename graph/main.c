#include "main.h"

int main(){
    srand(1998);
    graph_t *graph=initgraph(TAILLE);
    printf("ok\n");
    generer_couple_2(graph);
    arete_t*A=graph->suiv;
    int **tab;
    graph=ordonner_Fisher(graph);
    
    A=kruskal(graph);
	//afficher_arete(A);

    tab=tableau_aretes(A);

    creation_SDL(tab);


    liberer(tab);
	return 0;
}