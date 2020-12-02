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
  struct s_partie *partie = initialisationPartie();


  partie->plateau = gen_plateau();
  partie->pionsJoueurs = gen_pionsjoueur();


  while (1) {
    //CLEARSCREEN();
    //changer pour passer les pointeurs des structures uniquement
    refreshPlateau(partie->pionsJoueurs,partie->plateau);
    affichePlateau(partie->plateau);
    deplacementPion(partie->plateau,partie->pionsJoueurs); //le joueur est verrouillé pour l'instant
    //affichePionsJoueur(pions);
  }

  return 0;
}
