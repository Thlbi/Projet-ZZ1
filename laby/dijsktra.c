#include "dijsktra.h"


int * dijsktra(graph_t * graph, int noeuds, int nb_aretes, int depart)
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

	aretes_t * A= malloc(nb_aretes*sizeof(aretes_t));
	for (int i=0; i<nb_aretes; i++)
		A[i]=graph->liste[i];	

	tas_t * tas=init_tas(noeuds+1);
	for (int i=0; i<noeuds; i++)
		tas->tab[i]=distance[i];

	
	
	int sommet= depart;
	ajouter_tas_min(tas,distance[depart],indice_valeur);
	int i=0;
	int voisin;
	affiche_graph_couple(graph,noeuds,nb_aretes);
	while (nb_aretes)
	{
		for (int j=0; j<4; j++)
		{	
			i=0;
			while (i<nb_aretes && A[i].un!=sommet && A[i].deux!=sommet)
				i++;
			if (A[i].un==sommet)
				voisin=A[i].deux;
			else if (A[i].deux==sommet)
				voisin=A[i].un;
			if (voisin!=-1)
			{
				if (indice_valeur[voisin]!=-2)
				{
					if (indice_valeur[voisin]==-1)
					{
						distance[voisin].poids=1 + distance[sommet].poids;
						ajouter_tas_min(tas,distance[voisin],indice_valeur);
						parent[voisin]=sommet;
						A[i]=A[nb_aretes-1];
						nb_aretes--;
						voisin=-1;
					}
		//		printf("poids :%d \n",tas->tab[indice_valeur[voisin]].poids);
					else
					{
						if (distance[voisin].poids>1+distance[sommet].poids)
						{
							distance[voisin].poids=1 + distance[sommet].poids;
							percolation_bas_tas_min(tas,indice_valeur[voisin],indice_valeur);
							parent[voisin]=sommet;
						}
						A[i]=A[nb_aretes-1];
						voisin=-1;
						nb_aretes--;
					}
				}
			}
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
	//affichage(tas);   
	for(int i=0; i<noeuds; i++)
			printf("%d ",parent[i]);
		printf("\n");
		printf("taille tas: %d\n",tas->taille);
		printf("nb_aretes: %d\n", nb_aretes);
	free(distance);
	free(indice_valeur);
	free(A);
	liberer(tas);
	return parent;	
}
