#ifndef _gard_partition_
#define _gard_partition_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

typedef struct partition
{
	int parent;
	int racine;
	int taille;
}	partition_t;


partition_t * creer(int n);
int recuperer_classe(int indice, partition_t * part);
void fusion(int indice1, int indice2, partition_t * part);
void lister_classe_naif(partition_t * part, int etiquette, int n);
void lister_partition(partition_t * part,int n,int *,int *);
void graph(partition_t * part, int);
void remplir_mat(int n,int **mat);
void graph2(int **mat, int n);

#endif
