#include "main.h"

int main(int argc, char **argv){
    srand(1998);
    graph_t *graph=initgraph(TAILLE);
    generer_couple_2(graph);
    arete_t*A=graph->suiv;
    int **tab;
    graph=ordonner_Fisher(graph);
    
    A=kruskal(graph);
	//afficher_arete(A);

    tab=tableau_aretes(A);

    (void)argc;
    (void)argv;
    int running=1, pause=1;

    SDL_Rect window_dimensions = {0},source={0};

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    SDL_DisplayMode screen;

    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w*0.6, screen.h *0.6, SDL_WINDOW_RESIZABLE);

    if (window == 0)
        {
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
         /* on peut aussi utiliser SDL_Log() */
        }
    SDL_SetWindowTitle(window, "Anim Laby");

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);  
    
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    SDL_Texture* texture_laby = NULL;
    SDL_Texture* background = NULL;
    texture_laby = load_texture_from_image("0f6a29db-2521-4e60-899f-1795dfa4906e.png",window,renderer);
    if (texture_laby == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    
    afficherEcranIntelligemment_2(texture_laby,background,window,renderer,tab);

    SDL_DestroyTexture(texture_laby);
	IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
    liberer(tab);
	return 0;
}