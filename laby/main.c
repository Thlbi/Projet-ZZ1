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
	int i1,j1,x,noeud=0;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);

	for (int i=0;i<N;i++)
	{
	
		for (int j=0;j<P;j++)
		{
			x=tab[i][j];
			i1=(noeud%P)+1;
			j1=(noeud/P)+1;
			printf("%d %d \n",noeud,x);

			if (x%2!=1)
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,j1*taille_cell+50,(i1+1)*taille_cell+50,j1*taille_cell+50); //mur au nord
			if ((x!=2) && (x!=3) && (x!=6) && (x!=7) && (x!=10) && (x!=11) && (x!=14) && (x!=15))
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,(j1+1)*taille_cell+50,(i1+1)*taille_cell+50,(j1+1)*taille_cell+50); //mur au sud
			if ((x!=4) && (x!=5) && (x!=6) && (x!=7) && (x!=12) && (x!=13) && (x!=14) && (x!=15)) 
				SDL_RenderDrawLine(renderer,(i1+1)*taille_cell+50,j1*taille_cell+50,(i1+1)*taille_cell+50,(j1+1)*taille_cell+50); //mur à l'est
			if (x<8)
				SDL_RenderDrawLine(renderer,i1*taille_cell+50,j1*taille_cell+50,i1*taille_cell+50,(j1+1)*taille_cell+50); //mur à l'ouest
			
			noeud+=1;
		
		}
	}

        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        SDL_RenderClear(renderer);
}



int main ()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	int width = 800;
	int height =900;
	SDL_Window *window;
	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height, SDL_WINDOW_RESIZABLE);
	if (window == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	SDL_SetWindowTitle(window, "Mon_chef d'oeuvre");

	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
  
	int running=1;
	srand(time(0));
	int noeuds=N*P;
	int nb_aretes;
	int **tab;
	graph_t * graph=creer_graph(noeuds,100);
	partition_t * part=creer(noeuds);
	nb_aretes=generation(graph,4,5);
	graph=Fisher(graph,nb_aretes);
	affiche_graph_couple(graph,noeuds,nb_aretes);
	graph=kruskal(graph,noeuds,nb_aretes,&cours);
	affiche_graph_couple(graph,noeuds,nb_aretes);
	tab=tableau_ligne(graph,nb_aretes);

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
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						width = event.window.data1;
						height = event.window.data2;
						break;
					case SDL_WINDOWEVENT_EXPOSED:
						break;
					}
					break;
			break;
			}
		}
		afficherEcranIntelligemment(renderer,tab,100);
		SDL_RenderClear(renderer);
		SDL_Delay(30);
		SDL_RenderPresent(renderer);
	}
	end_sdl(1, "Normal ending", window, renderer);
	return 1;
}
                                     

