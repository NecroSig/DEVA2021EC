CC=gcc
CFLAGS=-Wall
EXEC=jeu

all= $(EXEC)

jeu : main.o hs_structures.o hs_mecaniques.o
	$(CC) -o jeu main.o HS_STRUCTURES.o HS_MECANIQUES.o $(CGFLAGS)

main.o : main.c
	$(CC) -c main.c $(CGFLAGS)

hs_structures.o : HS_STRUCTURES.c HS_STRUCTURES.h
	$(CC) -c HS_STRUCTURES.c $(CGFLAGS)

hs_mecaniques.o : HS_MECANIQUES.c HS_MECANIQUES.h
	$(CC) -c HS_MECANIQUES.c $(CGFLAGS)

clean:
	rm -rf *.o
