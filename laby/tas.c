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

tas_t * ajouter_tas_max(tas_t * tas,typetas x)
{
	typetas aux;
	tas->taille+=1;
	int rang=tas->taille;
	tas->tab[rang]=x;
	while (rang>0 && plusgrand(x,tas->tab[(rang-1)/2]))
	{
		aux=tas->tab[rang];
		tas->tab[rang]=tas->tab[(rang-1)/2];
		rang=(rang-1)/2;
		tas->tab[rang]=aux;
	}
	return tas;
}

tas_t * percolation_bas_tas_max(tas_t *tas, int indice)
{
	typetas valeur=tas->tab[indice];
	int rang=indice;
	typetas aux;
	int fin=1;
	while (fin)
	{
 // 	printf("dans le while\n");
		if (2*rang+1==(tas->taille) && plusgrand(tas->tab[2*rang +1],valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		if (2*rang + 1<=(tas->taille) && plusgrand(tas->tab[2*rang +1],tas->tab[2*rang +2]) && plusgrand(tas->tab[2*rang +1],valeur))
		{
		
  //	printf("dans le 1er if\n");
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		else if (2*rang + 2<=(tas->taille) && plusgrand(tas->tab[2*rang +2],tas->tab[2*rang +1]) && plusgrand(tas->tab[2*rang +2],valeur))
		{
//	printf("dans le 2er if\n");
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


tas_t * percolation_bas_tas_min(tas_t *tas, int indice)
{
	typetas valeur=tas->tab[indice];
	int rang=indice;
	typetas aux;
	int fin=1;
	while (fin)
	{
 // 	printf("dans le while\n");
		if (2*rang+1==(tas->taille) && !plusgrand(tas->tab[2*rang +1],valeur))
		{
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}

		if (2*rang + 1<=(tas->taille) && !plusgrand(tas->tab[2*rang +1],tas->tab[2*rang +2]) && !plusgrand(tas->tab[2*rang +1],valeur))
		{
		
  //	printf("dans le 1er if\n");
			aux=tas->tab[rang];
			tas->tab[rang]=tas->tab[2*rang +1];
			rang=2*rang +1;
			tas->tab[rang]=aux;
		}
		else if (2*rang + 2<=(tas->taille) && !plusgrand(tas->tab[2*rang +2],tas->tab[2*rang +1]) && !plusgrand(tas->tab[2*rang +2],valeur))
		{
//	printf("dans le 2er if\n");
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

tas_t * construire_tas_min(tas_t * tas, typetas *t, int pos)
{
	if (pos==0)
		return tas;
	else
		return construire_tas_min(ajouter_tas_min(tas, t[pos-1]), t,pos-1);
}

tas_t * construire_tas_max(tas_t * tas, typetas *t, int pos)
{
	if (pos==0)
		return tas;
	else
		return construire_tas_max(ajouter_tas_max(tas, t[pos-1]), t,pos-1);
}

tas_t* tri_par_tas(typetas *t, int n)
{
	tas_t* tas=init_tas(1000);
	tas=construire_tas_max(tas,t,n);
	while(tas->taille>0)
	{
	//printf("dans le while ");	
	//printf("%d\n",tas->taille);
	typetas aux=tas->tab[0];
	tas->tab[0]=tas->tab[tas->taille];
	tas->tab[tas->taille]=aux;
//	affichage(tas);	
	tas->taille+=-1;
	percolation_bas_tas_max(tas,0);
//	affichage(tas);	
	}
	tas->taille=n-1;
	return tas;
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
/*
int main()
{
	typetas tableau[8];
	tas_t* tas=init_tas(1000);
	tas_t * tas2;
	tableau[0].un=1, tableau[0].deux=4, tableau[0].valuation=2; 
	tableau[1].un=5, tableau[1].deux=1, tableau[1].valuation=3; 
	tableau[2].un=2, tableau[2].deux=3, tableau[2].valuation=5; 
	tableau[3].un=2, tableau[3].deux=3, tableau[3].valuation=7; 
	tableau[4].un=2, tableau[4].deux=3, tableau[4].valuation=6; 
	tableau[5].un=2, tableau[5].deux=3, tableau[5].valuation=4; 
	tableau[6].un=2, tableau[6].deux=3, tableau[6].valuation=1; 
	tableau[7].un=2, tableau[7].deux=3, tableau[7].valuation=0; */
/*	tableau[0]=5, tableau[1]=15, tableau[2]=2, tableau[3]=7, tableau[4]=3, tableau[5]=6, tableau[6]=5, tableau[7]=65, tableau[8]=52, tableau[9]=512; */
/*	tas2=tri_par_tas(tableau,8);
	printf("%d\n",tas2->taille);
	affichage(tas2);
}*/
