#ifndef _gard_graph_
#define _gard_graph_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "partition.h"

typedef struct arete{
    int sommet1;
    int sommet2;
    int poids;
    struct arete *suiv;
}arete_t;

typedef struct graph{
    int Nb_Noyau;
    arete_t *suiv;
}graph_t;

graph_t *  initgraph(int noyau);
arete_t * allouer(int coord1,int coord2,int poids);
void ajouter_arete(graph_t*graph,int sommet1,int sommet2,int poids);
void afficher_graph(graph_t*graph);
void afficher_arete(arete_t *arete);
void generer_couple(graph_t *graph);
arete_t * kruskal(graph_t *graph);

#endif
