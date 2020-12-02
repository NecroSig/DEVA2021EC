CC=gcc
CFLAGS=-Wall
EXEC=jeu

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif

all= $(EXEC)

jeu : main.o hs_structures.o hs_mecaniques.o chaine.o
	$(CC) -o jeu main.o hs_structures.o hs_mecaniques.o chaine.o $(CGFLAGS)

main.o : main.c
	$(CC) -c main.c $(CGFLAGS)

chaine.o : CHAINE.c CHAINE.h
	$(CC) -c CHAINE.c $(CGFLAGS)

hs_structures.o : HS_STRUCTURES.c HS_STRUCTURES.h
	$(CC) -c HS_STRUCTURES.c $(CGFLAGS)

hs_mecaniques.o : HS_MECANIQUES.c HS_MECANIQUES.h CHAINE.h
	$(CC) -c HS_MECANIQUES.c $(CGFLAGS)
