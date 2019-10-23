#Autor: Matheus Augusto Marques

CFLAGS = -g -std=c++11

regalloc: regalloc.o Graph.o GraphColoring.o
	g++ $(CFLAGS) regalloc.o Graph.o GraphColoring.o -o regalloc

regalloc.o: regalloc.cpp GraphColoring.h GraphColoring.cpp
	g++ $(CFLAGS) -c regalloc.cpp -o regalloc.o
	
Graph.o: Graph.h Graph.cpp
	g++ $(CFLAGS) -c Graph.cpp -o Graph.o

GraphColoring.o: GraphColoring.h GraphColoring.cpp Graph.h Graph.cpp
	g++ $(CFLAGS) -c GraphColoring.cpp -o GraphColoring.o

.PHONY:
	clean

clean:
	rm -f *.o