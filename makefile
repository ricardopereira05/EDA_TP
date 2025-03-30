all: prog

funcoes.o: funcoes.h funcoes.c
	gcc -c funcoes.c -o funcoes.o

prog: main.c funcoes.o
	gcc main.c funcoes.o -o prog.exe

run: prog
	./prog.exe
