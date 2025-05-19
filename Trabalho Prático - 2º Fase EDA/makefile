all: prog

biblioteca/grafo.o: biblioteca/grafo.c biblioteca/grafo.h
	gcc -c biblioteca/grafo.c -o biblioteca/grafo.o

prog: main/main.c biblioteca/grafo.o
	gcc main/main.c biblioteca/grafo.o -o prog.exe

run: prog
	./prog.exe
