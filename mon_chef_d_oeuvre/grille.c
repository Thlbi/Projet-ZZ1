/*Grillle du jeu 
15 juin 2021*/
#include "grille.h"




int** init_grille(int x,int y) 
{
	int ** grille=malloc(x*sizeof(int *));
	if (grille==NULL)
	{
		printf("Erreur d'allocation du int**\n");
	}
		
	for (int i=0; i<x;i++)
	{
		grille[i]=malloc(y*sizeof(int));
		if (grille[i]==NULL)
		{
			printf("Erreur d'allocation du int* numero %d\n",i);
		}
	
	}
	return grille;
}

void liberer(int **grille,int x) 
{
	for (int i=0; i<x;i++)
		free(grille[i]);
	free(grille);
}



void position_vaisseau(int **grille,int *pos_vaisseau,int longeur,int largeur,int commande) //gère le deplacement du vaisseau ne fonction de la commande -1 ou +1
{
	 largeur-=15;
    if (((*pos_vaisseau+commande)>=0)&&((*pos_vaisseau+commande)<=largeur-1))
    {
        grille[*pos_vaisseau][longeur-1]=0;
        *pos_vaisseau=*pos_vaisseau+commande;
        grille[*pos_vaisseau][longeur-1]=1;
    }

}


void vaisseau_gauche(int **grille,int *pos_vaisseau,int longeur) //gère le deplacement du vaisseau a gauche
{
    if ((*pos_vaisseau-1)>0)
    {
        grille[longeur-1][*pos_vaisseau]=0;
        *pos_vaisseau=*pos_vaisseau-1;
        grille[longeur-1][*pos_vaisseau]=1;
    }

}
void vaisseau_droite(int **grille,int *pos_vaisseau,int longeur,int largeur)
{
    if ((*pos_vaisseau-1)<largeur)
    {
        grille[longeur-1][*pos_vaisseau]=0;
        *pos_vaisseau=*pos_vaisseau-1;
        grille[longeur-1][*pos_vaisseau]=1;
    }

}
int init_tab(int** tab,int x,int y) //place le vaisseau 
{
	int i =0;
    int j =0;
	for (i=0;i<x;i++)
	{
		for (j=0;j<y;j++)
		{
			tab[i][j]=0;
		}
	}
    printf("%d\n",x/2);
    printf("%d\n",y-1);
    tab[x/2][y-1]=1;
	 return x/2;	
}

/*int colisition(int ** grille,int position)
{
	int coli=0;
	for (int i=0; i<15; i++)
	{
	if grille[position+i][19]==2
		coli==1;
	}
	return coli;
}*/


