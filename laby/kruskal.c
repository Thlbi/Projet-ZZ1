#include "kruskal.h"

int ** tableau_ligne(graph_t * graph,int nb_aretes)
{
	int** tab=malloc(P*sizeof(int*));
	for (int i=0; i<P; i++)
		tab[i]=malloc(N*sizeof(int));	
	for (int i=0; i<P; i++)
		for (int j=0; j<N; j++)
			tab[i][j]=0;

	int diff;
	int x;
	int y;
	for (int i=0; i<nb_aretes; i++)
	{
		diff=abs(graph->liste[i].un - graph->liste[i].deux);
		x=graph->liste[i].un%P;
		y=graph->liste[i].un/P;
//		printf("sommet1: %d sommet2: %d x :%d y :%d diff :%d\n",graph->liste[i].un,graph->liste[i].deux,x,y,diff);
		if (diff==1){
			tab[x][y]+=4;
			tab[x+1][y]+=8;
		}
		else{ // ne marche pas c'est incomprehensibleif (diff==P)
			tab[x][y]+=2;
			tab[x][y+1]+=1;
		}
	}
/*
	for (int i=0; i<N; i++)
	{
		tab[i][0]-=8;
		tab[i][P-1]-=4;
		
	}
	for(int j=0; j<P; j++)
	{
			tab[0][j]-=1;
			tab[N-1][j]-=2;
	}*/
/*	for (int i=0; i<N; i++)
	{
		for (int j=0; j<P; j++)
			printf("%d ", tab[j][i]);
		printf("\n");
	}*/
		return tab;			
}

graph_t * kruskal(graph_t * graph,int noeuds, int nb_aretes,int * cours,double p)
{
	int c1;
	int c2;
   graph_t * A=creer_graph(noeuds,nb_aretes);
   partition_t * partA=creer(noeuds);

	for (int i=0; i<nb_aretes;i++)
	{
//	printf("dans le for\n");
//	printf("%d \n", graph->liste[i].un);
  // affiche_part(partA,noeuds);
		c1=recuperer_classe(graph->liste[i].un,partA);
		c2=recuperer_classe(graph->liste[i].deux, partA);
//	printf("%d %d\n",c1,c2);
		if (c1!=c2 || p<(double)rand()/(double)RAND_MAX)
		{
			A->liste[*cours]=graph->liste[i];
			fusion(A->liste[*cours].un,A->liste[*cours].deux,partA);
			*cours+=1;
		}
	}
	return A;
}	

graph_t * Fisher(graph_t * graph, int nb_aretes)
{
	aretes_t aux;
	int random;
	for (int i=nb_aretes-1; i>0; i--)
	{
		random=rand()%i;
//		printf("%d ",random);
		aux=graph->liste[random];
		graph->liste[random]=graph->liste[i];
		graph->liste[i]=aux;
	}
	return graph;
}

void generation(graph_t * graph)
{
	int c=0;
	for (int i=0; i<N*P; i++)
	{
		
		if ((i+1)%P)
		{
			graph->liste[c].un=i;
			graph->liste[c].deux=i+1;
			graph->liste[c].valuation=1;
			c++;
		}
		if (i/P<N-1)
		{
			graph->liste[c].un=i;
			graph->liste[c].deux=i+P;
			graph->liste[c].valuation=1;
			c++;
		}
	}
}
/*
int main()
{
   srand(time(0));
   int nb_aretes=10;
	int ligne=4;
	int colonne=5;
	int noeuds=ligne*colonne;
	int cours=0;
// int ** mat=NULL;
 //   mat= creer_mat(10);
   graph_t * graph=creer_graph(noeuds,100);
   partition_t * part=creer(noeuds);
	printf("%d \n", nb_aretes);
	nb_aretes=generation(graph,4,5);
	for (int i=0; i<nb_aretes; i++)
	{
		printf("un :%d ",graph->liste[i].un);
		printf("deux :%d ",graph->liste[i].deux);
		printf("val :%d ",graph->liste[i].valuation);
		printf("\n");
	}
	printf("\n");
	graph=Fisher(graph,nb_aretes);

  // int liste_part[noeuds];
 for (int i=0; i<nb_aretes; i++)
   {
      graph->liste[i].un=rand()%noeuds;
      graph->liste[i].deux=rand()%noeuds;
      graph->liste[i].valuation=rand()%noeuds;
   }

  	graph->liste=tri_par_tas(graph->liste,nb_aretes)->tab;

  
   affiche_graph_couple(graph,noeuds,nb_aretes);
//   affiche_part(part,noeuds);
	
	graph=kruskal(graph,noeuds,nb_aretes,&cours);
	
affiche_graph_couple(graph,noeuds,cours);
   
   
  system("dot -Tpng graph_part.dot -o graph_part.png");
   system("display graph_part.png &");
   
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
