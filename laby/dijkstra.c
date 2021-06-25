#include "dijkstra.h"


int * dijkstra(int ** laby, int noeuds, int depart)
{
	int * parent = malloc(noeuds*sizeof(int));
	parent[depart]=depart;
	
	poids_t * distance = malloc(noeuds*sizeof(poids_t));
	for (int i=0; i<noeuds; i++)
	{
		distance[i].poids=noeuds;
		distance[i].val=i;
	}
	distance[depart].poids=0;

	int* indice_valeur = malloc(noeuds*sizeof(int));
	for (int i=0; i<noeuds; i++)
		indice_valeur[i]=-1;

	tas_t * tas=init_tas(noeuds+1);
	for (int i=0; i<noeuds; i++)
		tas->tab[i]=distance[i];

	int * voisin=malloc(4*sizeof(int));
	for (int i=0; i<4; i++)
		voisin[i]=-1;

	int sommet= depart;
	ajouter_tas_min(tas,distance[depart],indice_valeur);

	while (tas->taille>-1)
	{
		if (laby[sommet%P][sommet/P] & FLAG_N)
			voisin[0]=sommet-P;
		if (laby[sommet%P][sommet/P] & FLAG_S)
			voisin[1]=sommet+P;
		if (laby[sommet%P][sommet/P] & FLAG_O)
			voisin[2]=sommet-1;
		if (laby[sommet%P][sommet/P] & FLAG_E)
			voisin[3]=sommet+1;
		for (int j=0; j<4; j++)
		{	
			
			if (voisin[j]!=-1)
			{
				if (indice_valeur[voisin[j]]!=-2)
				{
					if (indice_valeur[voisin[j]]==-1)
					{
						distance[voisin[j]].poids=1 + distance[sommet].poids;
						ajouter_tas_min(tas,distance[voisin[j]],indice_valeur);
						parent[voisin[j]]=sommet;
					}
					else
					{
						if (distance[voisin[j]].poids>1+distance[sommet].poids)
						{
							distance[voisin[j]].poids=1 + distance[sommet].poids;
							percolation_bas_tas_min(tas,indice_valeur[voisin[j]],indice_valeur);
							parent[voisin[j]]=sommet;
						}
					}
				}
			}
			voisin[j]=-1;
		}
		indice_valeur[tas->tab[0].val]=-2;
		indice_valeur[tas->tab[tas->taille].val]=0;
		

		typetas aux=tas->tab[0];
		tas->tab[0]=tas->tab[tas->taille];
		tas->tab[tas->taille]=aux;
	
		tas->taille+=-1;
		percolation_bas_tas_min(tas,0,indice_valeur);
		sommet=tas->tab[0].val;
		
	}
	free(distance);
	free(voisin);
	free(indice_valeur);
	liberer(tas);
	return parent;	
}
