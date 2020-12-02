#include <stdlib.h>
#include <stdio.h>
#include "CHAINE.h"
#include "HS_STRUCTURES.h"
#include "HS_MECANIQUES.h"

#if _WIN32
    #define CLEARSCREEN(); system("cls");
  #elif __LINUX__
    #define CLEARSCREEN(); system("clear");
	#else
	  #define CLEARSCREEN(); printf("\n");
#endif



int main(int argc, char *argv[])
{
  //menu
  /*
  char *bienvenue = "Hasami Shogi";
  char *hr = "------------";
  char *version = "Version Alpha 0.1";

  int **plateau = gen_plateau();

  plateau[0][0] = 1;
  plateau[0][1] = 2;
  affichePlateau(plateau);

  int* test = coordonneesVersEntier("2G");
  char* lol = entierVersCoordonnees(test);
  printf("%d %d",test[0], test[1] );
  printf("\n%s",lol );
  */

  int **plateau = gen_plateau();
  int ***pions = gen_pionsjoueur();

  while (1) {
    //CLEARSCREEN();
    refreshPlateau(pions,plateau);
    affichePlateau(plateau);
    deplacementPion(plateau,pions);
    //affichePionsJoueur(pions);
  }

  return 0;
}
