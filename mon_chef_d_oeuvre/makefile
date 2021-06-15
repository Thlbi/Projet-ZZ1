C= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o affichage.o grille.o 
        $(CC) main.o affichage.o $(SDL2) -o prog

main.o : main.c main.h
        $(CC) $(OPT) main.c

affichage.o : affichage.c affichage.h
        $(CC) $(OPT) affichage.c

grille.o : grille.c grille.h
        $(CC) $(OPT) grille.c

clear :
	rm *.o
        
propre :
	rm prog

