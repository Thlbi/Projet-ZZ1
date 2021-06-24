#include "DFS.h"

void explorer(int ** laby,int sommet, int * som, int *explo)
{
	som[sommet]=-1;
	explo[explo[0]]=sommet;
	explo[0]+=1;
	if (laby[sommet%P][sommet/P] & FLAG_N)
		if (som[sommet-P]!=-1)
			explorer(laby,sommet-P,som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_S)
		if (som[sommet+P]!=-1)
			explorer(laby,sommet+P,som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_O)
		if (som[sommet-1]!=-1)
			explorer(laby,sommet-1,som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_E)
		if (som[sommet+1]!=-1)
			explorer(laby,sommet+1,som,explo);
}


int * DFS(int ** laby,int noeuds)
{
	int * explo=malloc((noeuds+1)*sizeof(int));
	explo[0]=1;
	int * som=malloc(noeuds*sizeof(int));
	for (int i =0; i<noeuds; i++)
		som[i]=0;
	for (int i=0; i<noeuds; i++)
			if (som[i]!=-1)
				explorer(laby,i,som,explo);
	return explo;
}
