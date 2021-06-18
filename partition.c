#include"partition.h"


partition_t * creer(int n)
{
	partition_t * part=malloc(n*sizeof(partition_t));
	for (int i=0; i<n; i++)
	{
		part[i].parent=i;
		part[i].taille=1;
		part[i].racine=1;
	}
	return part;
}

int recuperer_classe(int indice, partition_t * part)
{
	if (part[indice].parent==indice)
		return indice;
	else
		return recuperer_classe(part[indice].parent, part);
}

void fusion(int indice1, int indice2, partition_t * part)
{
	int c1=recuperer_classe(indice1, part);
	int c2=recuperer_classe(indice2, part);
	if (part[c1].taille>part[c2].taille)
		part[c2].parent=c1;
	else if (part[c1].taille<part[c2].taille)
		part[c1].parent=c2;
	else
	{
		part[c1].parent=c2;
		part[c2].taille+=1;
	}
}

void lister_classe_naif(partition_t * part, int etiquette, int n)
{
	for (int i=0; i<n; i++)
		if (recuperer_classe(i,part)==etiquette)
			printf("%d ",i);
}

void lister_partition(partition_t * part,int n, int * nbclasse,int * tab)
{
	int j=0;
	for (int i=0; i<n; i++)
	{
		if (part[i].parent==i)
		{
			tab[j]=i;
			j+=1;
		}
	}
	*nbclasse=j;
}

void graph(partition_t * part, int n)
{
	FILE *fichier;
	fichier=fopen("graph.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"digraph Nom{\n");
	for (int i=0; i<n ;i++)
	{
		fprintf(fichier,"%d",i);
		fprintf(fichier,"->");
		fprintf(fichier,"%d",part[i].parent);
		fprintf(fichier,";");
	}
	fprintf(fichier, "}");
	fclose(fichier);
	system("dot -Tpng graph.dot -o graph.png");
	system("display graph.png");
}

int main ()
{
	partition_t * part=creer(10);
	fusion(0,1,part);
	fusion(1,2,part);
	fusion(3,4,part);
	fusion(2,4,part);
	graph(part,10);
}
