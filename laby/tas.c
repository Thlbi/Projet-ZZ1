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

tas_t * ajouter_tas_min(tas_t * tas,typetas x)
{
	typetas aux;
	tas->taille+=1;
	int rang=tas->taille;
	tas->tab[rang]=x;
	while (rang>0 && plusgrand(tas->tab[(rang-1)/2],x))
	{
		aux=tas->tab[rang];
		tas->tab[rang]=tas->tab[(rang-1)/2];
		rang=(rang-1)/2;
		tas->tab[rang]=aux;
	}
	return tas;
}


void percolation_bas_tas_min(tas_t *tas, int indice)
{
	typetas valeur=tas->tab[indice];
	int rang=indice;
	typetas aux;
	int fin=1;
	while (fin)
	{
		if (2*rang+1==(tas->taille) && !plusgrand(tas->tab[2*rang +1],valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}

		if (2*rang + 1<=(tas->taille) && !plusgrand(tas->tab[2*rang +1],tas->tab[2*rang +2]) && !plusgrand(tas->tab[2*rang +1],valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		else if (2*rang + 2<=(tas->taille) && !plusgrand(tas->tab[2*rang +2],tas->tab[2*rang +1]) && !plusgrand(tas->tab[2*rang +2],valeur))
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


void affichage(tas_t* tas)
{
	for (int i=0; i<=tas->taille; i++)
	{	
		printf("valuation :%d ",tas->tab[i].valuation);
		printf("sommet un :%d ",tas->tab[i].un);
		printf("sommet deux :%d ",tas->tab[i].deux);
		printf("\n");
	}
	printf("\n");

}
