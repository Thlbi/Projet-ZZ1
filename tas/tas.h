typedef struct tas{
	int * tab;
	int rang_dernier;
	int taille;
}tas_t;

void init_tas(tas_t * t,int valeur);
void percolation(tas_t * t,int noeud, int taille);
void tri_par_tas(tas_t * t,int taille);
int main();
