/* Tas 17 Juin */

#include "tas.h"





tas_t * initas(int taille){
    tas_t *tas=malloc(sizeof(tas_t));
    tas->taille_max=taille;
    tas->taille=0;
    tas->tab=malloc(taille*sizeof(int)); 
    
    return tas;
    
}

void liberer_tas(tas_t *tas){
    free(tas->tab);
    free(tas);
}

int ajouter(int x,tas_t* tas ){
    int ereur=1;
    int i=tas->taille;
    int k;

    if (tas->taille+1<=tas->taille_max){
        tas->tab[tas->taille]=x;
        tas->taille=tas->taille+1;
        while ((i!=0)&&(x<tas->tab[(i-1)/2])){
            k=tas->tab[(i-1)/2];
            tas->tab[(i-1)/2]=x;
            tas->tab[i]=k;
            i=(i-1)/2;
        }
        ereur=0;
    }
    return ereur;
}

int retirer(tas_t * tas){
    int noeud=tas->tab[0];
    int i=tas->taille;
    int aux;

    tas->tab[0]=tas->tab[tas->taille];
    tas->taille=i-1;
    i=0;
    while((2*i+1<tas->taille)||(2*i+1<tas->taille)){
        if ((tas->tab[2*i+1]<tas->tab[i])&&(tas->tab[2*i+1]<tas->tab[2*i+2])){
            aux=tas->tab[2*i+1];
            tas->tab[2*i+1]=tas->tab[i];
            tas->tab[i]=aux;
            i=2*i+1;
        }
        else{
            if(tas->tab[2*i+2]<tas->tab[i]){
                aux=tas->tab[2*i+2];
                tas->tab[2*i+2]=tas->tab[i];
                tas->tab[i]=aux;
                i=2*i+2;
            }
        }
    }
    return noeud;
}

void perlocate_down(tas_t * tas,int i){
    int aux;

    while((2*i+1<tas->taille)||(2*i+1<tas->taille)){
        if ((tas->tab[2*i+1]<tas->tab[i])&&(tas->tab[2*i+1]<tas->tab[2*i+2])){
            aux=tas->tab[2*i+1];
            tas->tab[2*i+1]=tas->tab[i];
            tas->tab[i]=aux;
            i=2*i+1;
        }   
        else{
            if(tas->tab[2*i+2]<tas->tab[i]){
                aux=tas->tab[2*i+2];
                tas->tab[2*i+2]=tas->tab[i];
                tas->tab[i]=aux;
                i=2*i+2;
            }
        }
    }   
}
//L'opération de tamisage consiste à échanger la racine avec le plus grand de ses fils, et ainsi de suite récursivement jusqu'à ce qu'elle soit à sa place

void tamiser(int* tas,int indice,int n){ //descend la valeur d'indice donnée à sa place, sans dépasser l'indice n *
    int k=indice;                        
    int j=2*k;
    int w;
    while (j<=n){
        if ((j<n)&&(tas[j]<tas[j+1])){
            j=j+1;
        }
        if (tas[k]<tas[j]){
            w=tas[k];
            tas[k]=tas[j];
            tas[j]=w;
            k=j;
            j=2*k;
        }
        else{
            j=n+1;
        }
    }

}

void triParTas(int* tas,int taille){
    int i ;
    int k;

    for(i= (taille-1)/2;i>=0;i--){
        tamiser(tas,i,(taille-1));
        }
    for(i=(taille-1);i>0;i--){
            k=tas[i];
            tas[i]=tas[0];
            tas[0]=k;
            tamiser(tas, 0, i-1);for(int i=0;i<9;i++){
    }
    }
}
static int compare (void const *a, void const *b)
{
   /* definir des pointeurs type's et initialise's
      avec les parametres */
   int const *pa = a;
   int const *pb = b;

   /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
   return *pa - *pb;
}

int main(){
    tas_t *tas=initas(20);
    clock_t seconds;
    clock_t seconds2;    
    clock_t temps1;
    clock_t temps2;
    int k;


    ajouter(0,tas);
    ajouter(3,tas);
    ajouter(36,tas);
    ajouter(9,tas);
    ajouter(7,tas);
    ajouter(6,tas);
    ajouter(7,tas);
    ajouter(11,tas);
    ajouter(20,tas);
    ajouter(40,tas);
    ajouter(2,tas);
    ajouter(0,tas);
    ajouter(26,tas);
    ajouter(53,tas);
    int tab[100000];
    int tab2[100000];


    srand(time(0));
    for(int i=0;i<100000;++i){
        k=rand()%1000;
        tab[i]=k;
        tab2[i]=k;
    }
    /*
    for (int i=0;i<tas->taille;++i){
        printf("%d\n",tas->tab[i]);
    }
    triParTas(tas->tab,tas->taille);
    for (int i=0;i<tas->taille;++i){
        printf("%d\n",tas->tab[i]);
    }
    for (int i=0;i<20;++i){
        printf("%d\n",tab[i]);
    }
    */
    seconds=clock();
    qsort(tab, 100000 ,sizeof *tab, compare);

    
    seconds2=clock();
    temps1=seconds2-seconds;

    seconds=clock();
    triParTas(tab2,100000);


    seconds2=clock();
    temps2=seconds2-seconds;
    printf("%ld\n",temps2-temps1);
    /*
    for (int i=0;i<100000;++i){
        printf("%d ",tab2[i]);
    }
   
    printf("\n ");
    */
    printf("tp classic: %ld\ntp tas: %ld\n",temps1,temps2);

    liberer_tas(tas);
    return 0;
}   