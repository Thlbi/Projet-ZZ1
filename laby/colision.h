#ifndef _gard_coll_
#define _gard_coll_

#include "kruskal.h"
#include "main.h"

int collision_N(int pos_x,int pos_y,int **tab,int taille_cell);
int collision_S(int pos_x,int pos_y,int **tab,int taille_cell);
int collision_O(int pos_x,int pos_y,int **tab,int taille_cell);
int collision_E(int pos_x,int pos_y,int **tab,int taille_cell);

#endif
