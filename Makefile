CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g -O3
LFLAGS := -lm
INSTALL_DIR := /usr/sbin # Voy a tener que ser admin para instalar ahi

all: programa

main.o: main.c terreno.h config.h naves.h movimiento.h dibujar.h vector.h caracteres.h
	$(CC) $(CFLAGS) $(LFLAGS) main.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) caracteres.c

naves.o: naves.c naves.h
	$(CC) $(CFLAGS) naves.c

movimiento.o: movimiento.c movimiento.h config.h terreno.h
	$(CC) $(CFLAGS) movimiento.c $(LFLAGS) 

terreno.o: terreno.c terreno.h config.h vector.h movimiento.h
	$(CC) $(CFLAGS) terreno.c
	
dibujar.o: dibujar.c dibujar.h terreno.h config.h movimiento.h vector.h
	$(CC) $(CFLAGS) dibujar.c
	
diccionario.o: diccionario.c diccionario.h caracteres.h
	$(CC) $(CFLAGS) diccionario.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) vector.c

programa: main.o caracteres.o naves.o movimiento.o terreno.o dibujar.o diccionario.o vector.o
	$(CC) main.o caracteres.o naves.o movimiento.o terreno.o dibujar.o diccionario.o vector.o -o programa -lSDL2 $(LFLAGS) 

clean:
	rm *.o
