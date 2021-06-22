#include "main.h"



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
    int keyPressed;
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
						default:
							break;
                    }
				    break;
                default:   
			        break;
			}
        }
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
			keyPressed = 0;
			if ((keystates[SDL_SCANCODE_UP]||keystates[SDL_SCANCODE_W])&&(pos_y-deplacement>0)) {
                if (right){
                    play_with_elve_N(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                }
                else{
                    play_with_elve_N_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                }
                pos_y=pos_y-deplacement;
                stand=0;
				keyPressed = 1;
			}
			if ((keystates[SDL_SCANCODE_DOWN]||keystates[SDL_SCANCODE_S])&&(pos_y+deplacement+hauteur_elve<window_dimensions.h)) {
                if (right){
                    play_with_elve_S(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                }
                else{
                    play_with_elve_S_l(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                }                
                pos_y=pos_y+deplacement;
                stand=0;
				keyPressed = 1;
			}
			if ((keystates[SDL_SCANCODE_LEFT]||keystates[SDL_SCANCODE_A])&&(pos_x-deplacement>0)) {
                play_with_elve_O(texture_elve_reverse,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                pos_x=pos_x-deplacement;
                stand=0;
                right=0;
				keyPressed = 1;
			}
			if ((keystates[SDL_SCANCODE_RIGHT]||keystates[SDL_SCANCODE_D])&&(pos_x+deplacement+largeur_elve<window_dimensions.w)) {
                play_with_elve_E(texture_elve,bg_texture,window,renderer,pos_x,pos_y,deplacement,zoom);
                pos_x=pos_x+deplacement;
                stand=0;
                right=1;
				keyPressed = 1;
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
