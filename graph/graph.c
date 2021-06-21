#include "graph.h"



graph_t *  initgraph(int noyau){
    graph_t* graph=malloc(sizeof(graph_t));
    graph->Nb_Noyau=noyau;

    return graph;
}
arete_t * allouer(int coord1,int coord2,int poids){
	arete_t *nouv=(arete_t *)malloc(sizeof(arete_t));
	if (nouv!=NULL){
		nouv->sommet1=coord1;
		nouv->sommet2=coord2;
		nouv->poids=poids;
	}
	return nouv;
}


void ajouter_arete(graph_t*graph,int sommet1,int sommet2,int poids){
    arete_t *arete_nouv=malloc(sizeof(arete_t));
    arete_t *cour=graph->suiv;
    arete_t *prec;
    arete_nouv->sommet1=sommet1;
    arete_nouv->sommet2=sommet2;
    arete_nouv->poids=poids;
    if (cour==NULL){
        graph->suiv=arete_nouv;
    }

    else{
        if(cour->poids>=poids){
            arete_nouv->suiv=cour;
            graph->suiv=arete_nouv;
        }
        prec=cour;
        cour=cour->suiv;
        while((cour!=NULL)&&(cour->poids<poids)){
            prec=cour;
            cour=cour->suiv;
        }
        prec->suiv=arete_nouv;
        arete_nouv->suiv=cour;  
    } 
}



void afficher_graph(graph_t*graph){
	FILE *fichier;
    arete_t *arete=graph->suiv;
	fichier=fopen("graph.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
	for (int i=0; i<graph->Nb_Noyau ;i++){
        fprintf(fichier,"%d",i);
		fprintf(fichier,";");
    }
	
    while(arete->suiv!=NULL)
    {   
		fprintf(fichier,"%d",arete->sommet1);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",arete->sommet2);
        fprintf(fichier,"[label=");
		fprintf(fichier,"%d",arete->poids);
		fprintf(fichier,"];\n");
        arete=arete->suiv;
	}
	fprintf(fichier, "}");
	fclose(fichier);

}

void afficher_arete(arete_t *arete){
	FILE *fichier;

	fichier=fopen("graph6.dot","w");
	if (fichier==NULL)
		printf("echec de louverture du fichier\n");
	else 
		fprintf(fichier,"graph Nom{\n");
    while(arete->suiv!=NULL)
    {   
		fprintf(fichier,"%d",arete->sommet1);
		fprintf(fichier,"--");
		fprintf(fichier,"%d",arete->sommet2);
        fprintf(fichier,"[label=");
		fprintf(fichier,"%d",arete->poids);
		fprintf(fichier,"];\n");
        arete=arete->suiv;
	}
	fprintf(fichier, "}");
	fclose(fichier);
    
}


void generer_couple(graph_t *graph){
		int x;	
        int taille=graph->Nb_Noyau;
        srand(time(0));
		for (int i=0;i<taille;i++){
			for (int j=i+1;j<taille;j++){
				x=rand()%3;
				if (x==1){
                    ajouter_arete(graph,i,j,rand()%90);
				}
			}
		}
}

arete_t * kruskal(graph_t *graph){
    int noyau=graph->Nb_Noyau;
    arete_t *A=NULL;
    arete_t *nouv;
    partition_t *part=creer(noyau);
    arete_t *cour=graph->suiv;
    int sommet1;
    int sommet2;
    
    while(cour!=NULL){
        sommet1=cour->sommet1;
        sommet2=cour->sommet2;
        if(recuperer_classe(sommet1,part)!=recuperer_classe(sommet2,part)){
            fusion(sommet1,sommet2,part);
            nouv=allouer(sommet1,sommet2,cour->poids);
            nouv->suiv=A;
            A=nouv;
            
        }
        cour=cour->suiv;
    }
    return A;
}

int main(){
    graph_t *graph=initgraph(10);
    
    generer_couple(graph);
    /*
    printf("%d\n",(graph->suiv)->poids);
    printf("%d\n",(graph->suiv)->suiv->poids);
    */
    afficher_graph(graph);
    arete_t *A=kruskal(graph);
    afficher_arete(A);
    system("dot -Tpng graph6.dot -o graph6.png");
    system("dot -Tpng graph.dot -o graph.png");
	system("display graph6.png &");
	system("display graph.png &");

    return 0;
}