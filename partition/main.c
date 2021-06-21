#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partition_a.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <time.h>
#include "labyrinthe.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "affichage_image.h"

int main(){
	srand(time(0));
	labyrinthe_arbo();
	
	return 0;
}
