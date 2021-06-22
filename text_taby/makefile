C= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o balek.o 
	$(CC) main.o balek.o  $(SDL2) -o prog

main.o : main.c main.h
	$(CC) $(OPT) main.c

balek.o : balek.c balek.h
	$(CC) $(OPT) balek.c


clear :
	rm *.o
        
propre :
	rm prog

