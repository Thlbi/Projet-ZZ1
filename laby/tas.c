#include "tas.h"

tas_t * init_tas(int t)
{
	tas_t * tas= malloc(sizeof(tas_t));
	tas->taille_max=t;
	tas->taille=-1;
	tas->tab= malloc(t*sizeof(typetas));
	return tas;
}

void liberer(tas_t* tas)
{
	free(tas->tab);
	free(tas);
}

void ajouter_tas_min(tas_t * tas,int noeud,int distance)
{
	typetas aux;
	tas->taille+=1;
	int rang=tas->taille;
	tas->tab[rang].noeud=noeud;
	tas->tab[rang].distance=distance;
	while (rang>0 && (tas->tab[(rang-1)/2].distance>distance))
	{
		aux=tas->tab[rang];
		tas->tab[rang]=tas->tab[(rang-1)/2];
		rang=(rang-1)/2;
		tas->tab[rang]=aux;
	}
}


void percolation_bas_tas_min(tas_t *tas, int indice)
{
	int valeur=tas->tab[indice].distance;
	int rang=indice;
	typetas aux;
	int fin=1;
	while (fin)
	{
		if (2*rang+1==(tas->taille) && (tas->tab[2*rang +1].distance<valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}

		if (2*rang + 1<=(tas->taille) && (tas->tab[2*rang +1].distance<tas->tab[2*rang +2].distance) && (tas->tab[2*rang +1].distance<valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		else if (2*rang + 2<=(tas->taille) && (tas->tab[2*rang +2].distance<tas->tab[2*rang +1].distance) && (tas->tab[2*rang +2].distance<valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +2];
			rang=2*rang +2;
			tas->tab[rang]=aux;
		}
		else 
			fin=0;
	}
}
