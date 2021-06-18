#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partition_a.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

partition_t * creer(int taille){
	partition_t  *t;
	int i;

	t=(partition_t *)malloc(taille*sizeof(partition_t ));

	if (t!=NULL){
		for (i=0;i<taille;i++)
		{
			t[i].val=i;
			t[i].hauteur=1;
			t[i].par=i;
		}
	}
	
	return t;
}


int recuperer_classe(partition_t * t,int nombre,int taille){
	int i=0;
	int val=-1;

	while ((i<taille) && (t[i].val!=nombre))
	{
		i=i+1;
	}

	if (i<taille){
		while (t[i].par!=i){
			i=t[i].par;
		}
		val=i;
	}
	return val;
}


void fusion(partition_t * t ,int x,int y,int taille){
	int classe1=recuperer_classe(t,x,taille);
	int classe2=recuperer_classe(t,y,taille);

	if (classe1!=classe2){
		if (t[classe1].hauteur==t[classe2].hauteur){
			t[classe1].par=t[classe2].val;
			t[classe2].hauteur+=1;
		}
		else{
			if (t[classe1].hauteur<t[classe2].hauteur)
				t[classe1].par=t[classe2].val;
			else
				t[classe2].par=t[classe1].val;
		}
	}
}


void lister_classe(partition_t * t,int classe,int taille){
	int x;

	for (int i=0;i<taille;i++){
		x=recuperer_classe(t,i,taille);
		if (x==classe){
			printf("%d \n",t[i].val);
		}
	}
}

int graph(partition_t *t,int taille){
	
	FILE *fichier;
        fichier = fopen("graph.dot","w");
        if (fichier==NULL){
                printf("erreur d'ouverture du fichier");
                exit(EXIT_FAILURE);
        }
	fprintf(fichier,"digraph Nom{\n");
	for (int i=0;i<taille;i++){
		fprintf(fichier,"%d",i);
		fprintf(fichier,"->");
		fprintf(fichier,"%d",t[i].par);
		fprintf(fichier,";\n");
	}
	fprintf(fichier,"}");
	fclose(fichier);
	int erreur=system("dot -Tpng graph.dot -o graph.png");

	return erreur;

}

/*
void graph(partition_t *t,int taille){
	Agraph_t *graphe;
	Agnode_t 

	File *fichier;
	fichier = fopen("demo.dot","w");
	if (fichier==NULL){
		printf("erreur d'ouverture du fichier");
		exit(EXIT_FAILURE);
	}

	GVC_t *graph_context;
	graph_context=gvContext();
	if (graph_context==NULL){
		printf("erreur contexte")	
		exit(EXIT_FAILURE);
	}
	graphe= agopen("Graphe",Agdirected,0);

	noeud_1=agnode(graphe,"1",1);
	noeud_2=agnode(graphe,"2",1);
	noeud_3=agnode(graphe,"3",1);
	noeud_4=agnode(graphe,"4",1);
	ar_1=agedge(graphe,noeud_1,noeud_2,NULL,1);
	ar_2=agedge(graphe,noeud_1,noeud_4,NULL,1);
	ar_3=agedge(graphe,noeud_2,noeud_4,NULL,1);
	ar_4=agedge(graphe,noeud_3,noeud_2,NULL,1);
	ar_5=agedge(graphe,noeud_3,noeud_4,NULL,1);

	agwrite(graphe,graphe.png);
	gvLayout(graph_context,mon_graphe,"dot");
	gvRender(graph_context,mon_graphe,"dot",fichier);

	system("dot -Tpng demo.dot -o graph.png");
	if (sys!=0){
		printf("erreur sys");
	}
	gvFreeLayout(graph_context,graphe);
	agclose(graphe);
	fclose(fichier);
}
*/

void lister_partition(partition_t * t,int taille){
	for (int i=0;i<taille;i++){
		if (t[i].par==i)
			printf("%d \n",i);
	}
}


int main(){
	int taille=10;
	partition_t * t=creer(taille);
	
	printf("%d \n",recuperer_classe(t,5,taille));
	fusion(t,6,5,taille);
	printf("%d \n",recuperer_classe(t,5,taille));
	lister_classe(t,3,taille);
	lister_partition(t,taille);
	int erreur=graph(t,taille);

	if (erreur=0)
		printf("erreur");

	return 0;
}
