/*main.c*/
/*15 juin 2021*/
/*make*/

#include "main.h"

void end_sdl(char ok,char const* msg,SDL_Window* window, SDL_Renderer* renderer)
{
	char msg_formated[255];
	int l;

	if (!ok) 
	{	                             
		strncpy(msg_formated, msg, 250);
		l = strlen(msg_formated);           
		strcpy(msg_formated + l, " : %s\n");
		SDL_Log(msg_formated, SDL_GetError());
	}

	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL)   SDL_DestroyWindow(window);

	SDL_Quit();

	if (!ok) exit(EXIT_FAILURE);
}

void afficherEcranIntelligemment(SDL_Renderer *renderer,int **tab,int taille_cell)
{
	int x=0;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer,0,0,0,0);
 	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0,&screen);
	int decalage_horizontale=(screen.w/taille_cell-P)*taille_cell/3;
	int decalage_vertical=(screen.h/taille_cell-N)*taille_cell/20;

	SDL_SetRenderDrawColor(renderer,0,0,0,0);
	int i1,j1,noeud=0;
	
	for (int i=0;i<N;i++){
                for (int j=0;j<P;j++){
                        x=tab[j][i];
			i1=(noeud%P);
                        j1=((int)noeud/P);

                        if (!(x & FLAG_N)){
                                SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical); //mur au nord
                                }
                        if ((x & FLAG_S)!=2)
                                SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur au sud
                        if ((x & FLAG_E)!=4)
                                SDL_RenderDrawLine(renderer,(i1+1)*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,(i1+1)*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur à l'est
                        if ((x & FLAG_O)!=8)
                                SDL_RenderDrawLine(renderer,i1*taille_cell+decalage_horizontale,j1*taille_cell+decalage_vertical,i1*taille_cell+decalage_horizontale,(j1+1)*taille_cell+decalage_vertical); //mur à l'ouest

                        noeud+=1;

                }
        }
}

int min(int a, int b)
{
	if (a>b)
		return b;
	else
		return a;
}	


