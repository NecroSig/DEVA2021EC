#include <stdio.h>
#include <stdlib.h>
#include "CHAINE.h"

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


void affichePlateau(int **tab)
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

void refreshPlateau(int*** pionsJoueurs, int** plateau)
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
  // A faire
}


int* cherchePion(int*** pionsJoueurs,int* coordonnees)
{
  int i;
  int j;

  for (i=0; i<2;i++)
  {
    for (j=0; j<9; j++)
    {
      if (pionsJoueurs[i][j][0] == coordonnees[0] && pionsJoueurs[i][j][1] == coordonnees[1])
      {
        //printf("--- \nSortie Cherche pion\n---\n");
        return pionsJoueurs[i][j];
      }
    }
  }
  return NULL;
}


void movePion(int** plateau, int* depart, int* arrivee)
{
  //retirer le pion du plateau et échanger les valeurs
  plateau[depart[0]][depart[1]] = 0;

  depart[0] = arrivee[0];
  depart[1] = arrivee[1];
}

int pionEJoueur(int nbJoueur,int*** pions, int* pionSelect)
{
  int i;

  for (i = 0; i < 9; i++)
  {
    if (pions[nbJoueur][i][0] == pionSelect[0] && pions[nbJoueur][i][1] == pionSelect[1])
    {
      //printf("Pion appartient au joueur\n");
      return 0;
    }
  }
  //printf("Pion n'appartient pas au joueur\n");
  return 1;
}


int mouvementPionPossible(int** plateau,int* depart, int* arrivee)
{
  int i;
  int j;
  int diff = 0;

  if (depart[0] != arrivee[0] && depart[1] != arrivee[1]) //interdiction mouvement diagonale
  {
    //printf("mouvement impossible\n");
    return 1;
  }

  if (depart[0] != arrivee[0])
  {
    diff = depart[0] - arrivee[0];
    if (diff > 0)
    {
      for (i = depart[0]-1; i != arrivee[0]; i--)
      {
        if (plateau[i][depart[1]] > 0)
        {
          return 1;
        }
      }
    }
    else
    {
      for (i = depart[0]+1; i != arrivee[0]; i++)
      {
        if (plateau[i][depart[1]] > 0)
        {
          return 1;
        }
      }
    }
  }
  else
  {
    diff = depart[1] - arrivee[1];
    if (diff > 0)
    {
      for (i = depart[1]-1; i != arrivee[1]; i--)
      {
        if (plateau[depart[0]][i] > 0)
        {
          return 1;
        }
      }
    }
    else
    {
      for (i = depart[1]+1; i != arrivee[1]; i++)
      {
        if (plateau[depart[0]][i] > 0)
        {
          return 1;
        }
      }
    }
  }

  if (plateau[arrivee[0]][arrivee[1]] == 0)
  {
    return 0;
  }
}


int deplacementPion(int** plateau, int*** pions)
{
  int *depart = malloc(sizeof(int) *2);
  int *arrivee = malloc(sizeof(int) *2);
  int *pionAdeplacer;

  pionAdeplacer = NULL;

  do
  {
    printf("Choisissez votre pion : ");
    depart = coordonneesVersEntier(demanderChaine(2));
  } while(pionEJoueur(0,pions,depart));

  pionAdeplacer = (int*) cherchePion(pions,depart);

  do
  {
    printf("Vers la case : ");
    arrivee = coordonneesVersEntier(demanderChaine(2));
  } while(mouvementPionPossible(plateau,pionAdeplacer,arrivee));



  if (!mouvementPionPossible(plateau,pionAdeplacer,arrivee) && !pionEJoueur(0,pions,pionAdeplacer))
  {
    movePion(plateau,pionAdeplacer,arrivee);
    free(depart);
    free(arrivee);
    return 0;
  }
}

void afficheInfosJeu(int** plateau)
{
  affichePlateau(plateau);
}
