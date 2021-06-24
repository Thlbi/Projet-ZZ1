#include "affichage_txt.h"

void affichage_txt(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Rect window_dimensions = {0}, pos = {0, 0, 0, 0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);

    if (TTF_Init() < 0)
        exit(EXIT_FAILURE);

    TTF_Font *font = NULL;                   // la variable 'police de caractère'
    font = TTF_OpenFont("Pacifico.ttf", 65); // La police à charger, la taille désirée

    if (font == NULL)
        exit(EXIT_FAILURE);

    SDL_Color color = {230, 200, 0, 255}; // la couleur du texte
    SDL_Surface *text_surface = NULL;     // la surface  (uniquement transitoire)

    text_surface = TTF_RenderText_Blended(font, "Vous avez atteint votre maman !", color); // création du texte dans la surface

    if (text_surface == NULL)
        exit(EXIT_FAILURE);

    SDL_Texture *text_texture = NULL;                                    // la texture qui contient le texte
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

    if (text_texture == NULL)
        exit(EXIT_FAILURE);
    SDL_FreeSurface(text_surface); // la texture ne sert plus à rien

    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h); // récupération de la taille (w, h) du texte
    pos.x = (window_dimensions.w - pos.w) / 4;
    pos.y = 0;

    SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
    TTF_Quit();

    //ne pas oublier le TTF_Quit() dans le programme principal
}
