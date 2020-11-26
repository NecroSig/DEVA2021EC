#include <stdlib.h>
#include "HS_STRUCTURES.h"
#include "HS_MECANIQUES.h"

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
  affichePlateau(plateau);
  printf("LOG");
  int ***pions = gen_pionsjoueur();
  placementPionsPlateau(pions,plateau);
  affichePlateau(plateau);

  return 0;
}
