CC=gcc
CFLAGS=-Wall
EXEC=jeu

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif

all= $(EXEC)
objects := $(wilcard *.o)

jeu : main.o hs_ia.o hs_structures.o hs_affichage.o hs_fichiers.o hs_mecaniques.o chaine.o
	$(CC) -o jeu main.o hs_ia.o hs_structures.o hs_fichiers.o hs_mecaniques.o hs_affichage.o chaine.o $(CGFLAGS)

main.o : main.c
	$(CC) -c main.c $(CGFLAGS)

chaine.o : lib/CHAINE.c lib/CHAINE.h
	$(CC) -c lib/CHAINE.c $(CGFLAGS)

hs_affichage.o : lib\HS_AFFICHAGE.c lib/HS_AFFICHAGE.h
	$(CC) -c lib/HS_AFFICHAGE.c $(CGFLAGS)

hs_fichiers.o : lib\HS_FICHIERS.c lib\HS_FICHIERS.h
	$(CC) -c lib/HS_FICHIERS.c $(CGFLAGS)

hs_structures.o : lib/HS_STRUCTURES.c lib/HS_STRUCTURES.h
	$(CC) -c lib/HS_STRUCTURES.c $(CGFLAGS)

hs_mecaniques.o : lib/HS_MECANIQUES.c lib/HS_MECANIQUES.h lib/HS_STRUCTURES.h lib/CHAINE.h
	$(CC) -c lib/HS_MECANIQUES.c $(CGFLAGS)

hs_ia.o : lib/HS_IA.c lib/HS_IA.h
	$(CC) -c lib/HS_IA.c $(CGFLAGS)
