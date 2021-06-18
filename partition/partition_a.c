#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partition_a.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <time.h>

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


void fusion_mat(int ** mat,partition_t * t,int taille){
	for (int i=0;i<taille;i++){
		for (int j=i+1;j<taille;j++){
			if (mat[i][j]==1)
				fusion(t,i,j,taille);
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


/*
 *afficher le graph à partir de la matrice d'adjacence
 */
int graph_mat(int ** mat,int taille){
	
	FILE *fichier;
        fichier = fopen("graph.dot","w");
        if (fichier==NULL){
                printf("erreur d'ouverture du fichier");
                exit(EXIT_FAILURE);
        }
	fprintf(fichier,"graph Nom{\n");
	for (int i=0;i<taille;i++){
		for (int j=i;j<taille;j++){
			if (mat[i][j]==1){
				fprintf(fichier,"%d",i);
				fprintf(fichier,"--");
				fprintf(fichier,"%d",j);
				fprintf(fichier,";\n");
			}
			if (i==j){
				fprintf(fichier,"%d",i);
				fprintf(fichier,";\n");
			}
		}
	}
	fprintf(fichier,"}");
	fclose(fichier);
	int erreur=system("dot -Tpng graph.dot -o graph.png");

	return erreur;
}


void graph_connexes(int ** mat,int taille){
	
	FILE *fichier;
	char chaine[20];
	
	for (int i=0;i<taille;i++){
        	sprintf(chaine,"%d.dot",i);
		fichier = fopen(chaine,"w");
        	if (fichier==NULL){
                	printf("erreur d'ouverture du fichier");
                	exit(EXIT_FAILURE);
        	}
		fprintf(fichier,"graph Nom");
		fprintf(fichier,"%d",i);
		fprintf(fichier,"{\n");

		for (int j=i;j<taille;j++){
			if ((mat[i][j]==1)||(i==j)){
				fprintf(fichier,"%d",i);
				fprintf(fichier,"--");
				fprintf(fichier,"%d",j);
				fprintf(fichier,";\n");
			}
		}
		fprintf(fichier,"}\n");
		fclose(fichier);
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


int ** creer_mat(int nb_noeuds){
	int ** mat=(int **)malloc(nb_noeuds*sizeof(int *));
	
	if (mat==NULL){
		printf("erreur matrice");
		exit(EXIT_FAILURE);
	}
	for (int i=0;i<nb_noeuds;i++){
		mat[i]=(int*)malloc(nb_noeuds*sizeof(int));
		if (mat[i]==NULL){
			printf("erreur matrice");
			exit(EXIT_FAILURE);
		}
	}
	
	return mat;
}


void generation_mat(int **mat,int taille){
	for (int i=0;i<taille;i++){
		for (int j=0;j<taille;j++){
			if (j>i)
				mat[i][j]=rand()%8;
			else
				mat[i][j]=0;
		}
	}
}


void lister_partition(partition_t * t,int taille){
	for (int i=0;i<taille;i++){
		if (t[i].par==i)
			printf("%d \n",i);
	}
}


int main(){
	srand(time(0));
	int taille=10;
	partition_t * t=creer(taille);
	int ** mat=creer_mat(taille);
	generation_mat(mat,taille);
	int erreur=0;

	/*
	fusion(t,6,5,taille);
	lister_classe(t,3,taille);
	lister_partition(t,taille);
	*/

	//fusion_mat(mat,t,taille);
	//erreur=graph_mat(mat,taille);
	//erreur=graph(t,taille);
	graph_connexes(mat,taille);	

	if (erreur)
		printf("erreur\n");

	return 0;
}
