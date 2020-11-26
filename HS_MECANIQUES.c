#include <stdio.h>
#include <stdlib.h>

//A faire
//Fonction encercle ?
//


int** gen_plateau()
{
  int **tab = NULL;
  int i; int j;

  int nbLignes = 10;
  int nbColonnes = 10;

  //Allocation du tableau + 1 pour les infos plateau
  tab = (int**) malloc ( (nbLignes * sizeof(int*)));
  if (tab == NULL) {exit(0);}

  for ( i = 0 ; i < nbLignes ; i++ )
  {
    tab[i] = (int*) malloc(nbColonnes * sizeof(int));
  }

  //Remplissage du tableau - 1
  for (i = 0; i < nbLignes-1; i = i + 1)
  {
      for (j = 0; j < nbColonnes-1; j = j + 1)
      {
        tab[i][j] = 0 ;
      }
  }
  return tab;
}

void affichePlateau(int **tab)
{
  int i,j;
  int nbLignes = 10;
  int nbColonnes = 10;

  printf("\n");

  for (i=0; i<nbLignes; i++)
  {
    // Ligne du haut et entre lignes
    printf("|");
    for (j=0; j<nbColonnes; j++)
    {
      (j == 9) ?  :  printf("----|") ;
    }
    printf("\n|");
    //(printf(" %d",i))
    //remplissage cases
    for (j=0; j<nbColonnes; j++)
    {
      //if case == 1 affiche ami sinon ennemi sinon case vide
      if (i >= 9)
      {
        (j >= 9) ?  : (printf("%4d|",/*('A'+ j)*/j+1));
      }
      else
      {
        if (tab[i][j] == 1)
        {
          printf(" \\/ |");
        }
        else if (tab[i][j] == 2)
        {
          printf(" /\\ |");
        }
        else if (j >= 9)
        {
          printf(" %d", i+1);
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

int* coordonneesVersEntier(char* coordonnees)
{
  int* tab = NULL;
  tab = malloc(sizeof(int)*2);
  if (tab == NULL) {exit(0);}

  //A AJOUTER : Reconnaissance de la lettre et du chiffre

  *tab = (int) *coordonnees - 'A'+1;
  *(tab +1) = (int) *(coordonnees + 1) - '0';

  return tab;
}

char* entierVersCoordonnees(int* coordonnees)
{
  char* tab = NULL;
  tab = malloc(sizeof(char)*3);
  if (tab == NULL) {exit(0);}

  //A AJOUTER : Reconnaissance de la lettre et du chiffre

  *tab = (char) *coordonnees + 'A' - 1;
  *(tab + 1) = (char) *(coordonnees + 1) +'0';
  *(tab + 2) = '\0';

  return tab;
}

int*** gen_pionsjoueur()
{
    //Initialisation à 0
  int i;int j;int k;
  int*** pionsJoueur = NULL;
  pionsJoueur = malloc(sizeof(int**)*2);
  for (i=0; i<2 ;i++)
  {
    pionsJoueur[i] = malloc(sizeof(int*)*9);
  }

  for (i=0; i<2;i++)
  {
    for (j=0; j<9; j++)
    {
      pionsJoueur[i][j] = malloc(sizeof(int)*2);
    }
  }

  // Si chargemement fichier, on suit le fichier
  for (i=0; i<2;i++)
  {
    for (j=0; j<9; j++)
    {
      //A partir de là il faut les placer sur le plateau à leur position initiale
      if (i == 0)
      {
        pionsJoueur[i][j][0] = 0;
        pionsJoueur[i][j][1] = j;
      }
      else if (i == 1)
      {
        pionsJoueur[i][j][0] = 8;
        pionsJoueur[i][j][1] = j;
      }
    }
  }
  return pionsJoueur;
}

void placementPionsPlateau(int*** pionsJoueurs, int** plateau)
{
  int i; int j;
  for (i=0; i<2;i++)
  {
    for (j=0; j<9; j++)
    {
      if (i == 0)
      {
        plateau[pionsJoueurs[i][j][0]][pionsJoueurs[i][j][1]] = 1;
      }
      else if (i == 1)
      {
        plateau[pionsJoueurs[i][j][0]][pionsJoueurs[i][j][1]] = 2;
      }
    }
  }
}

void libererPionsJoueurs(int ***instance)
{
  


}
