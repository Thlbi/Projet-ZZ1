#include "collision.h"



int collision_N(int pos_x,int pos_y,**tab,int taille_case,int largeur_perso,int hauteur_perso,int deplacement){
    int j=pos_x%(P*taille_case);
    int i=pos_y/(P*taille_case);
    int colli=0

    if(pos_y-deplacement<i*taille_case){
        if (tab[i][j]&FLAG_N){
            colli=1;
        }
    }
return colli;
}

int collision_S(int pos_x,int pos_y,**tab,int taille_case,int largeur_perso,int hauteur_perso,int deplacement){
    int j=pos_x%(P*taille_case);
    int i=pos_y/(P*taille_case);
    int colli=0

    if(pos_y+deplacement>i*taille_case+taille_case){
        if (tab[i][j]&FLAG_S){
            colli=1;
        }
    }
return colli;
}
int collision_O(int pos_x,int pos_y,**tab,int taille_case,int largeur_perso,int hauteur_perso,int deplacement){
    int j=pos_x%(P*taille_case);
    int i=pos_y/(P*taille_case);
    int colli=0

    if(pos_x-deplacement<j*taille_case){
        if (tab[i][j]&FLAG_O){
            colli=1;
        }
    }
return colli;
int collision_E(int pos_x,int pos_y,**tab,int taille_case,int largeur_perso,int hauteur_perso,int deplacement){
    int j=pos_x%(P*taille_case);
    int i=pos_y/(P*taille_case);
    int colli=0

    if(pos_x+deplacement<j*taille_case+taille_case){
        if (tab[i][j]&FLAG_O){
            colli=1;
        }
    }
return colli;
