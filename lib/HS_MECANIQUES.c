#include <stdio.h>
#include <stdlib.h>
#include "HS_STRUCTURES.h"
#include "HS_AFFICHAGE.h"
#include "HS_FICHIERS.h"
#include "CHAINE.h"

void logF(char* txt)
{
  FILE *f;
  f = fopen("log.log", "a+");
  if (f == NULL) { exit(0);}
  fprintf(f,"%s \n",txt);
  fclose(f);
}

int victoire(int* pionsR, int tJ)
{
  if (pionsR[( (tJ == 0) ? 0 : 1 )] <= 2)
  {
    return 1;
  }
  return 0;
}

int pionDansLePlateau(int x, int y)
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

void checkPionsEtPlateau(struct s_jeu* jeu)
{
  int i;
  int j;
  //check Pions
  for (i = 0; i < 2; i++)
  {
    for (j=0; j<9; j++)
    {
      if (pionDansLePlateau(jeu->partie->pionsJoueurs[i][j][0],jeu->partie->pionsJoueurs[i][j][1]))
      {
        printf("erreur pions");
      }
    }
    printf("\n");
  }
  //check plateau
  for (i = 0; i < 8; i++)
  {
    for (j=0; j < 8; j++)
    {
      if (!(jeu->partie->plateau[i][j] >= 0 && jeu->partie->plateau[i][j] <= 3))
      {
        printf("erreur plateau");
      }
    }
  }
}

void refreshPlateau(int*** pionsJoueurs, int** plateau)
{
  //fonction a remettre au gout du jour
  int i; int j;
  for (i=0; i<2;i++)
  {
    for (j=0; j<9; j++)
    {
      if (i == 0 && pionsJoueurs[i][j][0] >= 0 && pionsJoueurs[i][j][0] <= 9)
      {
        plateau[pionsJoueurs[i][j][0]][pionsJoueurs[i][j][1]] = 1;
      }
      else if (i == 1 && pionsJoueurs[i][j][0] >= 0 && pionsJoueurs[i][j][0] <= 9)
      {
        plateau[pionsJoueurs[i][j][0]][pionsJoueurs[i][j][1]] = 2;
      }
    }
  }
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

int chercheNumPion(int*** pionsJoueurs,int* coordonnees)
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
        return j;
      }
    }
  }
  return -1;
}

