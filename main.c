#include <stdio.h>
#include <stdlib.h>

#include "lib/HS_STRUCTURES.h"
#include "lib/HS_MECANIQUES.h"
#include "lib/HS_AFFICHAGE.h"
#include "lib/HS_FICHIERS.h"
#include "lib/CHAINE.h"


#if _WIN32
    #define CLEARSCREEN(); system("cls");
  #elif __LINUX__
    #define CLEARSCREEN(); system("clear");
	#else
	  #define CLEARSCREEN(); printf("\n");
#endif



void menuPrincipal(struct s_jeu* jeu);
void hasamiShogi(struct s_jeu* jeu);
void menuPause(struct s_jeu* jeu);
void menuChargement(struct s_jeu* jeu);


int main(int argc, char *argv[])
{
  struct s_jeu* jeu = initialisationJeu();
  jeu -> partie = initialisationPartie();

  if (argc > 1)
  {
    puts("Demarrage par argument");
    printf("Il y a %d arguments\n",argc);
    int i;
    for (i=0; i<argc; i++)
    {
      printf("[%s]",argv[i]);
      puts("");
      if (compare(argv[i],"-save") && argv[i+1] != NULL)
      {
        chargement(argv[i+1],jeu);
        hasamiShogi(jeu);
        goto menu;
      }
      if (compare(argv[i],"-solo"))
      {
        jeu -> solo = 1;
        jeu -> partie = (jeu -> partie == NULL) ? initialisationPartie() : jeu->partie ;
        hasamiShogi(jeu);
        goto menu;
      }
      if (compare(argv[i],"-multi"))
      {
        jeu -> solo = 0;
        jeu -> partie = (jeu -> partie == NULL) ? initialisationPartie() : jeu->partie ;
        hasamiShogi(jeu);
        goto menu;
      }
    }
    menu: ;
    menuPrincipal(jeu);
  }
  else
  {
    menuPrincipal(jeu);

  }
  return 0;
}

void menuPrincipal(struct s_jeu* jeu)
{
  char nbUser = -1;
  int quit = 0;
  while (quit == 0)
  {
    CLEARSCREEN();
    puts("------------");
    puts("Hasami Shogi");
    puts("------------");
    puts("\n");
    puts("1 - Jeu Solo");
    puts("2 - Jeu Deux Joueurs");
    puts("3 - Charger une partie");
    puts("\n0 - Quitter");

    saisie:
    printf("\n\nVotre Choix : ");

    nbUser = get_c(10);
    nbUser -= '0';

    switch (nbUser)
    {
      case 0 :
        quit = 1;
        goto end;
        break;

      case 1 :
        jeu -> solo = 1;
        jeu -> partie = (jeu -> partie == NULL) ? initialisationPartie() : jeu->partie ;
        hasamiShogi(jeu);
        goto end;
      break;

      case 2 :
        jeu -> solo = 0;
        jeu -> partie = (jeu -> partie == NULL) ? initialisationPartie() : jeu->partie ;
        hasamiShogi(jeu);
        goto end;
      break;

      case 3 :
        jeu -> partie = (jeu -> partie == NULL) ? initialisationPartie() : jeu->partie ;
        menuChargement(jeu);
        goto end;
      break;

      default :
        printf("Saisie incorrecte !\n");
        goto saisie;
        break;
    }
    end: ;
    if (jeu->partie != NULL)
    {
      if (jeu->partie->load == 1)
      {
        jeu->partie->load = 0;
        hasamiShogi(jeu);
      }
    }
  }
}

void hasamiShogi(struct s_jeu* jeu)
{
  do {
    DebutTour: ;
    //Deroulement du tour
    tour(jeu);
    //Si sortie sauvegarde, on sauvegarde puis retour au menu

    if (jeu->partie->pause == 2)
    {
      deconstructionPartie(jeu->partie);
      jeu->partie = NULL;
      return;
    }
    if (jeu->partie->pause == 1)
    {
      jeu->partie->pause = 0;
      menuPause(jeu);
      goto DebutTour;
    }

    //Si le tour est considéré comme complet, on incrémente
    jeu->partie->compteurTour++;
    jeu->partie->tourJoueur = jeu->partie->compteurTour % 2;
    //on vérifie si la condition de victoire est avéré et on continue
  } while(!victoire(jeu->partie->pionsRestants,jeu->partie->tourJoueur));

  jeu->partie->compteurTour--;
  jeu->partie->tourJoueur = jeu->partie->compteurTour % 2;

  refreshPlateau(jeu->partie->pionsJoueurs,jeu->partie->plateau);
  afficheInfosJeu(jeu->partie);

  printf("\n\nPARTIE TERMIN%cE !\n",144);
  printf("Victoire du joueur %d en %d Tours !\n",jeu->partie->tourJoueur+1, jeu -> partie->compteurTour+1);
  printf("\n\nRetour au menu : Appuyez sur Entree pour continuer ...");
  deconstructionPartie(jeu->partie);
  jeu->partie = NULL;
  getchar();
  return;

}

void menuPause(struct s_jeu* jeu)
{
  CLEARSCREEN();
  char nbUser = -1;
  menu: ;
  puts("--------------------");
  puts("Hasami Shogi - Pause");
  puts("--------------------");
  puts("\n");
  puts("1 - Sauvegarder");
  puts("2 - Retour au jeu");
  puts("\n0 - Abandonner");

  saisie: ;
  printf("\n\nVotre Choix : ");

  nbUser = get_c(10);
  nbUser -= '0';

  switch (nbUser)
  {
    case 0 :
      printf("Etes-vous sur y/n : ");
      nbUser = get_c(10);

      if (nbUser == 'y')
      {
        jeu->partie->pause = 2;
        return;
      }
      break;
    case 1 :
      puts("Attention mettre le meme nom qu'une sauvegarde existante l'ecrasera !");
      printf("Entrez un nom de sauvegarde : ");
      jeu->nameFile = demanderChaine(30);
      sauvegarde(jeu->nameFile,jeu);
      puts("Appuyez sur Entree pour continuer ...");
      getchar();
    break;
    case 2 :
      return;
    break;
    default :
      puts("Saisie incorrecte !");
      goto saisie;
    break;
  }
}


void menuChargement(struct s_jeu* jeu)
{
  CLEARSCREEN();
  char nbUser = -1;
  puts("-------------------------");
  puts("Hasami Shogi - Chargement");
  puts("-------------------------");
  puts("\n");
  puts("Sauvegardes :\n");
  listerSaves();
  puts("\n0 - Quitter");
  puts("\n");

  printf("Choississez une sauvegarde : ");
  nbUser = get_c(10);

  nbUser -= '0';

  if (nbUser == 0)
  {
    return;
  }
  else
  {
    chargement(renvoiNomSave( (int) nbUser ),jeu);
    jeu->partie->load = 1;
  }
}
