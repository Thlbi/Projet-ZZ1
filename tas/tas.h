typedef struct tas{
	int * tab;
	int rang_dernier;
	int taille;
}tas_t;

void init_tas_min(tas_t * t,int valeur);
void percolation(tas_t * t,int rang);
void tri_par_tas(tas_t * t);
void affichage(tas_t *t);
int main();
