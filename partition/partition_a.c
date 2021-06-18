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

void fusion_couple(couple_t * c,partition_t *t,int taille){
	aretes_t *cour=c->suiv;
	
	while (cour!=NULL){
		fusion(t,cour->coord1,cour->coord2,taille);
		cour=cour->suiv;
	}
}

/*
 *la fontion nous renvoie la quantité de population dans la classe
 */
int lister_classe(partition_t * t,int classe,int taille,int *tab){
	int x;
	int j=0;

	for (int i=0;i<taille;i++){
		x=recuperer_classe(t,i,taille);
		if (x==classe){
			tab[j]=i; //tableau contenant les indices de la classe
			j=j+1;
		}
	}
	return j; //le cardinal de notre classe
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
	system("display graph.png ");

	return erreur;
}


/*
 *permet de renvoyer les différentes parties connexes
 */
void graph_connexes(partition_t *t,int taille){
	
	FILE *fichier;
	int tab[taille];
	int j;
	
	for (int i=0;i<taille;i++){
		if (t[i].par==i){
			fichier = fopen("graph.dot","w");
        		if (fichier==NULL){
      	        	  	printf("erreur d'ouverture du fichier");
	        	       	exit(EXIT_FAILURE);
        		}
			fprintf(fichier,"graph Nom");
			fprintf(fichier,"%d",i);
			fprintf(fichier,"{\n");
			j=lister_classe(t,i,taille,tab);
			for (int k=0;k<j;k++){
					fprintf(fichier,"%d",i);
					fprintf(fichier,"--");
					fprintf(fichier,"%d",tab[k]);
					fprintf(fichier,";\n");
			}
		fprintf(fichier,"}\n");
		fclose(fichier);
		system("dot -Tpng graph.dot -o graph.png");
		system("display graph.png ");
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
	system("display graph.png ");
	
	return erreur;

}


int graph_couple(couple_t *c){
	
	aretes_t *cour=c->suiv;

	FILE *fichier;
        fichier = fopen("graph.dot","w");
        if (fichier==NULL){
                printf("erreur d'ouverture du fichier");
                exit(EXIT_FAILURE);
        }
	fprintf(fichier,"graph Nom{\n");
	while (cour!=NULL){
		fprintf(fichier,"%d",cour->coord1);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",cour->coord2);
		fprintf(fichier,";\n");
		cour=cour->suiv;
	}
	fprintf(fichier,"}");
	fclose(fichier);
	int erreur=system("dot -Tpng graph.dot -o graph.png");
	system("display graph.png ");
	
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

void liberer(int ** mat,int taille){
	for (int i=0;i<taille;i++){
		free(mat[i]);
	}
	free(mat);
}

couple_t * init_couple(){
	couple_t *c=malloc(sizeof(couple_t));

	if (c==NULL){
		printf("erreur couple");
		exit(EXIT_FAILURE);
	}
	return c;
}

void generer_couple(couple_t *c,int taille){
		int x;	

		c->nb_noeud=taille;
		for (int i=0;i<taille;i++){
			for (int j=i+1;j<taille;j++){
				x=rand()%6;
				if (x==1){
					aretes_t *nouv=malloc(sizeof(aretes_t));
					nouv->coord1=i;
					nouv->coord2=j;
					nouv->suiv=c->suiv;
					c->suiv=nouv;
				}
			}
		}
}


int main(){
	srand(time(0));
	int taille=10;
	partition_t * t=creer(taille);
	int ** mat=creer_mat(taille);
	generation_mat(mat,taille);
	int erreur=0;
	couple_t *c=init_couple();
	generer_couple(c,taille);

	/*
	fusion(t,6,5,taille);
	lister_classe(t,3,taille);
	lister_partition(t,taille);
	*/
	fusion_couple(c,t,taille);

	//fusion_mat(mat,t,taille);
	//erreur=graph_mat(mat,taille); //afficher à partir de la matrice
	//erreur=graph(t,taille);  //afficher à partir de la partition
	//graph_connexes(t,taille);	//afficher les graphes connexes
	//graph_couple(c);
	graph_connexes(t,taille);	//afficher les graphes connexes

	if (erreur)
		printf("erreur\n");

	liberer(mat,taille);

	return 0;
}
