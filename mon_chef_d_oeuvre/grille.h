/*Grillle du jeu.h
16 juin 2021*/


#ifndef GRILLE_H
#define GRILLE_H


#include <math.h>
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
#include<time.h>

#define NB_MET 1
#define LARGEUR_MET 15

int** init_grille(int x,int y);
void liberer(int **grille,int x);
void vaisseau_gauche(int **grille,int *pos_vaisseau,int longeur);
void vaisseau_droite(int **grille,int *pos_vaisseau,int longeur,int largeur);
int init_tab(int** tab,int x,int y);
void position_vaisseau(int **grille,int *pos_vaisseau,int longeur,int largeur,int commande);
int  gestion_meteorites(int **tab,int largeur,int hauteur,int pos_vaisseau,int generation,int grille[][NB_MET], int regen);

#endif
