#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<stdlib.h>
#include<time.h>

void afficherEcran(SDL_Renderer *renderer,int tab1[30][50]){
	SDL_Rect rect;

	int i,j;
	
	SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	for (i=0;i<30;i++){
		for (j=0;j<50;j++){
			if (tab1[i][j]==1){
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
	/* afficher à l'ecran */
	
	SDL_RenderPresent(renderer);
}

void vivre(int tab1[30][50],int tab2[30][50])
{
	int i,j,vivre;
	for (i=0;i<30;i++){
		for (j=0;j<50;j++){
			vivre=0;
			vivre+=tab1[(i-1)%30][j];
			vivre+=tab1[(i+1)%30][j];
			vivre+=tab1[i][(j-1)%50];
			vivre+=tab1[i][(j+1)%50];
			vivre+=tab1[(i-1)%30][(j-1)%50];
			vivre+=tab1[(i-1)%30][(j+1)%50];
			vivre+=tab1[(i+1)%30][(j-1)%50];
			vivre+=tab1[(i+1)%30][(j+1)%50];
			if ((tab1[i][j]==0)&&(vivre==3)){
				//la cellule devient vivante
				tab2[i][j]=1;
			}
			else{
				if ((vivre==2) || (vivre==3)){
					//cellule reste en vie
					tab2[i][j]=1;
				}
				else{
					//la cellule meurt
					tab2[i][j]=0;
				}
			}
		}
	}
	for (i=0;i<30;i++){
		for (j=0;j<50;j++){
			tab1[i][j]=tab2[i][j];
		}
	}
}


void init_tab(int tab1[30][50]){
	int aleat,i,j;
	srand(time(0));

	for (i=0;i<30;i++){
		for (j=0;j<50;j++){
			aleat=(int)(((float)rand()/(float)RAND_MAX)*1.5);
			tab1[i][j]=aleat;
		}
	}
}

int main()
{
	int width=30*10, height=50*10;
	SDL_Window *window;
	int tab1[30][50];
	int tab2[30][50];
	int i,j;

	init_tab(tab1);
	
	vivre(tab1,tab2);

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE);

        if (window == 0)
        {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        }


	SDL_Renderer * renderer;
	renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	if (renderer == 0) {
     	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}

	afficherEcran(renderer,tab1);
	SDL_Delay(1000);
	int running=1;
	SDL_Event event;
	while (running) {
		SDL_Delay(150);
		afficherEcran(renderer,tab1);
		vivre(tab1,tab2);
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT:
					printf("window event\n");
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
							printf("appui sur la croix\n");
							break;
						default:
							for (i=0;i<30;i++){
								for (j=0;j<50;j++){
									tab1[i][j]=tab2[i][j];
								}
							}
							afficherEcran(renderer,tab1);
					}
				    break;
				case SDL_QUIT :
					printf("on quitte\n");
					running = 0;
			}
		}
		SDL_Delay(1); 
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
