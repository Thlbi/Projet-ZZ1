typedef struct cellule{
	int num_serpent;
	int x;
	int y;
	struct cellule * suiv;
}cellule_t;

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer);
void dessin(SDL_Renderer* renderer,cellule_t ** tab,int numero_serpent,int aleat);
int main ();
cellule_t * allouer(int num_serpent,int x,int y);
void adj_cell(cellule_t **prec,cellule_t *nouv);
void SuppCell(cellule_t **prec);

