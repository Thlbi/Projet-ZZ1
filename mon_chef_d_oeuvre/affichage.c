#include "affichage.h"
                    

void end_sdl2(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer)
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

	if (TTF_Init() < 0) end_sdl2(0, "Couldn't initialize SDL TTF", window, renderer);
	
	TTF_Font* font = NULL;                     // la variable 'police de caractère'
	font = TTF_OpenFont("polices/Pacifico.ttf", 65); // La police à charger, la taille désirée
	
	if (font == NULL) end_sdl2(0, "Can't load font", window, renderer);
	
	SDL_Color color = {230, 200, 0, 255};                       // la couleur du texte
	SDL_Surface* text_surface = NULL;               // la surface  (uniquement transitoire)
	
	if (victoire==1){
		text_surface = TTF_RenderText_Blended(font, "Vous avez survecu !", color); // création du texte dans la surface
	}
	else{
		text_surface = TTF_RenderText_Blended(font, "C'est la fin du voyage  :c", color); // création du texte dans la surface
	}
	
	if (text_surface == NULL) end_sdl2(0, "Can't create text surface", window, renderer);

	SDL_Texture* text_texture = NULL;           // la texture qui contient le texte
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture

	if (text_texture == NULL) end_sdl2(0, "Can't create texture from surface", window, renderer);
	SDL_FreeSurface(text_surface);             // la texture ne sert plus à rien

	SDL_Rect pos = {window_dimensions.w/3, window_dimensions.h/3, 0, 0};              // rectangle où le texte va être prositionné
	SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);   // récupération de la taille (w, h) du texte
	SDL_RenderCopy(renderer, text_texture, NULL, &pos); // Ecriture du texte dans le renderer
	SDL_DestroyTexture(text_texture);    // On n'a plus besoin de la texture avec le texte

	//ne pas oublier le TTF_Quit() dans le programme principal
}


SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface* my_image = NULL;
    SDL_Texture* my_texture = NULL;
    my_image = IMG_Load(file_image_name);
    
    if (my_image == NULL) end_sdl2(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl2(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
  }

/*
 *La fonction affiche le météore à la position indiquée au préalable
 */
void play_with_meteore(SDL_Texture * texture_meteore,SDL_Window * window,SDL_Renderer * renderer,int position_x,int position_y)
{

SDL_Rect
    source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    destination = {0},                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
    state = {0};

  SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w,
                    &window_dimensions.h);
  SDL_QueryTexture(texture_meteore, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

  float zoom = 0.708;                             // zoom, car ces images sont un peu petites
  int offset_x = source.w / 5.9,                // La largeur d'une vignette de l'image
      offset_y = source.h / 5.9;                // La hauteur d'une vignette de l'image

  state.x = 50;
  state.y = 50;
  state.w = offset_x;
  state.h = offset_y;

  /* construction des différents rectangles autour de chacune des vignettes de la planche */

  destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
  destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
  destination.x = position_x; // Position en x pour l'affichage du sprite
  destination.y = position_y;  // Position en y pour l'affichage du sprite
  SDL_RenderCopy(renderer,                  // Préparation de l'affichage
                   texture_meteore,&state,&destination);
}


/*
 * la fonction affiche le vaisseau à l'endroit indiqué
 * pos_x est la colonne où la dernière ligne du tableau est positive (c'est-à-dire la valeur où doit se trouve le vaisseau)
 */
void play_with_texture_vaisseau(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer,int pos_x) 
{
     SDL_Rect 
           source = {0},                      // Rectangle définissant la zone de la texture à récupérer
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

     SDL_GetWindowSize(
         window, &window_dimensions.w,
         &window_dimensions.h);               // Récupération des dimensions de la fenêtre
     SDL_QueryTexture(my_texture, NULL, NULL,
                      &source.w, &source.h);  // Récupération des dimensions de l'image

     float zoom = 0.25;                        // Facteur de zoom à appliquer    
     destination.w = source.w * zoom;         // La destination est un zoom de la source
     destination.h = source.h * zoom;         // La destination est un zoom de la source
     destination.x = pos_x;    
     destination.y = window_dimensions.h-destination.h;  // La destination est au milieu de la hauteur de la fenêtre

     SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                    &source,
                    &destination);            
}

void background(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer) 
{
  SDL_Rect
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher

}

