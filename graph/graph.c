#include "graph.h"
#include "union.h"
graph_t *  initgraph(int noyau){
    graph_t* graph=malloc(sizeof(graph_t));
    graph->Nb_Noyau=noyau;

    return graph;
}


void ajouter_arete(graph_t*graph,int sommet1,int sommet2){
    arete_t *arete_nouv=malloc(sizeof(arete_t));
    
    arete_nouv->sommet1=sommet1;
    arete_nouv->sommet2=sommet2;
    arete_nouv->suiv=graph->liste;
    graph->liste=arete_nouv;   
}



void afficher_graph(graph_t*graph){
	FILE *fichier;
    arete_t *arete=graph->liste;
	fichier=fopen("graph.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	for (int i=0; i<graph->Nb_Noyau ;i++){
        fprintf(fichier,"%d",i);
		fprintf(fichier,";");
    }
	
    while(arete->suiv!=NULL)
    {   
		fprintf(fichier,"%d",arete->sommet1);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",arete->sommet2);
        fprintf(fichier,"[label=");
		fprintf(fichier,"%d",arete->poids);
		fprintf(fichier,"];\n");
        arete=arete->suiv;
	}
	fprintf(fichier, "}");
	fclose(fichier);
    system("dot -Tpng graph.dot -o graph.png");
	system("display graph.png ");
}




void generer_couple(graph_t *graph){
		int x;	
        int taille=graph->Nb_Noyau;
        srand(time(0));
		for (int i=0;i<taille;i++){
			for (int j=i+1;j<taille;j++){
				x=rand()%3;
				if (x==1){
					arete_t *nouv=malloc(sizeof(arete_t));
					nouv->sommet1=i;
					nouv->sommet2=j;
					nouv->poids=rand()%90;
					nouv->suiv=graph->liste;
					graph->liste=nouv;
				}
			}
		}
}



void kruskal(graph_t *graph)

int main(){
    graph_t *graph=initgraph(10);

    generer_couple(graph);
   
    afficher_graph(graph);

    return 0;
}