/*Grillle du jeu 
16 juin 2021*/
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



void position_vaisseau(int **grille,int *pos_vaisseau,int hauteur,int largeur,int commande) //gère le deplacement du vaisseau ne fonction de la commande -1 ou +1
{
    if (((*pos_vaisseau+commande)>=0)&&((*pos_vaisseau+commande)<=(largeur-1)))
    {
        grille[*pos_vaisseau][hauteur-1]=0;
        *pos_vaisseau=(*pos_vaisseau)+commande;
        grille[*pos_vaisseau][hauteur-1]=1;
    }

}

/*
void vaisseau_gauche(int **grille,int *pos_vaisseau,int hauteur) //gère le deplacement du vaisseau a gauche
{1 1
        grille[hauteur-1][*pos_vaisseau]=0;
        *pos_vaisseau=*pos_vaisseau-1;
        grille[hauteur-1][*pos_vaisseau]=1;
    }

}
void vaisseau_droite(int **grille,int *pos_vaisseau,int hauteur,int largeur)
{
    if ((*pos_vaisseau+1)<largeur)
    {
        grille[hauteur-1][*pos_vaisseau]=0;
        *pos_vaisseau=*pos_vaisseau-1;
        grille[hauteur-1][*pos_vaisseau]=1;
    }

}
*/
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
    tab[0][y-1]=1;

    return 0;
}


int  gestion_meteorites(int **tab,int largeur,int hauteur,int pos_vaisseau,int generation,int  met[][NB_MET],int regen)
{ //renvoie 1 si on meurt 0 sinon et déplace  toutes les météorites
    int i;
    int j=hauteur-1;
    int mort=0;
    int k;
	 int hit;
	
/*Suppresion de meteroitew derniere ligne*/ 
    for(i=0;i<largeur;i++)
	 {
        if (tab[i][j]==2)
		  {
            tab[i][j]=0;
        }
    }

/*Gestion de la mort/hitbox*/
    i=0;
    while ((i<largeur)&&(mort==0))
    {
	 for (int k=0;k<20;k++)
	 {
      if (tab[i][j-(k+15)]==2)
		  {
			if (k>9)
				hit=5;
			else
				hit=1;
            for(int m=pos_vaisseau+hit;m<15+pos_vaisseau-hit;m++)
				{ 
                if (i==m)
                    mort=1;
            }
        }
		}
        i=i+1;
    }


/*Decalage meteorite*/
    if (mort==0)
	 {
        for(i=0;i<largeur;i++)
		  {
            for(j=hauteur-2;j>=0;j--)
				{
                if (tab[i][j]==2)
					 {
                    tab[i][j+1]=2;
                    tab[i][j]=0;
                }
            }
        }

		/*Generation metorite*/
        if (generation==1)
		  {   
            for (i=0;i<NB_MET;i++)
				{
                k=rand()%(largeur-LARGEUR_MET);
					 met[regen][i]=k;

                for (j=k;j<(k+LARGEUR_MET);j++)
					 {   
                        tab[j][0]=2;
                }
                
            }
        }
    }
    return mort;
}               


/*
int main(){
    
    int hauteur=5;
    int largeur=29;
    int pos_vaisseau;
    int **tab =init_grille(largeur,hauteur);
    int i;
    int j;
    int nb_met=1;
    int mort=0;
    int largeur_met=2;
    pos_vaisseau=init_tab(tab,largeur,hauteur);


    for (j=0;j<hauteur;j++)
	{
		for (i=0;i<largeur;i++)
		{
			printf("%d ",tab[i][j]);
		}
        printf("\n");
	}

    srand(time(0));
    mort = gestion_meteorites(tab,largeur,hauteur,largeur_met,nb_met,pos_vaisseau,1);
    mort = gestion_meteorites(tab,largeur,hauteur,largeur_met,nb_met,pos_vaisseau,1);
    mort = gestion_meteorites(tab,largeur,hauteur,largeur_met,nb_met,pos_vaisseau,0);
    mort = gestion_meteorites(tab,largeur,hauteur,largeur_met,nb_met,pos_vaisseau,0);
    printf("%d\n",mort);
    for (j=0;j<hauteur;j++)
	{
		for (i=0;i<largeur;i++)
		{
			printf("%d ",tab[i][j]);
		}
        printf("\n");
	}
    mort = gestion_meteorites(tab,largeur,hauteur,largeur_met,nb_met,pos_vaisseau,0);
        for (j=0;j<hauteur;j++)
	{
		for (i=0;i<largeur;i++)
		{
			printf("%d ",tab[i][j]);
		}
        printf("\n");
	}
    printf("%d\n",mort);
}*/