int main (int argc, char** argv)
{
	double p;

	//l'argument p regit l'affichage des murs : s'il vaut 0 il n'y a aucun mur, s'il vaut un on a un arbre
	if (argc==2)  p=atof(argv[1]);
	else p=0.75; 
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

 	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0,&screen);
	SDL_Window *window;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,screen.w,screen.h, SDL_WINDOW_RESIZABLE);
	
	if (window == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	
	SDL_SetWindowTitle(window, "Labyrinthe");

	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /*  SDL_RENDERER_SOFTWARE */
	if (renderer == 0) fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	int running=1;
	srand(time(0));
	int noeuds=N*P;
	int nb_aretes=2*N*P-N-P;
	int **tab;
	int cours=0;
	int taille_cell=min(screen.w/(P+2),screen.h/(N+2));
	//int * tab_parents;  à décommenter pour l'utilisation de Dijkstra
	graph_t * graph=creer_graph(noeuds,nb_aretes);
	generation(graph);
	graph=Fisher(graph,nb_aretes);
	graph=kruskal(graph,noeuds,nb_aretes,&cours,p);
	tab=tableau_ligne(graph,cours);

	//initialisation des differentes textures
	SDL_Texture * texture,*texture_fin,* texture_elve,* texture_elve_reverse;

	texture_elve = load_texture_from_image("Elve_lign.png",renderer);
    	if (texture_elve == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);

    	texture_elve_reverse = load_texture_from_image("Elve_ligne_reverse.png",renderer);
    	if (texture_elve_reverse == NULL) end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
	
	texture = load_texture_from_image("road.png",renderer);
	if (texture==NULL) exit(EXIT_FAILURE);

	texture_fin = load_texture_from_image("roguelikeChar_transparent.png",renderer);
    	if (texture_fin==NULL) exit(EXIT_FAILURE);

	//tab_parents=dijkstra(tab,graph->noeuds,ND_ARRIVEE);

	SDL_Event event;
	/*while (running)
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
					default:
						break;
					}
					break;
			break;
			}
			//afficherEcranIntelligemment(renderer,tab,taille_cell);
			//SDL_RenderPresent(renderer);
        		//SDL_Delay(5000);
        		//SDL_RenderClear(renderer);
			afficherImage(renderer,window,tab,taille_cell,texture);	
        		affichage_fin(texture_fin,window,renderer,ND_ARRIVEE/P,ND_ARRIVEE%P,taille_cell);
			SDL_RenderPresent(renderer);
        		SDL_Delay(10);
        		SDL_RenderClear(renderer);
		}
	}*/
	/*
	 *application du plus court chemin calculé par dijkstra
	int pause=1;
	int noeud_dep=rand()%TAILLE;
	int right=1;
	int stand=0;
	int pos_x=noeud_dep%P*taille_cell;
	int pos_y=noeud_dep/P*taille_cell;
	float zoom = (float)taille_cell/(float)22;
	int temps=1;
	int deplacement=taille_cell;
	int noeud_actuel=noeud_dep;
	int noeud_arrive=rand()%TAILLE;
	tab_parents=dijkstra(tab,graph->noeuds,noeud_arrive);

	while ((running)||(temps<10))
        {
        	if (noeud_actuel==noeud_arrive)
			running=0;
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
                                                temps=10;
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
		if(tab_parents[noeud_actuel]/P==(noeud_actuel/P)-1){
			if (right){
        			play_with_elve_N(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        		}
        		else{
        			play_with_elve_N_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
       	 		}
        		pos_y=pos_y-deplacement;
        		stand=0;
        	}
		if(tab_parents[noeud_actuel]/P==(noeud_actuel/P)+1){
			if (right){
        			play_with_elve_S(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        		}
        		else{
        			play_with_elve_S_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        		}
        		pos_y=pos_y+deplacement;
        		stand=0;
        	}
		if(tab_parents[noeud_actuel]%P==(noeud_actuel%P)-1){
        		play_with_elve_O(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        		pos_x=pos_x-deplacement;
        		stand=0;
        		right=0;
        	}
		if(tab_parents[noeud_actuel]%P==(noeud_actuel%P)+1){
			play_with_elve_E(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        		pos_x=pos_x+deplacement;
        		stand=0;
        		right=1;
        	}
        	if (right){
        		switch (stand){
        		        case 0:
                			play_standstill_1(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			case 2:
                			play_standstill_2(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			case 4:
                			play_standstill_3(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			case 6:
                			play_standstill_4(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
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
        	    	    play_standstill_1_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                		stand=(stand+1)%7;
                		break;
            		case 2:
                		play_standstill_2_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
               	 		stand=(stand+1)%7;
                		break;
            		case 4:
                		play_standstill_3_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                		stand=(stand+1)%7;
                		break;
            		case 6:
                		play_standstill_4_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                		stand=(stand+1)%7;
                		break;
            		default:
                		stand=(stand+1)%7;
                	break;
            		}
        	}
        	SDL_Delay(30);
        	SDL_RenderPresent(renderer);
		if (running==0){
			temps++;
        	}
		else
			noeud_actuel=tab_parents[noeud_actuel];

	}*/
	
	int pause=1;
	int noeud_dep=rand()%TAILLE;
	int right=1;
	int stand=0;
	int pos_x=noeud_dep%P*taille_cell;
	int pos_y=noeud_dep/P*taille_cell;
	float zoom = (float)taille_cell/(float)22;
	int temps=1;
	int deplacement=taille_cell;
	int noeud_actuel=noeud_dep;
	int noeud_arrive=rand()%TAILLE;
	int colli;

	while ((running)||(temps<10))
        {
        	if (noeud_actuel==noeud_arrive)
			running=0;
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
                                                temps=10;
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
		if (pause){
			if ((keystates[SDL_SCANCODE_UP]||keystates[SDL_SCANCODE_W])) {	
				colli=collision_N(pos_x,pos_y,tab,taille_cell);
				if(!colli){
					if (right){
        					play_with_elve_N(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        				}
        				else{
        					play_with_elve_N_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
       	 				}
        				pos_y=pos_y-deplacement;
        				stand=0;
        			}
			}
			if ((keystates[SDL_SCANCODE_DOWN]||keystates[SDL_SCANCODE_S])) {	
				colli=collision_S(pos_x,pos_y,tab,taille_cell);
				if(!colli){
					if (right){
        					play_with_elve_S(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        				}
        				else{
        					play_with_elve_S_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        				}
        				pos_y=pos_y+deplacement;
        				stand=0;
        			}
			}
        		if ((keystates[SDL_SCANCODE_LEFT]||keystates[SDL_SCANCODE_A])) {	
				colli=collision_O(pos_x,pos_y,tab,taille_cell);
				if(!colli){
					play_with_elve_O(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        				pos_x=pos_x-deplacement;
        				stand=0;
        				right=0;
        			}
			}
			if ((keystates[SDL_SCANCODE_RIGHT]||keystates[SDL_SCANCODE_D])) {	
				colli=collision_E(pos_x,pos_y,tab,taille_cell);
				if(!colli){
					play_with_elve_E(texture_elve,texture,window,renderer,pos_x,pos_y,deplacement,zoom,tab,taille_cell,texture_fin,noeud_arrive);
        				pos_x=pos_x+deplacement;
        				stand=0;
        				right=1;
        			}
			}
        		if (right){
        			switch (stand){
        		        	case 0:
                				play_standstill_1(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                				stand=(stand+1)%7;
                				break;
            				case 2:
                				play_standstill_2(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                				stand=(stand+1)%7;
                				break;
            				case 4:
                				play_standstill_3(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                				stand=(stand+1)%7;
                				break;
            				case 6:
                				play_standstill_4(texture_elve,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
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
        	    		    play_standstill_1_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			case 2:
                			play_standstill_2_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
               	 			stand=(stand+1)%7;
                			break;
            			case 4:
                			play_standstill_3_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			case 6:
                			play_standstill_4_l(texture_elve_reverse,texture,window,renderer,pos_x,pos_y,zoom,tab,taille_cell,texture_fin,noeud_arrive);
                			stand=(stand+1)%7;
                			break;
            			default:
                			stand=(stand+1)%7;
                		break;
            			}
        		}
        		SDL_Delay(30);
        		SDL_RenderPresent(renderer);
			if (running==0){
				temps++;
        		}
		}
	}

	SDL_DestroyTexture(texture_elve_reverse);
	SDL_DestroyTexture(texture_elve);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture_fin);
	end_sdl(1, "Normal ending", window, renderer);
	return 1;
}
                                     

