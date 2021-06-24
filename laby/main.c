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

void peindreDFS(SDL_Renderer * renderer, int noeuds, int taille_cell)
{
 		SDL_DisplayMode screen;
		SDL_GetCurrentDisplayMode(0,&screen);
		int decalage_horizontale=(screen.w/taille_cell-P)*taille_cell/3;
		int decalage_vertical=(screen.h/taille_cell-N)*taille_cell/4;
		SDL_Rect rectangle;
		
		int x=noeuds%P;
		int y=noeuds/P;
		SDL_SetRenderDrawColor(renderer, 0,255,0,0);
		
		rectangle.x=taille_cell*x+ decalage_horizontale;
		rectangle.y=taille_cell*y+ decalage_vertical;
		rectangle.h=rectangle.w=taille_cell;	
		
		SDL_RenderFillRect(renderer, &rectangle);
}

void peindreDFSGraphique(SDL_Texture * texture, SDL_Window* window ,SDL_Renderer *renderer, int noeuds, int taille_cell, int ** laby)
{
	affichage_texture(texture,window, renderer, laby[noeuds%P][noeuds/P], noeuds%P, noeuds/P, taille_cell);
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

		cours=arrivee;
		SDL_SetRenderDrawColor(renderer, 0,0,255,0);
		rectangle.x=taille_cell*(cours%P)+decalage_horizontale;
		rectangle.y=taille_cell*(cours/P)+decalage_vertical;
		rectangle.w=rectangle.h=taille_cell;
		SDL_RenderFillRect(renderer, &rectangle);

		cours=parent[depart];
		SDL_SetRenderDrawColor(renderer, 255,0,0,0);
		while(cours!=arrivee)
		{
			rectangle.x=taille_cell*(cours%P)+decalage_horizontale;
			rectangle.y=taille_cell*(cours/P)+decalage_vertical;
			rectangle.w=rectangle.h=taille_cell;
			SDL_RenderFillRect(renderer, &rectangle);
			cours=parent[cours];
			SDL_RenderPresent(renderer);
			SDL_Delay(20);
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
	SDL_Texture * texture,*texture_fin,* texture_elve,* texture_elve_reverse;

	texture_elve = load_texture_from_image("Elve_lign.png",renderer);
	if (texture_elve == NULL)
	{
		printf("erreur texture Elve_lign.png\n");
		exit(EXIT_FAILURE);
	}	
	texture_elve_reverse = load_texture_from_image("Elve_ligne_reverse.png",renderer);
	if (texture_elve_reverse == NULL) 
	{
		printf("erreur texture Elve_lign_reverse.png\n");
		exit(EXIT_FAILURE);
	}	
	
	texture = load_texture_from_image("road.png",renderer);
	if (texture==NULL) 
	{
		printf("erreur texture road.png\n");
		exit(EXIT_FAILURE);
	}	

	texture_fin = load_texture_from_image("roguelikeChar_transparent.png",renderer);
	if (texture_fin==NULL) 
	{
		printf("erreur texture roguelikechar.png\n");
		exit(EXIT_FAILURE);
	}	

	int running=1;
	srand(0);
	int noeuds=N*P;
	int nb_aretes=2*N*P-N-P;
	int **tab;
	int *parent;
	int cours=0;
	int depart=0;
	int arrivee=12;
	int * explo;
	int taille_cell=min(screen.w/(P+2),screen.h/(N+2));
	//printf("%d \n", taille_cell);
	graph_t * graph=creer_graph(noeuds,nb_aretes);
	generation(graph);
	graph=Fisher(graph,nb_aretes);
	graph=kruskal(graph,noeuds,nb_aretes,&cours,p);
	tab=tableau_ligne(graph,cours);

	explo=DFS(tab,noeuds);
	int temps=600;
	int i=1;
	int nouv_noeuds=0;
	int pause=0;
	int direction=0;
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
					
				case SDL_KEYDOWN:  
					switch (event.key.keysym.sym) 
					{  
      				case SDLK_p:                 
      				case SDLK_SPACE:            
        					pause = !pause;       
        					break;
						case SDLK_ESCAPE:
							running = 0;
        					break;
						case SDLK_d:  /*on va a droite*/
							direction = 1;
        					break;
						case SDLK_q: /*on va a gauche*/
							direction = 2;
        					break;
						case SDLK_z:  /*on va en haut*/
							direction = 3;
        					break;
						case SDLK_s:  /*on va en bas*/
							direction = 4;
							break;
						default:
							break;
      			}
      			break;
			}
		}
			peindreDFSGraphique(texture,window,renderer,0,taille_cell,tab);
		if (direction)
		{
			if (direction==1 && (tab[nouv_noeuds%P][nouv_noeuds/P] & FLAG_E))
				nouv_noeuds=nouv_noeuds+1;
			if (direction==2 && (tab[nouv_noeuds%P][nouv_noeuds/P] & FLAG_O))
				nouv_noeuds=nouv_noeuds-1;
			if (direction==3 && (tab[nouv_noeuds%P][nouv_noeuds/P] & FLAG_N))
				nouv_noeuds=nouv_noeuds-P;
			if (direction==4 && (tab[nouv_noeuds%P][nouv_noeuds/P] & FLAG_S))
				nouv_noeuds=nouv_noeuds+P;
			peindreDFSGraphique(texture,window,renderer,nouv_noeuds,taille_cell,tab);
			direction=0;
		}
			
/*
			if (temps>100)
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

			if (i==1)
			{
				afficherEcranIntelligemment(renderer,tab,taille_cell);
			}
			if  (i<=noeuds)
			{
				peindreDFS(renderer,explo[i],taille_cell);
				peindreDFSGraphique(texture,window,renderer,explo[i],taille_cell,tab);
				i++;
			}
			else
			{
				SDL_Delay(8000);
				running=0;
			}*/
			SDL_RenderPresent(renderer);
			SDL_Delay(20);
	}
	end_sdl(1, "Normal ending", window, renderer);
	return 1;
}
                                     

