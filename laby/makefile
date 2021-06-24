CC= gcc
OPT  = -c -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm

prog : kruskal.o graph_aretes_tab.o partition.o tas.o main.o affichage_image.o dijkstra.o texture_perso.o colision.o DFS.o
	$(CC)  kruskal.o graph_aretes_tab.o partition.o tas.o main.o affichage_image.o dijkstra.o texture_perso.o colision.o DFS.o $(SDL2) -o prog

main.o : main.c main.h
	$(CC) $(OPT) main.c

dijkstra.o : dijkstra.c dijkstra.h
	$(CC) $(OPT) dijkstra.c

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

texture_perso.o : texture_perso.c texture_perso.h
	$(CC) $(OPT) texture_perso.c

colision.o : colision.c colision.h
	$(CC) $(OPT) colision.c

DFS.o : DFS.c DFS.h
	$(CC) $(OPT) DFS.c

clear :
	rm *.o
