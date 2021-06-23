#ifndef _gard_Aetoile_
#define _gard_Aetoile__
/*gcc Aetoile.c -c -Wall -Wextra
gcc Aetoile.o kruskal.o graph_aretes_tab.o tas.o partition.o -lm -o Aetoile -g*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>
#include <math.h>
#include "graph_aretes_tab.h"
#include "tas.h"
#include "kruskal.h"

typedef enum {
	FLAG_N=1,
	FLAG_S=2,
	FLAG_E=4,
	FLAG_O=8
}flag_t;

int distance_euclidienne(int a, int b);
int distance_tcheby(int a, int b);
int distance_manhattan(int a, int b);

int * dijsktra(int **, int, int);
int * Aetoile_euclidienne(int ** laby, int noeuds, int depart,int );
int * Aetoile_tcheby(int ** laby, int noeuds, int depart, int);
int * Aetoile_manhattan(int ** laby, int noeuds, int depart, int);

int main (int argc, char** argv);
#endif
