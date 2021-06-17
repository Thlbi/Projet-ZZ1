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
  
	SDL_Texture* texture_vaisseau = NULL;
	SDL_Texture* texture_vaisseau2 = NULL;
	SDL_Texture* texture_vaisseau3 = NULL;
	SDL_Texture* texture_meteore = NULL;
	SDL_Texture* bg_texture = NULL;
	SDL_Texture* image = NULL;
  
	texture_vaisseau = load_texture_from_image("images/redfighter0005.png",window,renderer);
	if (texture_vaisseau == NULL) end_sdl2(0, "Echec du chargement de l'image dans la texture", window, renderer);
	texture_vaisseau2 = load_texture_from_image("images/redfighter0001.png",window,renderer);
	if (texture_vaisseau2 == NULL) end_sdl2(0, "Echec du chargement de l'image dans la texture", window, renderer);
	texture_vaisseau3 = load_texture_from_image("images/redfighter0009.png",window,renderer);
	if (texture_vaisseau3 == NULL) end_sdl2(0, "Echec du chargement de l'image dans la texture", window, renderer);
	texture_meteore = load_texture_from_image("images/buttons.png",window,renderer);
	if (texture_meteore == NULL) end_sdl2(0, "Echec du chargement de l'image dans la texture", window, renderer);
	bg_texture = load_texture_from_image("images/Nebula Aqua-Pink.png",window,renderer);
	if (bg_texture == NULL) end_sdl2(0, "Echec du chargement de l'image dans la texture", window, renderer);


	int largeur = width/5, longueur =height/5;
   int running=1, pause=1, pos=0;
	int posvaisseau=0, gen=1, nb_lignes=0, coli=0, efface=0, creation_met=0;

	int met[longueur/HAUTEUR_MET][NB_MET];
	int ** grille;
	grille=init_grille(largeur,longueur);
	posvaisseau=init_tab(grille,largeur,longueur);
	srand(time(0));

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
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_SPACE:
						case SDLK_p:
							pause=1-pause;
							break;
						case SDLK_LEFT:
						case SDLK_q:
							pos=-1;
							image=texture_vaisseau2;
							break;
						case SDLK_RIGHT:
						case SDLK_d:
							pos=1;
							image=texture_vaisseau3;
							break;
						default: 
							break;
					}
					break;
			break;
			}
      }
	if (!pause)
	{
		gen+=1;
		creation_met+=1;
		position_vaisseau(grille, &posvaisseau,longueur,largeur,pos);
		if (gen==HAUTEUR_MET)
		{
			if (nb_lignes!=longueur/HAUTEUR_MET)
			{
				creation_met=0;
				nb_lignes+=1;
			}
			else 
				efface+=1;
			gen=0;
		}
		coli=gestion_meteorites(grille,largeur,longueur,posvaisseau,creation_met, met,nb_lignes);

		SDL_RenderClear(renderer);
		background(bg_texture,window,renderer);
		play_with_texture_vaisseau(image,window,renderer,5*posvaisseau);
		for (int j=efface; j<nb_lignes+1; j++)
		{
			for (int i=0; i<NB_MET;i++)
			{
   			play_with_meteore(texture_meteore,window,renderer, PIXEL*met[j][i], PIXEL*HAUTEUR_MET*(nb_lignes-j+efface)+PIXEL*gen);
			}
		}

		SDL_Delay(30);
		SDL_RenderPresent(renderer);
		pos=0;
		image=texture_vaisseau;
	}
	if (coli)
	{
		SDL_RenderClear(renderer);
		affichage_texte(0, window, renderer);
		SDL_RenderPresent(renderer);
		running=0;
		SDL_Delay(1000);
	}
	if (efface>=longueur/HAUTEUR_MET)
	{
		SDL_RenderClear(renderer);
		affichage_texte(1, window, renderer);
		SDL_RenderPresent(renderer);
		running=0;
		SDL_Delay(1000);
	}	
	SDL_Delay(5);
	}
	SDL_DestroyTexture(texture_meteore);
	SDL_DestroyTexture(texture_vaisseau);
	SDL_DestroyTexture(texture_vaisseau2);
	SDL_DestroyTexture(texture_vaisseau3);
	IMG_Quit();
	TTF_Quit();
   end_sdl(1, "Normal ending", window, renderer);
	liberer(grille,largeur);
	return 1;
}
                                     

