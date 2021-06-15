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
      int width = 300;
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
   SDL_Event event;
   int running=1;
	int pause=1;
	int posvaisseau;
	posvaisseau=init_tab(grille,largeur,longueur);
	int pos=0;
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
									printf("pause\n");
									break;
								case SDLK_LEFT:
								case SDLK_q:
									pos=-1;
									break;
								case SDLK_RIGHT:
								case SDLK_d:
									pos=1;
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
			printf("%d\n",pos);
			position_vaisseau(grille, &posvaisseau,longueur,largeur,pos);
			printf("%d\n",posvaisseau);
			afficherEcran(grille, window, renderer,posvaisseau);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			pos=0;
			for (int j=0;j<longueur;j++)
	{
		for (int i=0;i<largeur;i++)
		{
			printf("%d ",grille[i][j]);
		}
        printf("\n");
	}

		}
		SDL_Delay(15);
		
		}
   end_sdl(1, "Normal ending", window, renderer);
}
                                     


