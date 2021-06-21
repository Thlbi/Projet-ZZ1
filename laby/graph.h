#ifndef _gard_graph_
#define _gard_graph_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <time.h>
#include "partition.h"

int ** creer_mat(int n);
void remplir_mat(int ** mat, int n);

void affiche_graph(int ** mat, int n);

void partition_connexe(partition_t *,int **,int);

void affiche_graph2(int ** mat, int *,int n);

int main();
#endif
