#include <stdio.h>
#include "HS_STRUCTURES.h"
#include "HS_MECANIQUES.h"




int main(int argc, char *argv[])
{
  struct s_jeu* jeu = initialisationJeu();

  if (argc > 1)
  {
    logF("Demarrage par argument");
    printf("Y a de l argument les gars !\n");
  }
  else
  {
    char nbUser = -1;
    menu: ;
    printf("------------\n");
    printf("Hasami Shogi\n");
    printf("------------\n");
    printf("\n\n");
    printf("1 - Jeu Solo\n");
    printf("2 - Jeu Deux Joueurs\n");
    printf("3 - Charger une partie\n");
    printf("\n0 - Quitter\n");

    saisie:
    printf("\n\nVotre Choix : ");

    scanf("%c",&nbUser);
    nbUser -= '0';

    switch (nbUser)
    {
      case 0 :
        goto end;
        break;
      case 1 :
        goto solo;
      break;
      case 2 :
        goto multi;
      break;
      case 3 :
        goto load;
      break;
      default :
        printf("Saisie incorrecte !\n");
        goto saisie;
        break;
    }
  }

  load: ;
  if (jeu->partie != NULL);
  else jeu -> partie = initialisationPartie();
  if (!chargement("save",jeu))
  {goto jeu;}
  else
  {goto menu;}


  solo: ;
  jeu -> solo = 1;
  
  goto menu;


  multi: ;
  jeu -> partie = initialisationPartie();
  jeu -> solo = 0;


  jeu: ;


  do {
    tour(jeu);
    if ( jeu->partie->save == 1)
    {
      printf("\nPartie Sauvegardee !\n");
      deconstructionPartie(jeu->partie);
      jeu->partie = NULL;
      goto menu;
    }
    jeu->partie->compteurTour++;
    jeu->partie->tourJoueur = jeu->partie->compteurTour % 2;
  } while(!victoire(jeu->partie->pionsRestants,jeu->partie->tourJoueur) || jeu->partie->save != 1 );

  jeu->partie->compteurTour--;
  jeu->partie->tourJoueur = jeu->partie->compteurTour % 2;

  printf("\n\nPartie Terminée !\n");
  printf("Victoire du joueur %d en %d Tours !\n",jeu->partie->tourJoueur, jeu -> partie->compteurTour+1);
  printf("\n\nRetour au menu : Appuyez sur Entree pour continuer ...");
  deconstructionPartie(jeu->partie);
  jeu->partie = NULL;
  getchar();
  goto menu;

  end:
  return 0;
}
