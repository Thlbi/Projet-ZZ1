#include <SDL2/SDL_ttf.h>
#include "affichage_texte.h"


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


void affichage_texte(int victoire,SDL_Window *window,SDL_Renderer *renderer)
{
	SDL_Rect window_dimensions = {0};
	SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

	if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", window, renderer);
	
	TTF_Font* font = NULL;                     // la variable 'police de caractère'
	font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée
	
	if (font == NULL) end_sdl(0, "Can't load font", window, renderer);
	
	SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
	SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)
	
	if (victoire==1){
		text_surface = TTF_RenderText_Blended(font, "Vous avez survecu !", color); // création du texte dans la surface
	}
	else{
		text_surface = TTF_RenderText_Blended(font, "C'est la fin du voyage  :c", color); // création du texte dans la surface
	}
	
	if (text_surface == NULL) end_sdl(0, "Can't create text surface", window, renderer);

	SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

	if (text_texture == NULL) end_sdl(0, "Can't create texture from surface", window, renderer);
	SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien

	SDL_Rect pos = {window_dimensions.w/3, window_dimensions.h/3, 0, 0};              // rectangle où le texte va être prositionné
	SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
	SDL_DestroyTexture(text_texture);    // On n'a plus besoin de la texture avec le texte

	//ne pas oublier le TTF_Quit() dans le programme principal
}

/*
int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
        {
                 fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
                 return EXIT_FAILURE;
        }
        SDL_Window *window;
        int width = 1900;
        int height = 1000;
        window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

        if (window == 0)
        {
                 fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        }
        SDL_SetWindowTitle(window, "écran");

	SDL_Renderer *renderer;
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == 0)
        {
                fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        }

	affichage_texte(0,window,renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}
*/
