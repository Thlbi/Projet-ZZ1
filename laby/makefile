CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm

prog : kruskal.o graph_aretes_tab.o partition.o tas.o main.o affichage_image.o
	$(CC)  kruskal.o graph_aretes_tab.o partition.o tas.o main.o affichage_image.o $(SDL2) -o prog

main.o : main.c main.h
	$(CC) $(OPT) main.c

affichage_image.o : affichage_image.c affichage_image.h
	$(CC) $(OPT) affichage_image.c

graph_aretes_tab.o: graph_aretes_tab.c graph_aretes_tab.h
	$(CC) $(OPT) graph_aretes_tab.c

kruskal.o : kruskal.c kruskal.h
	$(CC) $(OPT) kruskal.c 

partition.o : partition.c partition.h
	$(CC) $(OPT) partition.c 

tas.o : tas.c tas.h
	$(CC) $(OPT) tas.c 

clear :
	rm *.o
