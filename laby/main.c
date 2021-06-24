/*main.c*/
/*15 juin 2021*/
/*make*/

#include "main.h"

void end_sdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
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

	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);

	SDL_Quit();

	if (!ok)
		exit(EXIT_FAILURE);
}

void afficherEcranIntelligemment(SDL_Renderer *renderer, int **tab, int taille_cell)
{
	int x = 0;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0, &screen);
	int decalage_horizontale = (screen.w / taille_cell - P) * taille_cell / 3;
	int decalage_vertical = (screen.h / taille_cell - N) * taille_cell / 20;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	int i1, j1, noeud = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < P; j++)
		{
			x = tab[j][i];
			i1 = (noeud % P);
			j1 = ((int)noeud / P);

			if (!(x & FLAG_N))
			{
				SDL_RenderDrawLine(renderer, i1 * taille_cell + decalage_horizontale, j1 * taille_cell + decalage_vertical, (i1 + 1) * taille_cell + decalage_horizontale, j1 * taille_cell + decalage_vertical); //mur au nord
			}
			if ((x & FLAG_S) != 2)
				SDL_RenderDrawLine(renderer, i1 * taille_cell + decalage_horizontale, (j1 + 1) * taille_cell + decalage_vertical, (i1 + 1) * taille_cell + decalage_horizontale, (j1 + 1) * taille_cell + decalage_vertical); //mur au sud
			if ((x & FLAG_E) != 4)
				SDL_RenderDrawLine(renderer, (i1 + 1) * taille_cell + decalage_horizontale, j1 * taille_cell + decalage_vertical, (i1 + 1) * taille_cell + decalage_horizontale, (j1 + 1) * taille_cell + decalage_vertical); //mur à l'est
			if ((x & FLAG_O) != 8)
				SDL_RenderDrawLine(renderer, i1 * taille_cell + decalage_horizontale, j1 * taille_cell + decalage_vertical, i1 * taille_cell + decalage_horizontale, (j1 + 1) * taille_cell + decalage_vertical); //mur à l'ouest

			noeud += 1;
		}
	}
}

int min(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}

