#include <stdio.h>
#include <stdlib.h>

#include "HS_STRUCTURES.h"
#include "CHAINE.h"

#if _WIN32
    #define CLEARSCREEN(); system("cls");
  #elif __LINUX__
    #define CLEARSCREEN(); system("clear");
	#else
	  #define CLEARSCREEN(); printf("\n");
#endif

int pionDansLePlateauX(int x, int y)
{
  if (x > 8 || x < 0 || y > 8 || y < 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


void affichePionsJoueur(int*** tab)
{
  int i;
  int j;
  for (i = 0; i < 2; i++)
  {
    for (j=0; j<9; j++)
    {
      printf("TAB[%d][%d] = [%d,%d]  \n",i,j,(tab[i][j][0]),(tab[i][j][1]));
    }
    printf("\n");
  }
}

void affichePlateau(int **tab, int tj)
{
  int i,j,k;
  int nbLignes = 10;
  int nbColonnes = 10;

  printf("\n");

  for (i=0; i<nbLignes; i++)
  {
    // Ligne du haut et entre lignes
    printf("%c",179);
    for (j=0; j<nbColonnes; j++)
    {
      if (j == 9) { }
      else
      {
        for(k=0;k<4;k++){printf("%c",196);}
        printf("%c",197);
      }
    }
    printf("\n%c",179);

    //remplissage cases
    for (j=0; j<nbColonnes; j++)
    {
      if (i >= 9)
      {
        (j >= 9) ?  : (printf("%4c|",('A'+ j))); //affichage lettre colonne
      }
      else
      {
        //if case == 1 affiche ami sinon ennemi sinon case vide
        if (pionDansLePlateauX(i,j)
        &&  tab[i][j] == 1)
        {
          !(tj == 0) ? printf(" /\\ |") : printf(" /\\*|");
        }
        else if (pionDansLePlateauX(i,j)
        &&  tab[i][j] == 2)
        {
          !(tj == 1) ? printf(" \\/ |") : printf(" \\/*|");
        }
        else if (j >= 9)
        {
          printf(" %d", i+1); //affichage chiffre lignes
        }
        else
        {
          printf("    |");
        }
      }
    }
    printf("\n");
  }
}

void afficheInfosJeu(struct s_partie* p)
{
  CLEARSCREEN();
  printf("--- Tour : %2d ---\n\n",p->compteurTour + 1 );
  printf("Tour du joueur %d \n",p->tourJoueur + 1);
  printf("Pions restants : %d\n",p->pionsRestants[p->tourJoueur] );
  if (p->compteurTour == 0){}
  else {
    printf("\nDernier coup joue : %s",p->dernierMouvement);

  }
  affichePlateau(p->plateau,p->tourJoueur);
  puts("");
  puts("Menu Pause -> 00");
}
