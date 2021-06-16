/*main.c*/
/*15 juin 2021*/
/*make*/

#include "main.h"

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer)
{
  char msg_formated[255];
  int l;

  if (!ok) {                             
         strncpy(msg_formated, msg, 250);
         l = strlen(msg_formated);           
         strcpy(msg_formated + l, " : %s\n");

         SDL_Log(msg_formated, SDL_GetError());
  }

  if (renderer != NULL) SDL_DestroyRenderer(renderer);
  if (window != NULL)   SDL_DestroyWindow(window);

  SDL_Quit();

  if (!ok) {                
         exit(EXIT_FAILURE);
  }
}


int main ()
{


   if (SDL_Init(SDL_INIT_VIDEO) == -1)
   {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            return EXIT_FAILURE;
      }
   SDL_Window *window;
      int width = 900;
      int height =900;
      int largeur = width/5;
      int longueur =height/5;
		int ** grille;
		grille=init_grille(largeur,longueur);

   window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height, SDL_WINDOW_RESIZABLE);

   if (window == 0)
      {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
         /* on peut aussi utiliser SDL_Log() */
      }
      SDL_SetWindowTitle(window, "Jeu_de_la_vie");
      SDL_Renderer *renderer;

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
      if (renderer == 0)
      {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
      }
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


   SDL_Event event;
   int running=1;
	int pause=1;
	int posvaisseau=0;
	posvaisseau=init_tab(grille,largeur,longueur);
	int pos=0;
	int gen=1;
	int regen=0;
	int coli=0;
	int met[longueur/HAUTEUR_MET][NB_MET];
	int efface=0;
	int creation_met=0;
	srand(time(0));

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
								//	printf("pause\n");
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
							/*case SDL_MOUSEBUTTONDOWN:
 							if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) )
							{
							}
								break;
							default:*/
								break;
								 
         			}
      	}
		if (!pause)
		{
			//printf("%d\n",pos);
			position_vaisseau(grille, &posvaisseau,longueur,largeur,pos);
			//printf("%d\n",posvaisseau);
			gen+=1;
			creation_met+=1;
			if (gen==HAUTEUR_MET)
			{
				if (regen!=11)
					creation_met=0;
				gen=0;
				regen+=1;
			}
			coli=gestion_meteorites(grille,largeur,longueur,posvaisseau,creation_met, met,regen);
			background(bg_texture,window,renderer);
			play_with_texture_vaisseau(image,window,renderer,5*posvaisseau);
			for (int j=efface; j<regen; j++)
			{
				for (int i=0; i<NB_MET;i++)
				{
	   			play_with_meteore(texture_meteore,window,renderer, PIXEL*met[j][i], PIXEL*HAUTEUR_MET*(regen-j+efface)+PIXEL*gen);
				}
				SDL_Delay(5);
			}
				if (regen>11)
				{
					regen=11;
					efface+=1;
				} 
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			pos=0;
			image=texture_vaisseau;
/*			printf("gen :%d\n", gen);
			printf("regen :%d\n", regen);
			printf("efface :%d\n", efface);
*/			
	/*		for (int j=0;j<longueur;j++)
	{
		for (int i=0;i<largeur;i++)
		{
			printf("%d ",grille[i][j]);
		}
        printf("\n");
	}*/

		
	  }
		if (coli)
		{
			SDL_RenderClear(renderer);
			affichage_texte(0, window, renderer);
			SDL_RenderPresent(renderer);
		//	printf("mort\n");
			running=0;
			SDL_Delay(1000);
		}
		if (efface==12)
		{
			SDL_RenderClear(renderer);
			affichage_texte(1, window, renderer);
			SDL_RenderPresent(renderer);
		//	printf("victoire bravo\n");
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
}
                                     


