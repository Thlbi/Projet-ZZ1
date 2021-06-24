#include "colision.h"

int collision_N(int pos_x, int pos_y, int **tab, int taille_cell, int largeur_perso, int deplacement)
{
	int colli = 0;
	int j = pos_x / taille_cell;
	int i = pos_y / taille_cell;
	int j2 = (pos_x + largeur_perso) / taille_cell;
	if (pos_y - deplacement / 10 < i * taille_cell) // deplacement /10 correspond au depalcement de chaque frame (10 frame en tout )
	{
		if ((!(tab[j][i] & FLAG_N)) || (!(tab[j2][i] & FLAG_N)))
		{
			colli = 1;
		}
	}
	return colli;
}

int collision_S(int pos_x, int pos_y, int **tab, int taille_cell, int largeur_perso, int hauteur_perso, int deplacement)
{
	int colli = 0;
	int j = pos_x / taille_cell;
	int i = pos_y / taille_cell;
	int j2 = (pos_x + largeur_perso) / taille_cell;
	if (pos_y + deplacement / 10 + hauteur_perso > (i + 1) * taille_cell)
	{
		if ((!(tab[j][i] & FLAG_S)) || (!(tab[j2][i] & FLAG_S)))
		{
			colli = 1;
		}
	}
	return colli;
}

int collision_O(int pos_x, int pos_y, int **tab, int taille_cell, int hauteur_perso, int deplacement)
{
	int colli = 0;
	int j = pos_x / taille_cell;
	int i = pos_y / taille_cell;
	int i2 = (pos_y + hauteur_perso) / taille_cell;
	if (pos_x - deplacement / 10 < j * taille_cell)
	{
		if ((!(tab[j][i] & FLAG_O)) || (!(tab[j][i2] & FLAG_O)))
		{
			colli = 1;
		}
	}
	return colli;
}

int collision_E(int pos_x, int pos_y, int **tab, int taille_cell, int largeur_perso, int hauteur_perso, int deplacement)
{
	int colli = 0;
	int j = pos_x / taille_cell;
	int i = pos_y / taille_cell;
	int i2 = (pos_y + hauteur_perso) / taille_cell;
	if (pos_x + deplacement / 10 + largeur_perso > (j + 1) * taille_cell)
	{
		if ((!(tab[j][i] & FLAG_E)) || (!(tab[j][i2] & FLAG_E)))
		{
			colli = 1;
		}
	}
	return colli;
}
