#include "graph.h"

int ** creer_mat(int n)
{
	int ** mat= malloc(n*sizeof(int *));
	if (!mat)
		printf("erreur d'allocation de la matrice\n");
	for (int i=0; i<n; i++)
	{
		mat[i]= malloc(n*sizeof(int));
		if (!mat[i])
			printf("erreur d'allocation de la ligne %d\n",i);
	}
	return mat;
}

void remplir_mat(int ** mat, int n)
{
	for (int i=0; i<n ;i++)
	{
		for (int j=0; j<i; j++)
			mat[i][j]=rand()%8;
	}
}
	

void affiche_graph(int ** mat, int n)
{
	FILE *fichier;
	fichier=fopen("graph1.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	for (int i=0; i<n ;i++)
	{
		fprintf(fichier,"%d",i);
		fprintf(fichier,";");
		for (int j=0; j<i; j++)
		{
			if (mat[i][j]==1)
			{
				fprintf(fichier,"%d",i);
				fprintf(fichier,"--");
				fprintf(fichier,"%d",j);
				fprintf(fichier,";");
			}
		}
	}
	fprintf(fichier, "}");
	fclose(fichier);
}

void partition_connexe(partition_t* part, int ** mat,int n)
{
	for (int i=0; i<n ;i++)
		for (int j=0; j<i; j++)
			if (mat[i][j]==1)
				fusion(i,j,part);
}

int main()
{
	srand(time(0));
	int ** mat=NULL;
	mat= creer_mat(10);
	remplir_mat(mat,10);
	partition_t * part=creer(10);
/*		for (int i=0; i<10 ;i++)
	{
		for (int j=0; j<i; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
*/
	affiche_graph(mat, 10);
	partition_connexe(part,mat,10);
	affiche_part(part, 10);
	
	system("dot -Tpng graph1.dot -o graph1.png");
	system("dot -Tpng graph_part.dot -o graph_part.png");
	system("display graph1.png &");
	system("display graph_part.png &");
	return 0;
}			
