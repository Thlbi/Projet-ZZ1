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
void fusion_mat(int ** mat,partition_t * t,int taille);
void fusion_couple(couple_t * c,partition_t *t,int taille);
int lister_classe(partition_t * t,int classe,int taille,int *tab);
void lister_partition(partition_t * t,int taille);
int ** creer_mat(int nb_noeuds);
int graph_mat(int ** mat,int taille);
int graph_couple(couple_t *c);
void generation_mat(int **mat,int taille);	
void liberer(int **mat,int taille);
couple_t * init_couple();
void generer_couple(couple_t *c,int taille);
int graph_couple(couple_t *c);
void graph_kruskal(aretes_t *A);
aretes_t * allouer(int coord1,int coord2,int poids);
couple_t * ordonner_aretes(couple_t *c);
void kruskal(int taille);
int main();

#endif
