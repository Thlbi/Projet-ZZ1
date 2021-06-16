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


int  gestion_meteorites(int **tab,int largeur,int hauteur,int largeur_met,int nb_met,int pos_vaisseau,int generation){ //renvoie 1 si on meurt 0 sinon et déplace  toutes les météorites
    int i;
    int j=hauteur-1;
    int mort=0;
    int k;

    for(i=0;i<largeur;i++){
        if (tab[i][j]==2){
            tab[i][j]=0;
        }
    }
    j=j-1;
    i=0;
    while ((i<largeur)&&(mort==0)){
        if (tab[i][j]==2){
            printf("ok\n");
            for(k=pos_vaisseau;k<19;k++){ //19 correspond a la taille du vaisseau en pixel (largeur)
                if (i==k){
                    mort=1;
                }
            }
            tab[i][j+1]=2;
            tab[i][j]=0;   
        }
        i=i+1;
    }
    if (mort==0){
        for(i=0;i<largeur;i++){
            for(j=hauteur-3;j>=0;j--){
                if (tab[i][j]==2){
                    tab[i][j+1]=2;
                    tab[i][j]=0;
                }
            }
        }
        if (generation==1){   
            for (i=0;i<nb_met;i++){

                k=rand()%29;
                printf("%d\n",k);
                for (j=k;j<=(k+largeur_met);j++){   
                    if (k<largeur){
                        tab[j][0]=2;
                    printf("ok\n");
                    }
                }
                
            }
        }
    }
    return mort;
}               



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
}
