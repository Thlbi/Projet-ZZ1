#ifndef _gard_graph_
#define _gard_graph_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

typedef struct arrete{
    int sommet1;
    int sommet2;
    struct arrete *suiv;
}arrete_t;

typedef struct graph{
    int Nb_Noyau;
    arrete_t *liste;
}graph_t;

#endif