int main(int argc, char **argv)
{
	double p;
	SDL_Rect source = {0};

	//l'argument p regit l'affichage des murs : s'il vaut 0 il n'y a aucun mur, s'il vaut un on a un arbre
	if (argc == 2)
		p = atof(argv[1]);
	else
		p = 0.75;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0, &screen);
	SDL_Window *window;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h, SDL_WINDOW_RESIZABLE);

	if (window == 0)
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());

	SDL_SetWindowTitle(window, "Labyrinthe");

	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == 0)
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	int running = 1;
	srand(time(0));
	int noeuds = N * P;
	int nb_aretes = 2 * N * P - N - P;
	int **tab;
	int cours = 0;
	int taille_cell = min(screen.w / (P + 2), screen.h / (N + 2));
	//int * tab_parents;  à décommenter pour l'utilisation de Dijkstra
	//initialisation du graph
	graph_t *graph = creer_graph(noeuds, nb_aretes);
	generation(graph);
	graph = Fisher(graph, nb_aretes);
	graph = kruskal(graph, noeuds, nb_aretes, &cours, p);
	tab = tableau_ligne(graph, cours);

	//initialisation des differentes textures
	SDL_Texture *texture, *texture_fin, *texture_elve, *texture_elve_reverse;

	texture_elve = load_texture_from_image("Elve_lign.png", renderer);
	if (texture_elve == NULL)
		end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

	texture_elve_reverse = load_texture_from_image("Elve_ligne_reverse.png", renderer);
	if (texture_elve_reverse == NULL)
		end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

	texture = load_texture_from_image("road.png", renderer);
	if (texture == NULL)
		exit(EXIT_FAILURE);

	texture_fin = load_texture_from_image("roguelikeChar_transparent.png", renderer);
	if (texture_fin == NULL)
		exit(EXIT_FAILURE);

	//tab_parents=dijkstra(tab,graph->noeuds,ND_ARRIVEE);

	SDL_Event event;

	//on initialise une fenêtre 2 pour une mini-map
	SDL_Window *window2;

	window2 = SDL_CreateWindow("SDL2 Programme 0.1", screen.w - screen.w / 3, 0, screen.w / 3, screen.h / 4, SDL_WINDOW_RESIZABLE);

	if (window2 == 0)
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());

	SDL_SetWindowTitle(window2, "Carte d'exploration");

	//on initialise le renderer de la mini-map
	SDL_Renderer *renderer2;
	renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer2 == 0)
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());

	//on initialise les textures pour la deuxième fenêtre
	SDL_Texture *texture2, *texture_fin2;

	texture2 = load_texture_from_image("road.png", renderer2);
	if (texture2 == NULL)
		exit(EXIT_FAILURE);

	texture_fin2 = load_texture_from_image("roguelikeChar_transparent.png", renderer2);
	if (texture_fin2 == NULL)
		exit(EXIT_FAILURE);

	SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

	float zoom = (float)taille_cell / (float)32;

	int largeur_elve = source.w / 8 * zoom;

	int hauteur_elve = source.h * zoom;

	int pause = 1;
	int noeud_dep = rand() % TAILLE;
	int right = 1;
	int pos_x = noeud_dep % P * taille_cell;
	int pos_y = noeud_dep / P * taille_cell;
	int temps = 1;
	int deplacement = taille_cell;
	int noeud_arrive = rand() % TAILLE;
	int colli;
	int noeud_actuel;
	int taille_cell2 = min((screen.w / 3) / (P + 2), (screen.h / 3) / (N + 2));

	affichage_fin(texture_fin2, window2, renderer2, noeud_arrive / P, noeud_arrive % P, taille_cell2);
	printf("l : relancer \np,SPACE : pause \ncroix : quitter\n");
	while ((running) || (temps < 50))
	{
		noeud_actuel=pos_x/taille_cell+(pos_y/taille_cell)*P;
		if (noeud_actuel == noeud_arrive)
			running = 0;
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
					temps = 1000;
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					screen.w = event.window.data1;
					screen.h = event.window.data2;
					break;
				case SDL_WINDOWEVENT_EXPOSED:
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_l:
					noeud_dep = rand() % TAILLE;
					right = 1;
					pos_x = noeud_dep % P * taille_cell;
					pos_y = noeud_dep / P * taille_cell;
					temps = 1;
					noeud_arrive = rand() % TAILLE;
					break;
				case SDLK_SPACE:
				case SDLK_p:
					pause = 1 - pause;
					break;
				case SDLK_m: //la fonction devra afficher la totalite du labyrinthe sans brouillard de guerre
					afficherImage(renderer, window, tab, taille_cell2, texture);
					affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
					SDL_RenderPresent(renderer);
					SDL_Delay(2000);
					SDL_RenderClear(renderer);
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		const Uint8 *keystates = SDL_GetKeyboardState(NULL);
		if (pause)
		{
			peindreMap(texture2, window2, renderer2, noeud_actuel, taille_cell2, tab);
			SDL_RenderPresent(renderer2);
			if ((keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]))
			{
				colli = collision_N(pos_x, pos_y, tab, taille_cell, largeur_elve, deplacement);
				if (!colli)
				{
					if (right)
					{
						play_with_elve_N(texture_elve, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					}
					else
					{
						play_with_elve_N_l(texture_elve_reverse, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					}
					pos_y = pos_y - deplacement / 10; //deplacement de deplacement/nb_image_aniamtion a chaque frame
				}
			}
			if ((keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]))
			{
				colli = collision_S(pos_x, pos_y, tab, taille_cell, largeur_elve, hauteur_elve, deplacement);
				if (!colli)
				{
					if (right)
					{
						play_with_elve_S(texture_elve, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					}
					else
					{
						play_with_elve_S_l(texture_elve_reverse, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					}
					pos_y = pos_y + deplacement / 10;
				}
			}
			if ((keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]))
			{
				colli = collision_O(pos_x, pos_y, tab, taille_cell, hauteur_elve, deplacement);
				if (!colli)
				{
					play_with_elve_O(texture_elve_reverse, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					pos_x = pos_x - deplacement / 10;
					right = 0;
				}
			}
			if ((keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]))
			{
				colli = collision_E(pos_x, pos_y, tab, taille_cell, largeur_elve, hauteur_elve, deplacement);
				if (!colli)
				{
					play_with_elve_E(texture_elve, texture, window, renderer, pos_x, pos_y, deplacement, zoom, tab, taille_cell, texture_fin, noeud_arrive);
					pos_x = pos_x + deplacement / 10;
					right = 1;
				}
			}
			/*
			else
			{
				if (right)
				{
					play_standstill(texture_elve, texture, window, renderer, pos_x, pos_y, zoom, tab, taille_cell, texture_fin, noeud_arrive);
				}
				else
				{
					play_standstill_l(texture_elve_reverse, texture, window, renderer, pos_x, pos_y, zoom, tab, taille_cell, texture_fin, noeud_arrive);
				}
			}
			*/
			SDL_RenderPresent(renderer);
			SDL_Delay(30);
			if (running == 0)
			{
				temps++;
			}
		}
	}

	SDL_DestroyTexture(texture_elve_reverse);
	SDL_DestroyTexture(texture_elve);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture_fin);
	end_sdl(1, "Normal ending", window, renderer);
	end_sdl(1, "Normal ending", window2, renderer2);
	return 1;
}
