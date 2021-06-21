#include "kruskal.h"


int main()
{
   int noeuds=10;
   srand(time(0));
   int nb_aretes=10;
	int c1;
	int c2;
// int ** mat=NULL;
 //   mat= creer_mat(10);
   graph_t * graph=creer_graph(noeuds,nb_aretes);
   graph_t * A=creer_graph(noeuds,nb_aretes);
   partition_t * part=creer(noeuds);
   partition_t * partA=creer(noeuds);
  // int liste_part[noeuds];

   for (int i=0; i<nb_aretes; i++)
   {
      graph->liste[i].un=rand()%noeuds;
      graph->liste[i].deux=rand()%noeuds;
      graph->liste[i].valuation=rand()%noeuds;
   }
   
   affiche_graph_couple(graph,noeuds,nb_aretes);
   affiche_part(part,noeuds);
	graph->liste=tri_par_tas(graph->liste,nb_aretes)->tab;
	int cours=0;
	for (int i=0; i<nb_aretes;i++)
	{
		c1=recuperer_classe(graph->liste[i].un,partA);
		c2=recuperer_classe(graph->liste[i].deux, partA);
		if (c1!=c2)
		{
			A->liste[cours]=graph->liste[i];
			fusion(A->liste[cours].un,A->liste[cours].deux,partA);
			cours+=1;
		}
	}
	
   affiche_graph_couple(A,noeuds,cours);
   
   
   system("dot -Tpng graph_part.dot -o graph_part.png");
   system("display graph_part.png &");
   
/*   nbpart=lister_partition(part,10,liste_part); 
   for (int i=0;i<nbpart;i++)
   {
      affiche_graph2(graph,part,liste_part[i], noeuds,nb_aretes);
   }
*/
   free(graph->liste);  
   free(graph);
	free(A->liste);
	free(A);
   free(part);
   return 0;
}
