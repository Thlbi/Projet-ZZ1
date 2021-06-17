#include "tas.h"

tas_t * init_tas(int t)
{
	tas_t * tas= malloc(sizeof(tas_t));
	tas->taille_max=t;
	tas->taille=-1;
	tas->tab= malloc(t*sizeof(int));
	return tas;
}

void liberer(tas_t* tas)
{
	free(tas->tab);
	free(tas);
}

tas_t * ajouter_tas_min(tas_t * tas,int x)
{
	int aux;
	tas->taille+=1;
	int rang=tas->taille;
	tas->tab[rang]=x;
	while (rang>0 && x<tas->tab[(rang-1)/2])
	{
		aux=tas->tab[rang];
		tas->tab[rang]=tas->tab[(rang-1)/2];
		rang=(rang-1)/2;
		tas->tab[rang]=aux;
	}
	return tas;
}

tas_t * ajouter_tas_max(tas_t * tas,int x)
{
	int aux;
	tas->taille+=1;
	int rang=tas->taille;
	tas->tab[rang]=x;
	while (rang>0 && x>tas->tab[(rang-1)/2])
	{
		aux=tas->tab[rang];
		tas->tab[rang]=tas->tab[(rang-1)/2];
		rang=(rang-1)/2;
		tas->tab[rang]=aux;
	}
	return tas;
}

tas_t * percolation_bas_tas_min(tas_t *tas, int indice)
{
	int valeur=tas->tab[indice];
	int rang=indice;
	int aux;
	int fin=1;
	while (fin)
	{
//	printf("dans le while\n");
		if (2*rang + 1<=(tas->taille) && tas->tab[2*rang +1]<=tas->tab[2*rang +2] && tas->tab[2*rang +1]<valeur)
		{
		
//	printf("dans le 1er if\n");
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		else if (2*rang + 2<=(tas->taille) && tas->tab[2*rang +2]<tas->tab[2*rang +1] && tas->tab[2*rang +2]<valeur)
		{
	printf("dans le 1er if\n");
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +2];
			rang=2*rang +2;
			tas->tab[rang]=aux;
		}
		else 
			fin=0;
	}
	return tas;
}

tas_t * construire(tas_t * tas, int *t, int pos)
{
	if (pos==0)
		return tas;
	else
		return construire(ajouter_tas_min(tas, t[pos-1]), t,pos-1);
}

tas_t* tri_par_tas(int *t, int n)
{
	tas_t* tas=init_tas(1000);
	tas=construire(tas,t,n);
	while(tas->taille>0)
	{
	//printf("dans le while ");	
	//printf("%d\n",tas->taille);
	int aux=tas->tab[0];
	tas->tab[0]=tas->tab[tas->taille];
	tas->tab[tas->taille]=aux;
	affichage(tas);	
	tas->taille+=-1;
	percolation_bas_tas_min(tas,0);
	affichage(tas);	
	}
	tas->taille=n-1;
	return tas;
}

void affichage(tas_t* tas)
{
	for (int i=0; i<=tas->taille; i++)
		printf("%d ",tas->tab[i]);
	printf("\n");

}

int main()
{
	int tableau[10];
	tas_t* tas=init_tas(1000);
	tas_t * tas2;
	tableau[0]=5, tableau[1]=15, tableau[2]=2, tableau[3]=7, tableau[4]=3, tableau[5]=6, tableau[6]=5, tableau[7]=65, tableau[8]=52, tableau[9]=512; 
	construire(tas,tableau,10);
	affichage(tas);
	printf("%d\n",tas->taille);
	tas2=tri_par_tas(tableau,10);
	printf("%d\n",tas2->taille);
	affichage(tas2);
}
