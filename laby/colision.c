#include "colision.h"

int collision_N(int pos_x,int pos_y,int **tab,int taille_cell){
    	int colli=0;

        if (!(tab[pos_x/taille_cell][pos_y/taille_cell]&FLAG_N)){
            colli=1;
	}
	return colli;
}

int collision_S(int pos_x,int pos_y,int **tab,int taille_cell){
    	int colli=0;

        if (!(tab[pos_x/taille_cell][pos_y/taille_cell]&FLAG_S)){
            colli=1;
        }
	return colli;
}

int collision_O(int pos_x,int pos_y,int **tab,int taille_cell){
    	int colli=0;

        if (!(tab[pos_x/taille_cell][pos_y/taille_cell]&FLAG_O)){
        	    colli=1;
    	}
	return colli;
}

int collision_E(int pos_x,int pos_y,int **tab,int taille_cell){
    	int colli=0;

        if (!(tab[pos_x/taille_cell][pos_y/taille_cell]&FLAG_E)){
            colli=1;
        }
 	return colli;
}
