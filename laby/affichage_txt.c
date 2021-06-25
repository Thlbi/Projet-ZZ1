#include "affichage_txt.h"

void affichage_txt(SDL_Window *window,SDL_Renderer *renderer)
{
        SDL_Rect window_dimensions = {0}, pos = {0, 0, 0, 0};
        SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

        if (TTF_Init() < 0) exit(EXIT_FAILURE);

        TTF_Font* font = NULL;                     // la variable 'police de caractère'
        font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée

        if (font == NULL) exit(EXIT_FAILURE);

        SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
        SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)

        text_surface = TTF_RenderText_Blended(font, "Vous avez atteint votre maman ! (:", color); // création du texte dans la surface

        if (text_surface == NULL) exit(EXIT_FAILURE);

        SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

        if (text_texture == NULL) exit(EXIT_FAILURE);
        SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien

        SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= (window_dimensions.w-pos.w)/2;
	pos.y= (window_dimensions.h-pos.h)/2;

	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
		SDL_DestroyTexture(text_texture);
		TTF_CloseFont(font);
		TTF_Quit();

        //ne pas oublier le TTF_Quit() dans le programme principal
}

void affichage_txt_pause(SDL_Window *window,SDL_Renderer *renderer)
{
        SDL_Rect window_dimensions = {0}, pos = {0, 0, 0, 0};
        SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

        if (TTF_Init() < 0) exit(EXIT_FAILURE);

        TTF_Font* font = NULL;                     // la variable 'police de caractère'
        font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée

        if (font == NULL) exit(EXIT_FAILURE);

        SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
        SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)
        SDL_Surface* text_surface1 = NULL;               // la surface  (uniquement transitoire)
        SDL_Surface* text_surface2 = NULL;               // la surface  (uniquement transitoire)
        SDL_Surface* text_surface3 = NULL;               // la surface  (uniquement transitoire)

        text_surface = TTF_RenderText_Blended(font, "p :pause\n", color); // création du texte dans la surface
        text_surface1 = TTF_RenderText_Blended(font, "m : afficher minimap\n", color); // création du texte dans la surface
        text_surface2 = TTF_RenderText_Blended(font, "l : relancer \n", color); // création du texte dans la surface
        text_surface3 = TTF_RenderText_Blended(font, "r : appliquer dijkstra\n", color); // création du texte dans la surface

        if (text_surface == NULL) exit(EXIT_FAILURE);
        if (text_surface1 == NULL) exit(EXIT_FAILURE);
        if (text_surface2 == NULL) exit(EXIT_FAILURE);
        if (text_surface3 == NULL) exit(EXIT_FAILURE);

        SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
        SDL_Texture* text_texture1 = NULL;           // la texture qui contient le texte
        SDL_Texture* text_texture2 = NULL;           // la texture qui contient le texte
        SDL_Texture* text_texture3 = NULL;           // la texture qui contient le texte

        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
        text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
        text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2); // transfert de la surface à la texture
        text_texture3 = SDL_CreateTextureFromSurface(renderer, text_surface3); // transfert de la surface à la texture

        if (text_texture == NULL) exit(EXIT_FAILURE);
        if (text_texture1 == NULL) exit(EXIT_FAILURE);
        if (text_texture2 == NULL) exit(EXIT_FAILURE);
        if (text_texture3 == NULL) exit(EXIT_FAILURE);

        SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= (window_dimensions.w-pos.w)/4;
			pos.y= 0;
	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
        SDL_QueryTexture(text_texture1, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= (window_dimensions.w-pos.w)/4;
			pos.y+= pos.h +10;
	SDL_RenderCopy(renderer, text_texture1, NULL, &pos); // Ecriture du texte dans le renderer
        SDL_QueryTexture(text_texture2, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= (window_dimensions.w-pos.w)/4;
			pos.y+= pos.h+10;
	SDL_RenderCopy(renderer, text_texture2, NULL, &pos); // Ecriture du texte dans le renderer
        SDL_QueryTexture(text_texture3, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= (window_dimensions.w-pos.w)/4;
			pos.y+= pos.h+10;
	SDL_RenderCopy(renderer, text_texture3, NULL, &pos); // Ecriture du texte dans le renderer

		SDL_DestroyTexture(text_texture);
      SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien
		SDL_DestroyTexture(text_texture1);
      SDL_FreeSurface(text_surface1);             // la texture ne sert plus à rien
		SDL_DestroyTexture(text_texture2);
      SDL_FreeSurface(text_surface2);             // la texture ne sert plus à rien
		SDL_DestroyTexture(text_texture3);
      SDL_FreeSurface(text_surface3);             // la texture ne sert plus à rien
		TTF_CloseFont(font);
		TTF_Quit();

        //ne pas oublier le TTF_Quit() dans le programme principal
}

void timer(SDL_Window * window, SDL_Renderer * renderer, int compteur)
{
	     SDL_Rect window_dimensions = {0}, pos = {0, 0, 0, 0};
        SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

        if (TTF_Init() < 0) exit(EXIT_FAILURE);

        TTF_Font* font = NULL;                     // la variable 'police de caractère'
        font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée

        if (font == NULL) exit(EXIT_FAILURE);

			char * temps=malloc(10*sizeof(char));

        SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
        SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)
		  sprintf(temps,"%d",compteur);
        text_surface = TTF_RenderText_Solid(font, temps , color); 

        if (text_surface == NULL) exit(EXIT_FAILURE);

        SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

        if (text_texture == NULL) exit(EXIT_FAILURE);
        SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien

        SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= window_dimensions.w-pos.w;
			pos.y= 0;

	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
		SDL_DestroyTexture(text_texture);
		TTF_CloseFont(font);
		TTF_Quit();
		free(temps);
}
 
void affichage_txt_perdu(SDL_Window * window, SDL_Renderer * renderer)
{
	     SDL_Rect window_dimensions = {0}, pos = {0, 0, 0, 0};
        SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);

        if (TTF_Init() < 0) exit(EXIT_FAILURE);

        TTF_Font* font = NULL;                     // la variable 'police de caractère'
        font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée

        if (font == NULL) exit(EXIT_FAILURE);

        SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
        SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)
        text_surface = TTF_RenderText_Blended(font, "Oh non!!! Vous n'avez pas retrouve votre maman :(" , color); 

        if (text_surface == NULL) exit(EXIT_FAILURE);

        SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

        if (text_texture == NULL) exit(EXIT_FAILURE);
        SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien

        SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
        pos.x= window_dimensions.w/2	-pos.w/2;
			pos.y= window_dimensions.h/2 	-pos.h/2;

	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
		SDL_DestroyTexture(text_texture);
		TTF_CloseFont(font);
		TTF_Quit();
}
