#include "DFS.h"

void explorer(int ** laby,int sommet, int * som, int *explo)
{
	som[sommet]=-1;
	explo[explo[0]]=sommet;
	explo[0]+=1;
	if (laby[sommet%P][sommet/P] & FLAG_N)
		if (som[laby[sommet%P][sommet/P]]!=-1)
			explorer(laby,laby[sommet%P][sommet/P],som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_S)
		if (som[laby[sommet%P][sommet/P]]!=-1)
			explorer(laby,laby[sommet%P][sommet/P],som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_O)
		if (som[laby[sommet%P][sommet/P]]!=-1)
			explorer(laby,laby[sommet%P][sommet/P],som,explo);
	if (laby[sommet%P][sommet/P] & FLAG_E)
		if (som[laby[sommet%P][sommet/P]]!=-1)
			explorer(laby,laby[sommet%P][sommet/P],som,explo);
}


int * DFS(int ** laby,int noeuds)
{
	int * explo=malloc((noeuds+1)*sizeof(int));
	explo[0]=1;
	int * som=malloc(noeuds*sizeof(int));
	for (int i =0; i<noeuds; i++)
		som[i]=0;
	for (int i=0; i<noeuds; i++)
			explorer(laby,laby[0][0],som,explo);
	return explo;
}
