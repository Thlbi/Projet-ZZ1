#include "graph_aretes_tab.h"

int plusgrand(aretes_t a, aretes_t b)
{
	return a.valuation>b.valuation;
}

graph_t * creer_graph(int n, int nb_aretes)
{
	graph_t* graph= malloc(sizeof(graph_t));
	graph->liste= malloc(nb_aretes*sizeof(aretes_t));
	graph->noeuds=n;
	graph->nb_aretes=nb_aretes;
	return graph;
}

void affiche_graph_couple(graph_t * graph,int taille, int nb_aretes)
{
	FILE *fichier;
	fichier=fopen("graph1.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");

	for (int i=0; i<taille; i++)
	{
		fprintf(fichier,"%d",i);
		fprintf(fichier,";");
	}
		
	
	for (int j=0; j<nb_aretes; j++)
	{
		fprintf(fichier,"%d",graph->liste[j].un);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",graph->liste[j].deux);
		fprintf(fichier," [label=%d]",graph->liste[j].valuation);
		fprintf(fichier,";");
	}

	fprintf(fichier, "}");
	fclose(fichier);
	system("dot -Tpng graph1.dot -o graph1.png");
	system("display graph1.png &");
	
}

void affiche_graph2(graph_t * graph, partition_t * part, int classe,int taille,int nb_aretes )
{
	FILE *fichier;
	fichier=fopen("graph_co.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	int classe_cours;
	for (int i=0; i<taille; i++)
	{
		classe_cours=recuperer_classe(i, part);
		if (classe==classe_cours)
		{
			fprintf(fichier,"%d",i);
			fprintf(fichier,";");
		}
	}
		
	for (int j=0; j<nb_aretes;j++)
	{
		classe_cours=recuperer_classe(graph->liste[j].un, part);
		if (classe==classe_cours)
		{
			fprintf(fichier,"%d",graph->liste[j].un);
			fprintf(fichier,"--");
			fprintf(fichier,"%d",graph->liste[j].deux);
			fprintf(fichier," [label=%d]",graph->liste[j].valuation);
			fprintf(fichier,";");
		}
	}

	fprintf(fichier, "}");
	fclose(fichier);
	system("dot -Tpng graph_co.dot -o graph_co.png");
	system("display graph_co.png ");
	
}

void partition_connexe(partition_t* part, graph_t * graph,int nb_aretes)
{
	for (int j=0; j<nb_aretes;j++)
	{
		fusion(graph->liste[j].un,graph->liste[j].deux,part);
	}
}
/*
int main()
{
	int noeuds=10;
  	srand(time(0));
	int nb_aretes=5;
//	int ** mat=NULL;
 // 	mat= creer_mat(10);
	graph_t * graph=creer_graph(noeuds,nb_aretes);
	partition_t * part=creer(noeuds);
  	int liste_part[noeuds];
  	int nbpart;
		for (int i=0; i<10 ;i++)
	{
		for (int j=0; j<i; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}

	for (int i=0; i<nb_aretes; i++)
	{
		graph->liste[i].un=rand()%noeuds;
		graph->liste[i].deux=rand()%noeuds;
		graph->liste[i].valuation=rand()%noeuds;
	}
	
	affiche_graph_couple(graph,noeuds,nb_aretes);
  	partition_connexe(part,graph,nb_aretes);
  	affiche_part(part,noeuds);
	
	
  	system("dot -Tpng graph_part.dot -o graph_part.png");
  	nbpart=system("display graph_part.png &");
	
  	nbpart=lister_partition(part,10,liste_part);	
	for (int i=0;i<nbpart;i++)
	{
		affiche_graph2(graph,part,liste_part[i], noeuds,nb_aretes);
	}

	free(graph->liste);	
	free(graph);
	free(part);
	return 0;
}*/			
