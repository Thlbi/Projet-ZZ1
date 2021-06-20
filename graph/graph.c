#include "graphe.h"


graph_t *initgraph(int noyau){
    graph_t* graph=malloc(sizeof(graph_t));
    graph->Nb_Noyau=noyau;
    return graph;
}


void ajouter_arrete(graph_t*graph,int sommet1,int sommet2){
    arrete_t *arrete_nouv=malloc(sizeof(arrete_t));
    
    arrete_nouv->sommet1=sommet1;
    arrete_nouv->sommet2=sommet2;
    arrete_nouv->suiv=graph->liste;
    graph->liste=arrete_nouv;   
}


void afficher_graph(graph_t*graph){
	FILE *fichier;
    arrete_t *arrete=graph->liste;
	fichier=fopen("graph.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	for (int i=0; i<graph->Nb_Noyau ;i++){
        fprintf(fichier,"%d",i);
		fprintf(fichier,";");
    }
	
    while(arrete->suiv!=NULL)
    {   
		fprintf(fichier,"%d",arrete->sommet1);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",arrete->sommet2);
		fprintf(fichier,";");
        arrete=arrete->suiv;
	}
	fprintf(fichier, "}");
	fclose(fichier);
    system("dot -Tpng graph.dot -o graph.png");
	system("display graph.png ");
}






int main(){
    graph_t *graph=initgraph(10);

    ajouter_arrete(graph,1,2);
    ajouter_arrete(graph,2,3);
    ajouter_arrete(graph,4,5);
    ajouter_arrete(graph,5,3);
    ajouter_arrete(graph,6,7);
    ajouter_arrete(graph,7,8);

    afficher_graph(graph);

    return 0;