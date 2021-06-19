#ifndef _gard_partition
#define _gard_partition

#include "arete.h"

typedef struct partition{
	int val;
	int hauteur;
	int par;
}partition_t;

typedef struct couple{
	int nb_noeud;
	aretes_t *suiv;
} couple_t;

#define POIDS 20

partition_t * creer(int taille);
int recuperer_classe(partition_t * t,int nombre,int taille);
void fusion(partition_t * t,int x,int y,int taille);
int lister_classe(partition_t * t,int classe,int taille,int *tab);
void lister_partition(partition_t * t,int taille);
int ** creer_mat(int nb_noeuds);
int graph_mat(int ** mat,int taille);
void generation_mat(int **mat,int taille);	
void liberer(int **mat,int taille);
couple_t * init_couple();
void generer_couple(couple_t *c,int taille);
int graph_couple(couple_t *c);
int main();

#endif
