#include "balek.h"

// gcc balek.c -o prog -Wextra -Wall $(sdl2-config --cflags --libs) -lSDL2_image

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

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface

    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}


void play_with_background(SDL_Texture *my_background, SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_background, NULL, NULL,&source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              


  SDL_RenderCopy(renderer, my_background,&source,&destination); 
               
}
void play_with_elve_N(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom){
    SDL_Rect source = {0},destination = {0};                 
             
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;                          
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;  //taille image largeur
    destination.h = offset_y * zoom; //taille image hauteur
    destination.x=pos_x;             //position image x
    destination.y=pos_y;             //position image y


    state[0].x=0; //different rectangle qu'on prend comme sprite 
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=4*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=5*offset_x;
    state[2].y=0;
    state[2].w = offset_x;
    state[2].h = offset_y;
   
    state[3].x=6*offset_x;
    state[3].y=0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x=7*offset_x;
    state[4].y=0;    
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=4*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=5*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=6*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=7*offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=4*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.y=destination.y-(deplacement/nb_images_animation); //déplacement du personnage ici de wind dim.h /32 en tout (diviser par nb animation pour chaque anim)
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }      
}
void play_with_elve_S(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom){
     SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

     SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
     SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;                      
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=0;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=4*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=5*offset_x;
    state[2].y=0;
    state[2].w = offset_x;
    state[2].h = offset_y;
   
    state[3].x=6*offset_x;
    state[3].y=0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x=7*offset_x;
    state[4].y=0;    
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=4*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=5*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=6*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=7*offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=4*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.y=destination.y+(deplacement/nb_images_animation);
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }      

}
void play_with_elve_O(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom){

     SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

     SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
     SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;                         
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=7*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=3*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=2*offset_x;
    state[2].y=0;
    state[2].w=offset_x;
    state[2].h = offset_y;

    state[3].x=1*offset_x;
    state[3].y=0;
    state[3].w=offset_x;
    state[3].h = offset_y;

    state[4].x=0;
    state[4].y=0;
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=3*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=2*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=1*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=7*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.x=destination.x-(deplacement/nb_images_animation);
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }           
}       
void play_with_elve_E(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,int deplacement,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int nb_images_animation=9;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[10];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=0;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;

    state[1].x=4*offset_x;
    state[1].y=0;
    state[1].w=offset_x;
    state[1].h = offset_y;

    state[2].x=5*offset_x;
    state[2].y=0;
    state[2].w = offset_x;
    state[2].h = offset_y;
   
    state[3].x=6*offset_x;
    state[3].y=0;
    state[3].w = offset_x;
    state[3].h = offset_y;

    state[4].x=7*offset_x;
    state[4].y=0;    
    state[4].w=offset_x;
    state[4].h = offset_y;

    state[5].x=4*offset_x;
    state[5].y=0;
    state[5].w=offset_x;
    state[5].h = offset_y;

    state[6].x=5*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[6].x=6*offset_x;
    state[6].y=0;
    state[6].w=offset_x;
    state[6].h = offset_y;

    state[7].x=7*offset_x;;
    state[7].y=0;
    state[7].w=offset_x;
    state[7].h = offset_y;

    state[8].x=4*offset_x;
    state[8].y=0;
    state[8].w=offset_x;
    state[8].h = offset_y;

    state[9].x=0;
    state[9].y=0;
    state[9].w=offset_x;
    state[9].h = offset_y;
    
    for(i=0;i<nb_images_animation;++i){
        play_with_background(background,window,renderer);
        destination.x=destination.x+(deplacement/nb_images_animation);
        SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }  
}
void play_standstill_1(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=0;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_1_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=7*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_2(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_2_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=6*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_3(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=2*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_3_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=5*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_4(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=3*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
void play_standstill_4_l(SDL_Texture* texture_elve,SDL_Texture* background,SDL_Window* window,SDL_Renderer* renderer,int pos_x,int pos_y,float zoom){
    SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                 

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               
    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int nb_images = 8;
    int i=0;                           
    int offset_x = source.w/nb_images;
    int offset_y = source.h;   
    SDL_Rect state[1];

    destination.w = offset_x * zoom;           
    destination.h = offset_y * zoom;
    destination.x=pos_x;
    destination.y=pos_y;



    state[0].x=4*offset_x;
    state[0].y=0;
    state[0].w=offset_x;
    state[0].h = offset_y;
    play_with_background(background,window,renderer);
    SDL_RenderCopy(renderer,texture_elve, &state[i], &destination);
}
int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    int running=1, pause=1;
    int pos_x=100;
    int pos_y=100;
    int zoom =2;
    int stand=0; 
    SDL_Rect window_dimensions = {0},source={0};
    int deplacement; //nb de pixel dont on se déplace pour aller d'une cas à l'autre 
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
    deplacement=window_dimensions.w/32;
    
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
    }
    SDL_Texture* texture_elve = NULL;
    SDL_Texture* texture_elve_reverse = NULL;
    SDL_Texture* bg_texture = NULL;

  

    texture_elve = load_texture_from_image("Elve_lign.png",window,renderer);
    if (texture_elve == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    
    texture_elve_reverse = load_texture_from_image("Elve_ligne_reverse.png",window,renderer);
    if (texture_elve_reverse == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    bg_texture = load_texture_from_image("background.png",window,renderer);
    if (bg_texture == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    SDL_QueryTexture(texture_elve, NULL, NULL,&source.w, &source.h);

    int largeur_elve = source.w/8*zoom;
    int hauteur_elve = source.h*zoom;
    int right=1;
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
						screen.w = event.window.data1;
						screen.h = event.window.data2;
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
                            if (pos_x-deplacement>0){
                                    play_with_elve_O(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                                    pos_x=pos_x-deplacement;
                                    stand=0;
                                    right=0;
                                }
							break;
						case SDLK_RIGHT:
						case SDLK_d:
                            if(pos_x+deplacement+largeur_elve<window_dimensions.w){
                                play_with_elve_E(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                                pos_x=pos_x+deplacement;
                                stand=0;
                                right=1;
                            }
							break;
                        case SDLK_UP:
						case SDLK_z:
                            if(pos_y-deplacement>0){
                                play_with_elve_N(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                                pos_y=pos_y-deplacement;
                                stand=0;
                                right=1;
                            }
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            if(pos_y+deplacement+hauteur_elve<window_dimensions.h){
                                play_with_elve_S(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                                pos_y=pos_y+deplacement;
                                stand=0;
                                right=1;
                            }
                            break;
						default:
							break;
                    }
				    break;
                default:   
			        break;
			}
        }
        if (right){
        switch (stand){
            case 0:
                play_standstill_1(texture_elve,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 2:
                play_standstill_2(texture_elve,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 4:
                play_standstill_3(texture_elve,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 6:
                play_standstill_4(texture_elve,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            default:
                stand=(stand+1)%7;
                break;
                
            }
        }
        else{
        switch (stand){
            case 0:
                play_standstill_1_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 2:
                play_standstill_2_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 4:
                play_standstill_3_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            case 6:
                play_standstill_4_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,zoom);
                stand=(stand+1)%7;
                break;
            default:
                stand=(stand+1)%7;
                break;
                
            }
        } 
  
	    SDL_Delay(30);
	    SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(bg_texture);;
	SDL_DestroyTexture(texture_elve_reverse);
	SDL_DestroyTexture(texture_elve);
	IMG_Quit();
    end_sdl(1, "Normal ending", window, renderer);
	return 1;
}

