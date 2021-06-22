
CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm

prog :  graph.o partition.o  labyrinthe.o affichage.o main.o 
	$(CC)   graph.o partition.o affichage.o labyrinthe.o main.o $(SDL2) -o prog

main.o : main.c main.h
	$(CC) $(OPT) main.c

graph.o: graph.c graph.h
	$(CC) $(OPT) graph.c
affichage.o: affichage.c affichage.h
	$(CC) $(OPT) affichage.c
partition.o : partition.c partition.h
	$(CC) $(OPT) partition.c 
labyrinthe.o : labyrinthe.c labyrinthe.h
	$(CC) $(OPT) labyrinthe.c
clear :
	rm *.o