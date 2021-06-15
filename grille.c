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
    if (((*pos_vaisseau+commande)>0)&&((*pos_vaisseau+commande)<largeur-1))
    {
        grille[*pos_vaisseau][hauteur-1]=0;
        *pos_vaisseau=*pos_vaisseau+commande;
        grille[*pos_vaisseau+commande][hauteur-1]=1;
    }

}


void vaisseau_gauche(int **grille,int *pos_vaisseau,int hauteur) //gère le deplacement du vaisseau a gauche
{
    if ((*pos_vaisseau-1)>0)
    {
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
    tab[x/2][y-1]=1;

    return x/2;
}


int  gestion_meteorites(int **tab,int largeur,int hauteur){ //renvoie 1 si on meurt 0 sinon et déplace  toutes les météorites
    int i;
    int j=hauteur-1;
    int mort=0;

    for(i=0;i<largeur;i++){
        if (tab[i][j]==2){
            tab[i][j]=0;
        }
    }
    j=j-1;
    while ((i<largeur)&&(mort==0)){
        if (tab[i][j]==2){
            if (tab[i][j+1]==1){
                mort=1;
            }
            else{
                tab[i][j]=0;
                tab[i][j+1]=0;;
            }
        }
        i=i+1;
    }
    if (mort==0){
        j=j-1;
        for(i=0;i<largeur;i++){
            for(j=j;j>=0;j--){
                if (tab[i][j]==2){
                    tab[i][j+1]=2;
                    tab[i][j]=0;
                }
            }
        }
        srand(time);
        for (i=0;i<15;i++){
            printf("%d\n",rand()%30);
            tab[rand()%30][0]=2;
        }
    }
    return mort;
}               



int main(){
    
    int hauteur=50;
    int largeur=29;
    int pos_vaisseau;
    int **tab =init_grille(largeur,hauteur);
    int i;
    int j;  
    pos_vaisseau=init_tab(tab,largeur,hauteur);
    position_vaisseau(tab,&pos_vaisseau,hauteur,largeur,-1);
    position_vaisseau(tab,&pos_vaisseau,hauteur,largeur,-1);
    position_vaisseau(tab,&pos_vaisseau,hauteur,largeur,-1);
    for (j=0;j<hauteur;j++)
	{
		for (i=0;i<largeur;i++)
		{
			printf("%d ",tab[i][j]);
		}
        printf("\n");
	}
    gestion_meteorites(tab,largeur,hauteur);
    for (j=0;j<hauteur;j++)
	{
		for (i=0;i<largeur;i++)
		{
			printf("%d ",tab[i][j]);
		}
        printf("\n");
	}


    liberer(tab,largeur);
}
