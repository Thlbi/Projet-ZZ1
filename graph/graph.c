#include "graph.h"



graph_t *  initgraph(int noyau){
    graph_t* graph=malloc(sizeof(graph_t));
    graph->Nb_Noyau=noyau;

    return graph;
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
    system("dot -Tpng graph.dot -o graph.png");
	system("display graph.png ");
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

partition_t * kruskal(graph_t *graph){
    int noyau=graph->Nb_Noyau;
    partition_t *part=creer(noyau);
    arete_t *cour=graph->suiv;
    int sommet1;
    int sommet2;
    
    while(cour!=NULL){
        sommet1=cour->sommet1;
        sommet2=cour->sommet2;
        if(recuperer_classe(sommet1,part)!=recuperer_classe(sommet2,part)){
            fusion(sommet1,sommet2,part);
        }
        cour=cour->suiv;
    }
    return part;
}

int main(){
    graph_t *graph=initgraph(10);
    
    generer_couple(graph);
    /*
    printf("%d\n",(graph->suiv)->poids);
    printf("%d\n",(graph->suiv)->suiv->poids);
    */
    afficher_graph(graph);
    partition_t *part=kruskal(graph);
    aff_graph(part,graph->Nb_Noyau);

    return 0;
}