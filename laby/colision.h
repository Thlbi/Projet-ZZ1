#ifndef _gard_coll_
#define _gard_coll_

#include "kruskal.h"
#include "main.h"

int collision_N(int pos_x,int pos_y,int **tab,int taille_cell,int largeur_perso, int deplacement);
int collision_S(int pos_x,int pos_y,int **tab,int taille_cell,int largeur_perso, int hauteur_perso, int deplacement);
int collision_O(int pos_x,int pos_y,int **tab,int taille_cell, int hauteur_perso, int deplacement);
int collision_E(int pos_x,int pos_y,int **tab,int taille_cell,int largeur_perso, int hauteur_perso, int deplacement);


#endif
