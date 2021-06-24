#include "texture_perso.h"

int frameCount = 0;
float frameCount2 = 0;

void play_with_elve_N(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, destination = {0};

    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 10;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom; //taille image largeur
    destination.h = offset_y * zoom; //taille image hauteur
    destination.x = pos_x;           //position image x
    destination.y = pos_y;           //position image y

    state[0].x = 0; //different rectangle qu'on prend comme sprite
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 4 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 5 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 6 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 7 * offset_x;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 4 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 5 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 6 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = 7 * offset_x;
    ;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 4 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 0;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.y = destination.y - (deplacement / nb_images_animation); //déplacement du personnage ici de wind dim.h /32 en tout (diviser par nb animation pour chaque anim)
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_with_elve_N_l(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, destination = {0};

    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 9;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom; //taille image largeur
    destination.h = offset_y * zoom; //taille image hauteur
    destination.x = pos_x;           //position image x
    destination.y = pos_y;           //position image y

    state[0].x = 7 * offset_x;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 3 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 2 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 1 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 0;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 3 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 2 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 1 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = 0;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 3 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 7 * offset_x;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.y = destination.y - (deplacement / nb_images_animation);
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_with_elve_S(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 9;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 0;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 4 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 5 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 6 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 7 * offset_x;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 4 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 5 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 6 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = 7 * offset_x;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 4 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 0;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.y = destination.y + (deplacement / nb_images_animation);
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_with_elve_S_l(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 9;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 7 * offset_x;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 3 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 2 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 1 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 0;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 3 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 2 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 1 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = 0;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 3 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 7 * offset_x;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.y = destination.y + (deplacement / nb_images_animation);
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_with_elve_O(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{

    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 9;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 7 * offset_x;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 3 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 2 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 1 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 0;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 3 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 2 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 1 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = offset_x;
    ;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 7 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 0;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.x = destination.x - (deplacement / nb_images_animation);
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_with_elve_E(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, int deplacement, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation = 9;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[10];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 0;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 4 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 5 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 6 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x = 7 * offset_x;
    state[4].y = 0;
    state[4].w = offset_x;
    state[4].h = offset_y;

    state[5].x = 4 * offset_x;
    state[5].y = 0;
    state[5].w = offset_x;
    state[5].h = offset_y;

    state[6].x = 5 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[6].x = 6 * offset_x;
    state[6].y = 0;
    state[6].w = offset_x;
    state[6].h = offset_y;

    state[7].x = 7 * offset_x;
    ;
    state[7].y = 0;
    state[7].w = offset_x;
    state[7].h = offset_y;

    state[8].x = 4 * offset_x;
    state[8].y = 0;
    state[8].w = offset_x;
    state[8].h = offset_y;

    state[9].x = 0;
    state[9].y = 0;
    state[9].w = offset_x;
    state[9].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    destination.x = destination.x + (deplacement / nb_images_animation);
    SDL_RenderCopy(renderer, texture_elve, &state[frameCount], &destination);
    frameCount = (frameCount + 1) % 10;
}
void play_standstill(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[4];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 0;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 2 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 2 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    SDL_RenderCopy(renderer, texture_elve, &state[(int)frameCount2], &destination);
    frameCount2 = (frameCount2 + 0.25); 
    
    if (frameCount2>=4){
        frameCount2=0;
    }

}
void play_standstill_l(SDL_Texture *texture_elve, SDL_Texture *background, SDL_Window *window, SDL_Renderer *renderer, int pos_x, int pos_y, float zoom, int **tab, int taille_cell, SDL_Texture *texture_fin, int noeud_arrive)
{
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(texture_elve, NULL, NULL, &source.w, &source.h);

    int nb_images = 8;
    int offset_x = source.w / nb_images;
    int offset_y = source.h;
    SDL_Rect state[1];

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = pos_x;
    destination.y = pos_y;

    state[0].x = 7 * offset_x;
    state[0].y = 0;
    state[0].w = offset_x;
    state[0].h = offset_y;

    state[1].x = 6 * offset_x;
    state[1].y = 0;
    state[1].w = offset_x;
    state[1].h = offset_y;

    state[2].x = 5 * offset_x;
    state[2].y = 0;
    state[2].w = offset_x;
    state[2].h = offset_y;

    state[3].x = 4 * offset_x;
    state[3].y = 0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    afficherImage(renderer, window, tab, taille_cell, background);
    affichage_fin(texture_fin, window, renderer, noeud_arrive / P, noeud_arrive % P, taille_cell);
    SDL_RenderCopy(renderer, texture_elve, &state[(int)frameCount2], &destination);
    frameCount2 = (frameCount2 + 0.25);
        if (frameCount2>=4){
        frameCount2=0;
    }
}
