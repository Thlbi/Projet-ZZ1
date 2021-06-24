










while (running){
		while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                        case SDL_QUIT:
                        running = 0;
					break;
                        case SDL_WINDOWEVENT:
                            switch (event.window.event){
                                case SDL_WINDOWEVENT_CLOSE:
                                            running = 0;
                                            temps=1000;
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
						case SDLK_l:
							noeud_dep=rand()%TAILLE;
							right=1;
							stand=0;
							pos_x=noeud_dep%P*taille_cell;
							pos_y=noeud_dep/P*taille_cell;
							temps=1;
							noeud_arrive=rand()%TAILLE;
							break;
                                                case SDLK_SPACE:
                                                case SDLK_p:
                                                        pause=1-pause;
                                                        break;
						case SDLK_m: //la fonction devra afficher la totalite du labyrinthe sans brouillard de guerre
							afficherImage(renderer,window,tab,taille_cell2,texture);
							affichage_fin(texture_fin,window,renderer,noeud_arrive/P,noeud_arrive%P,taille_cell);
							SDL_RenderPresent(renderer);
							SDL_Delay(2000);
							SDL_RenderClear(renderer);
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
        		peindreMap(texture2,window2,renderer2,noeud_actuel,taille_cell2,tab);
			SDL_RenderPresent(renderer2);
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






















// Boucle principale
while(running)
    {
  
        // Gestion des evenements
        if (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    boolBoucle=0;
                    SDL_Quit();
                    break;
  
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                       //...Quelque chose...
  
                    } // switch (event.key.keysym.sym)
                    break;
  
            } // switch(event.type)
  
        } // if (SDL_PollEvent(&event))
  
          
        // Refresh
        tempsActu = SDL_GetTicks();
        if ( (tempsActu - tempsPrecedent ) > REFRESH_TIME)
        {
  
            // Met à jour les surfaces...
            // L'UNIQUR SDL_FLIP ICI !!!
            tempsPrecedent = tempsActu;
        }else{
            SDL_Delay( REFRESH_TIME -(tempsActu - tempsPrecedent)  );
        }
  
  
    } // Fin boucle principale