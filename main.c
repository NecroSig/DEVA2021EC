#include <stdio.h>
#include "HS_STRUCTURES.h"
#include "HS_MECANIQUES.h"




int main(int argc, char *argv[])
{
  //menu
  struct s_partie *partie = initialisationPartie();


  partie->plateau = gen_plateau();
  partie->pionsJoueurs = gen_pionsjoueur();


  while (1) {



    tour(partie);
  }

  return 0;
}
