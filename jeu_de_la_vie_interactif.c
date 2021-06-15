/*Jeu de la vie interactif*/
/*15 juin 2021*/
/*gcc jeu_de_la_vie_interactif.c -o prog -Wall -Wextra -lSDL2 -lm -g*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL.h>
#include<stdlib.h>
#include<time.h>

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

int** init_grille(int x,int y)
{
	int ** grille=malloc(x*sizeof(int *));
	if (grille==NULL)
	{
		printf("Erreur d'allocation du int**\n");
	}
		
	for (int i=0; i<x;i++)
	{
		grille[i]=malloc(y*sizeof(int));
		if (grille[i]==NULL)
		{
			printf("Erreur d'allocation du int* numero %d\n",i);
		}
	
	}
	return grille;
}

void liberer(int **grille,int x)
{
	for (int i=0; i<x;i++)
		free(grille[i]);
	free(grille);
}

int modulo(int a, int b)
{
	if (a>=0 && a<b)
		return a;
	else if (a>=b)
		return modulo(a-b,b);
	else 
		return modulo(a+b,b);
	
}
int * survie(int ** tab, int x, int y,int pos_x,int pos_y)
{
	int * survie=malloc(9*sizeof(int));

	if (survie==NULL)
		printf("Erreur d'allocation du int* survie\n");
	survie[0]=tab[modulo((pos_x+1),x)][modulo((pos_y+1),y)];
	survie[1]=tab[modulo((pos_x+1),x)][modulo((pos_y),y)];
	survie[2]=tab[modulo((pos_x+1),x)][modulo((pos_y-1),y)];
	survie[3]=tab[modulo((pos_x),x)][modulo((pos_y+1),y)];
	survie[4]=tab[modulo((pos_x),x)][modulo((pos_y-1),y)];
	survie[5]=tab[modulo((pos_x-1),x)][modulo((pos_y+1),y)];
	survie[6]=tab[modulo((pos_x-1),x)][modulo((pos_y-1),y)];
	survie[7]=tab[modulo((pos_x-1),x)][modulo((pos_y),y)];
	survie[8]=tab[modulo((pos_x),x)][modulo((pos_y),y)];
	
	return survie;
}

int vie_mort(int * survie)
{
	int total=0;
	int vie=0;
	for (int i=0; i<8; i++)
		total+=survie[i];
	
	if (total<=1 && total>=4)
		vie=0;
	else if (total==3)
		vie=1;
	else if (total==2 && survie[9]==1)
		vie=1;
	free(survie);
	return vie;
}

void t_tplusun(int ** tab_t, int x, int y,int ** tab_tplusun)
{
	
	int i,j;
	for (i=0;i<x;i++)
	{
		for (j=0;j<y;j++)
		{
			tab_tplusun[i][j]=vie_mort(survie(tab_t,x,y,i,j));
		}
	}
}
void init_tab(int** tab,int x,int y)
{
	int aleat,i,j;
	srand(time(0));

	for (i=0;i<x;i++)
	{
		for (j=0;j<y;j++)
		{
			aleat=(int)(((float)rand()/(float)RAND_MAX)*2);
			tab[i][j]=aleat;
		}
	}
}

void afficherEcran(SDL_Renderer *renderer,int** tab, int x,int y){
	SDL_Rect rect;

	int i,j;
	
	SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	for (i=0;i<x;i++){
		for (j=0;j<y;j++){
			if (tab[i][j]==1){
				//cellule vivante donc couleur noire
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}
			else{
				//cellule morte, couleur blanche
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			}
			rect.x=i*10;
			rect.y=j*10;
			rect.w=rect.h=10;
			SDL_RenderFillRect(renderer,&rect);
		}
	}	
	SDL_RenderPresent(renderer);
}
	
int main ()
{


   if (SDL_Init(SDL_INIT_VIDEO) == -1)
   {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
            return EXIT_FAILURE;
      }
   SDL_Window *window;
      int width = 1900;
      int height = 1000;
		int ** tab1=NULL;
		int ** tab2=NULL;
		tab1=init_grille(width/10, height/10);
		tab2=init_grille(width/10, height/10);
		init_tab(tab1,width/10,height/10);

   window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

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
								default: 
									break;
							}
							break;
							case SDL_MOUSEBUTTONDOWN:
 							if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) )
							{
								init_tab(tab1,width/10,height/10);
							}
								break;
							default:
								break;
								 
         			}
      	}
		if (!pause)
		{
			t_tplusun(tab1,width/10,height/10,tab2);
			afficherEcran(renderer,tab2,width/10,height/10);
			for (int i=0;i<width/10;i++)
			{
				for (int j=0;j<height/10;j++)
					tab1[i][j]=tab2[i][j];
			}
		}
		SDL_Delay(150);
		}
   end_sdl(1, "Normal ending", window, renderer);
	liberer(tab1,width/10);
	liberer(tab2,width/10);
}
                                     


