#include "Aetoile.h"

int max(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}

int distance_euclidienne(int a, int b)
{
	return (int) sqrt((a/P - b/b)*(a/P - b/P) + (a%P -b%P)*(a%P -b%P));
}

int distance_tcheby(int a, int b)
{
	return max(abs(a/P-b/P),abs(a%P-b%P));
}

int distance_manhattan(int a, int b)
{
	return (abs(a/P - b/P) + abs(a%P - b%P));
}

int * dijsktra(int ** laby, int noeuds, int depart)
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
	free(indice_valeur);
	liberer(tas);
	return parent;	
}

int * Aetoile_euclidienne(int ** laby, int noeuds, int depart, int arrivee)
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
						distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_euclidienne(voisin[j],arrivee);
						ajouter_tas_min(tas,distance[voisin[j]],indice_valeur);
						parent[voisin[j]]=sommet;
					}
					else
					{
						if (distance[voisin[j]].poids>(1+distance[sommet].poids+ distance_euclidienne(voisin[j],arrivee)))
						{
							distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_euclidienne(voisin[j],arrivee);
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
		tas->tab[0].poids-=distance_euclidienne(tas->tab[0].val,arrivee);
		
	}
	free(distance);
	free(indice_valeur);
	liberer(tas);
	return parent;	
}

int * Aetoile_tcheby(int ** laby, int noeuds, int depart,int arrivee)
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
						distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_tcheby(voisin[j],arrivee);
						ajouter_tas_min(tas,distance[voisin[j]],indice_valeur);
						parent[voisin[j]]=sommet;
					}
					else
					{
						if (distance[voisin[j]].poids>1+distance[sommet].poids+ distance_tcheby(voisin[j],arrivee))
						{
							distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_tcheby(voisin[j],arrivee);
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
		tas->tab[0].poids-=distance_tcheby(tas->tab[0].val,arrivee);
		
	}
	free(distance);
	free(indice_valeur);
	liberer(tas);
	return parent;	
}

int * Aetoile_manhattan(int ** laby, int noeuds, int depart, int arrivee)
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
						distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_manhattan(voisin[j],arrivee);
						ajouter_tas_min(tas,distance[voisin[j]],indice_valeur);
						parent[voisin[j]]=sommet;
					}
					else
					{
						if (distance[voisin[j]].poids>1+distance[sommet].poids+ distance_manhattan(voisin[j],arrivee))
						{
							distance[voisin[j]].poids=1 + distance[sommet].poids+ distance_manhattan(voisin[j],arrivee);
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
		tas->tab[0].poids-=distance_manhattan(tas->tab[0].val,arrivee);
		
	}
	free(distance);
	free(indice_valeur);
	liberer(tas);
	return parent;	
}

int main (int argc, char** argv)
{
	double p;
	if (argc==2)  p=atof(argv[1]);
	else p=1; 
	srand(time(0));
	int noeuds=N*P;
	int nb_aretes=2*N*P-N-P;
	int **tab;
	int *parent;
	int cours=0;
	
	graph_t * graph=creer_graph(noeuds,nb_aretes);
	generation(graph);
	graph=Fisher(graph,nb_aretes);
	graph=kruskal(graph,noeuds,nb_aretes,&cours,p);
	tab=tableau_ligne(graph,cours);

	int depart=rand()%noeuds;
	int arrivee=rand()%noeuds;
	
	clock_t t_depart, t_fin;
	float temps;

	t_depart=clock();
//	for (int i=0; i<1000; i++)
	parent=dijsktra(tab,noeuds,arrivee);
	t_fin=clock();
	temps=-t_depart+t_fin;
	printf("temps dijsktra : %f\n",temps);

	t_depart=clock();
//	for (int i=0; i<1000; i++)
	parent=Aetoile_euclidienne(tab,noeuds,depart,arrivee);
	t_fin=clock();
	temps=-t_depart+t_fin;
	printf("temps Aetoile_euclidienne : %f\n",temps);

	t_depart=clock();
//	for (int i=0; i<1000; i++)
	parent=Aetoile_tcheby(tab,noeuds,depart,arrivee);
	t_fin=clock();
	temps=-t_depart+t_fin;
	printf("temps Aetoile_tcheby : %f\n",temps);

	t_depart=clock();
//	for (int i=0; i<1000; i++)
	parent=Aetoile_manhattan(tab,noeuds,depart,arrivee);
	t_fin=clock();
	temps=-t_depart+t_fin;
	printf("temps Aetoile_manhattan: %f\n",temps);
}
                                     

