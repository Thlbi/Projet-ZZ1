/*main.c*/
/*15 juin 2021*/
/*make*/

#include "main.h"

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer)
{
	char msg_formated[255];
	int l;

	if (!ok) 
	{	                             
		strncpy(msg_formated, msg, 250);
		l = strlen(msg_formated);           
		strcpy(msg_formated + l, " : %s\n");
		SDL_Log(msg_formated, SDL_GetError());
	}

	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL)   SDL_DestroyWindow(window);

	SDL_Quit();

	if (!ok) exit(EXIT_FAILURE);
}
void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab,int taille_cell)
{
	int x=0;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
 	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0,&screen);
	int decalage_horizontale=(screen.w/taille_cell-P)*taille_cell/3;
	int decalage_vertical=(screen.h/taille_cell-N)*taille_cell/4;

	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	int i1,j1,noeud=0;
	
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<P;j++)
		{
			x=tab[j][i];
			i1=(noeud%P);
			j1=((int)noeud/P);

			if (!(x & FLAG_N))
				SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical); //mur au nord
			if ((x & FLAG_S)!=2)
				SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur au sud
			if ((x & FLAG_E)!=4)
				SDL_RenderDrawLine(renderer,(i1+1)*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur à l'est
			if ((x & FLAG_O)!=8)
				SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,i1*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur à l'ouest

			noeud+=1;

		}
	}
}

void chemin(SDL_Renderer * renderer, int depart, int arrivee, int taille_cell,int *parent)
{
 		SDL_DisplayMode screen;
		SDL_GetCurrentDisplayMode(0,&screen);
		int decalage_horizontale=(screen.w/taille_cell-P)*taille_cell/3;
		int decalage_vertical=(screen.h/taille_cell-N)*taille_cell/4;
		SDL_Rect rectangle;
		int cours=depart;
		SDL_SetRenderDrawColor(renderer, 0,255,0,0);
		rectangle.x=taille_cell*(cours%P)+decalage_horizontale;
		rectangle.y=taille_cell*(cours/P)+decalage_vertical;
		rectangle.w=rectangle.h=taille_cell;
		SDL_RenderFillRect(renderer, &rectangle);
		cours=parent[cours];
		SDL_SetRenderDrawColor(renderer, 255,0,0,0);
		while(cours!=arrivee)
		{
			rectangle.x=taille_cell*(cours%P)+decalage_horizontale;
			rectangle.y=taille_cell*(cours/P)+decalage_vertical;
			rectangle.w=rectangle.h=taille_cell;
			SDL_RenderFillRect(renderer, &rectangle);
			cours=parent[cours];
		}
		cours=arrivee;
		SDL_SetRenderDrawColor(renderer, 0,0,255,0);
		rectangle.x=taille_cell*(cours%P)+decalage_horizontale;
		rectangle.y=taille_cell*(cours/P)+decalage_vertical;
		rectangle.w=rectangle.h=taille_cell;
		SDL_RenderFillRect(renderer, &rectangle);
}

int min(int a, int b)
{
	if (a>b)
		return b;
	else
		return a;
}	


int main (int argc, char** argv)
{
	double p;
	if (argc==2)  p=atof(argv[1]);
	else p=1; 
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

 	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0,&screen);
	SDL_Window *window;
	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,screen.w,screen.h, SDL_WINDOW_RESIZABLE);
	if (window == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	SDL_SetWindowTitle(window, "Mon_chef d'oeuvre");

	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	int running=1;
	srand(0);
	int noeuds=N*P;
	int nb_aretes=2*N*P-N-P;
	int **tab;
	int *parent;
	int cours=0;
	int depart=0;
	int arrivee=12;
	int taille_cell=min(screen.w/(P+2),screen.h/(N+2));
	//printf("%d \n", taille_cell);
	graph_t * graph=creer_graph(noeuds,nb_aretes);
	generation(graph);
	graph=Fisher(graph,nb_aretes);
	graph=kruskal(graph,noeuds,nb_aretes,&cours,p);
	tab=tableau_ligne(graph,cours);
	int temps=600;
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event)
					{
					case SDL_WINDOWEVENT_CLOSE:
						running = 0;
						break;
					}
					break;
			break;
			}
			if (temps>600)
			{
				temps=0;
				SDL_RenderClear(renderer);
				afficherEcranIntelligemment(renderer,tab,taille_cell);
				depart=arrivee;
				arrivee=rand()%noeuds;
				parent=dijsktra(tab,noeuds,arrivee);
				chemin(renderer,depart, arrivee, taille_cell, parent);
			}
			else
				temps+=10;
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}
	}
	end_sdl(1, "Normal ending", window, renderer);
	return 1;
}
                                     