int verifCase(int** plateau, int x, int y)
{
  if (x < 0 || x > 9 || y < 0 || y > 9 )
  {
    return 0;
  }
  else
  {
    return plateau[x][y];
  }
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

void capture(int** plt,int*** pions, int tj, int *pionsRestants, int* coor)
{
  int numPionCapture = chercheNumPion(pions,coor);
  int numJoueur = 0;
  numJoueur =  (tj == 0) ? 1 : 0;

  plt[pions[numJoueur][numPionCapture][0]][pions[numJoueur][numPionCapture][1]] = 0;

  pions[numJoueur][numPionCapture][0] = -1;
  pions[numJoueur][numPionCapture][1] = -1;

  pionsRestants[numJoueur]--;
}

void encercle(struct s_partie* p)
{
  int i;
  char* ptMove = extraction(p->dernierMouvement,longueur(p->dernierMouvement)-2,longueur(p->dernierMouvement));
  int* coor = coordonneesVersEntier(ptMove); //coor pion qui s'est deplacé
  int* coorCap = malloc(sizeof(int) * 2);

  //Si la valeur de la case y+1 du plateau par rapport a notre pion ne correspond pas a un pion de notre joueur et que la case n'est pas vide
  if (verifCase(p->plateau,coor[0]+1,coor[1]) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0]+1,coor[1]) != 0 )
  {
    i = coor[0] + 1; // cela veut dire que le pion est peut être encerclé donc on continu
    while (verifCase(p->plateau,i,coor[1]) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,i,coor[1]) != 0) {
      i++;
    }
    if (verifCase(p->plateau,i,coor[1]) == ( (p->tourJoueur == 0) ? 1 : 2 ))
    {
      // si il y a bien un point joueur au bout, les pions sont encerclés et doivent être capturés
      coorCap[1] = coor[1];

      while (i != coor[0]+1)
      {
        coorCap[0] = i - 1;
        capture(p->plateau,p->pionsJoueurs,p->tourJoueur,p->pionsRestants,coorCap);
        i--;
      }
    }
  }
  //bas
  if (verifCase(p->plateau,coor[0]-1,coor[1]) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0]-1,coor[1]) != 0 )
  {
    i = coor[0] - 1;
    while (verifCase(p->plateau,i,coor[1]) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,i,coor[1]) != 0) {
      i--;
    }
    if (verifCase(p->plateau,i,coor[1]) == ( (p->tourJoueur == 0) ? 1 : 2 ))
    {
      coorCap[1] = coor[1];

      while (i != coor[0] - 1)
      {
        coorCap[0] = i + 1;
        capture(p->plateau,p->pionsJoueurs,p->tourJoueur,p->pionsRestants,coorCap);
        i++;
      }
    }
  }
  //droite
  if (verifCase(p->plateau,coor[0],coor[1]+1) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0],coor[1]+1) != 0 )
  {
    i = coor[1] + 1;
    while (verifCase(p->plateau,coor[0],i) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0],i) != 0) {
      i++;
    }
    if (verifCase(p->plateau,coor[0],i) == ( (p->tourJoueur == 0) ? 1 : 2 ))
    {
      coorCap[0] = coor[0];

      while (i != coor[1]+1)
      {
        coorCap[1] = i - 1;
        capture(p->plateau,p->pionsJoueurs,p->tourJoueur,p->pionsRestants,coorCap);
        i--;
      }
    }
  }
  //gauche
  if (verifCase(p->plateau,coor[0],coor[1]-1) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0],coor[1]-1) != 0 )
  {
    i = coor[1] - 1;
    while (verifCase(p->plateau,coor[0],i) != ( (p->tourJoueur == 0) ? 1 : 2 ) && verifCase(p->plateau,coor[0],i) != 0) {
      i--;
    }
    if (verifCase(p->plateau,coor[0],i) == ( (p->tourJoueur == 0) ? 1 : 2 ) )
    {
      while (i != coor[1]-1)
      {
        coorCap[0] = coor[0];
        coorCap[1] = i + 1;
        capture(p->plateau,p->pionsJoueurs,p->tourJoueur,p->pionsRestants,coorCap);
        i++;
      }
    }
  }

  free(ptMove);
  free(coor);
}

int deplacementPion(struct s_partie* p)
{
  int *depart = malloc(sizeof(int) *2);
  char *departTxt = malloc(sizeof(char) *2);
  int *arrivee = malloc(sizeof(int) *2);
  char *arriveeTxt = malloc(sizeof(char) *2);
  int *pionAdeplacer;

  pionAdeplacer = NULL;

  do
  {
    printf("\nChoisissez votre pion : ");
    departTxt = demanderChaine(2);

    if (compare(departTxt,"00"))
    {
      p->pause = 1;
      return 0;
    }

    depart = coordonneesVersEntier(departTxt);

  } while(pionEJoueur(p->tourJoueur,p->pionsJoueurs,depart));

  pionAdeplacer = (int*) cherchePion(p->pionsJoueurs,depart);

  printf("Vers la case : ");
  arriveeTxt = demanderChaine(2);
  arrivee = coordonneesVersEntier(arriveeTxt);



  if (!mouvementPionPossible(p->plateau,pionAdeplacer,arrivee) && !pionEJoueur(p->tourJoueur,p->pionsJoueurs,pionAdeplacer))
  {
    movePion(p->plateau,pionAdeplacer,arrivee);

    minToMaj(departTxt);
    minToMaj(arriveeTxt);
    sprintf(p->dernierMouvement,"%s -> %s",departTxt,arriveeTxt);

    free(depart);

    return 0;
  }
}

void tour(struct s_jeu* j)
{
    if (j->partie->pause == 2)
    {
      return;
    }
    //Debut du Tour
    refreshPlateau(j->partie->pionsJoueurs,j->partie->plateau);
    do {  afficheInfosJeu(j->partie); }
    while(deplacementPion(j->partie));

    //Verification si commande effectué
    if (j->partie->pause == 1)
    {
      return;
    }


    if (j->partie->compteurTour <= 1) {}
    else
      encercle(j->partie);
}
