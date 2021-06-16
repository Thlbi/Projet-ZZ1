void end_sdl2(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer);
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void play_with_meteore(SDL_Texture * texture_meteore,SDL_Window * window,SDL_Renderer * renderer,position_x,position_y);
void play_with_texture_vaisseau(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer,int pos_x);
void background(SDL_Texture *my_texture, SDL_Window *window,SDL_Renderer *renderer);
void initialiser_texture();
void end_texture(SDL_Texture* my_texture,SDL_Texture* my_texture2,SDL_Texture* my_texture3,SDL_Texture* my_texture4,SDL_Texture* my_texture5);

