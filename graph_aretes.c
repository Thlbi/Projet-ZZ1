#include "graph_aretes.h"

graph_t * creer_graph(int n)
{
	graph_t* graph= malloc(sizeof(graph_t));
	graph->liste=NULL;
	graph->noeuds=n;
	return graph;
}

void ajouter_aretes(graph_t *graph, int un, int deux, int valuation)
{
	aretes_t * cours=graph->liste;
	aretes_t * nouv= malloc(sizeof(aretes_t));
	nouv->un=un;
	nouv->deux=deux;
	nouv->suiv=cours;
	nouv->valuation=valuation;
	graph->liste=nouv;
	
}

aretes_t* liberer_aretes(aretes_t	* aretes)
{
	if (aretes)
	{
		aretes_t	* sauv=aretes->suiv;
		free(aretes);
		return liberer_aretes(sauv);
	}
	else
		return aretes;
}
	
void affiche_graph_couple(graph_t * graph,int taille)
{
	FILE *fichier;
	fichier=fopen("graph1.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");

	aretes_t * cours=graph->liste;
	for (int i=0; i<taille; i++)
	{
		fprintf(fichier,"%d",i);
		fprintf(fichier,";");
	}
		
	while (cours)
	{
		fprintf(fichier,"%d",cours->un);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",cours->deux);
			fprintf(fichier," [label=%d]",cours->valuation);
		fprintf(fichier,";");
		cours=cours->suiv;
	}

	fprintf(fichier, "}");
	fclose(fichier);
	system("dot -Tpng graph1.dot -o graph1.png");
	system("display graph1.png &");
	
}

void affiche_graph2(graph_t * graph, partition_t * part, int classe,int taille )
{
	FILE *fichier;
	fichier=fopen("graph_co.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	int classe_cours;
	aretes_t * cours=graph->liste;
	for (int i=0; i<taille; i++)
	{
		classe_cours=recuperer_classe(i, part);
		if (classe==classe_cours)
		{
			fprintf(fichier,"%d",i);
			fprintf(fichier,";");
		}
	}
		
	while (cours)
	{
		classe_cours=recuperer_classe(cours->un, part);
		if (classe==classe_cours)
		{
			fprintf(fichier,"%d",cours->un);
			fprintf(fichier,"--");
			fprintf(fichier,"%d",cours->deux);
			fprintf(fichier," [label=%d]",cours->valuation);
			fprintf(fichier,";");
		}
		cours=cours->suiv;
	}

	fprintf(fichier, "}");
	fclose(fichier);
	system("dot -Tpng graph_co.dot -o graph_co.png");
	system("display graph_co.png ");
	
}

void partition_connexe(partition_t* part, graph_t * graph)
{
	aretes_t * cours=graph->liste;
	while (cours)
	{
		fusion(cours->un,cours->deux,part);
		cours=cours->suiv;
	}
}

int main()
{
	int noeuds=10;
  	srand(time(0));
//	int ** mat=NULL;
 // 	mat= creer_mat(10);
	graph_t * graph=creer_graph(noeuds);
	partition_t * part=creer(noeuds);
  	int liste_part[noeuds];
  	int nbpart;
/*		for (int i=0; i<10 ;i++)
	{
		for (int j=0; j<i; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
*/
	for (int i=0; i<10; i++)
		ajouter_aretes(graph,1+rand()%9,1+ rand()%9,1 +rand()%20);
	
	affiche_graph_couple(graph,noeuds);
  	partition_connexe(part,graph);
  	affiche_part(part,noeuds);
	
	
  	system("dot -Tpng graph_part.dot -o graph_part.png");
  	nbpart=system("display graph_part.png &");
	
  	nbpart=lister_partition(part,10,liste_part);	
	for (int i=0;i<nbpart;i++)
	{
		affiche_graph2(graph,part,liste_part[i], noeuds);
	}
	
	liberer_aretes (graph->liste);
	free(graph);
	free(part);
	return 0;
}			
