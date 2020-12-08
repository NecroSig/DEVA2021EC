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
        if (tab[i][j] == 1)
        {
          !(tj == 0) ? printf(" \\/ |") : printf(" \\/*|");
        }
        else if (tab[i][j] == 2)
        {
          !(tj == 1) ? printf(" /\\ |") : printf(" /\\*|");
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

void afficheInfosJeu(struct s_partie* p)
{
  //CLEARSCREEN();
  printf("--- Tour : %2d ---\n\n",p->compteurTour + 1 );
  printf("Tour du joueur %d\n",p->tourJoueur + 1);

  if (p->compteurTour == 0){}
  else {
    printf("Dernier coup joue : %s",p->dernierMouvement);

  }
  affichePlateau(p->plateau,p->tourJoueur);
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

void capture(int*** pions,int* coor)
{
  int* pionCapture = cherchePion(pions,coor);
  pionCapture[0] = -1;
  pionCapture[1] = -1;

  //add pions capture pour le joueur
}

//quand le pion se déplace on check si il y a des pions ennemis autour
void encercle(int** plat, int tj, int*** pions, char* derMove)
{
  int i;
  char* ptMove = extraction(derMove,6,8);
  int* coor = coordonneesVersEntier(ptMove);
  int* coorCap = malloc(sizeof(int) * 2);


  if (verifCase(plat,coor[0]+1,coor[1]) != tj+1 && verifCase(plat,coor[0]+1,coor[1]) != 0 )
  {
    i = coor[0] + 1;
    while (verifCase(plat,i,coor[1]) != tj+1 && verifCase(plat,i,coor[1]) != 0) {
      i++;
    }
    if (verifCase(plat,i,coor[1]) == tj+1)
    {
      coorCap[0] = i;
      coorCap[1] = coor[1]+1;
      capture(pions,coorCap);
      printf("Capture vers la bas !\n");
    }
  }

  if (verifCase(plat,coor[0]-1,coor[1]) != tj+1 && verifCase(plat,coor[0]-1,coor[1]) != 0 )
  {
    i = coor[0] - 1;
    while (verifCase(plat,i,coor[1]) != tj+1 && verifCase(plat,i,coor[1]) != 0) {
      i--;
    }
    if (verifCase(plat,i,coor[1]) == tj+1)
    {
      printf("Capture vers la haut !\n");
    }
  }

  if (verifCase(plat,coor[0],coor[1]+1) != tj+1 && verifCase(plat,coor[0],coor[1]+1) != 0 )
  {
    i = coor[1] + 1;
    while (verifCase(plat,coor[0],i) != tj+1 && verifCase(plat,coor[0],i) != 0) {
      i++;
    }
    if (verifCase(plat,coor[0],i) == tj+1)
    {
      printf("Capture vers le droite !\n");
    }
  }

  if (verifCase(plat,coor[0],coor[1]-1) != tj+1 && verifCase(plat,coor[0],coor[1]-1) != 0 )
  {
    i = coor[1] - 1;
    while (verifCase(plat,coor[0],i) != tj+1 && verifCase(plat,coor[0],i) != 0) {
      i--;
    }
    if (verifCase(plat,coor[0],i) == tj+1)
    {
      printf("Capture vers le gauche !\n");
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
    depart = coordonneesVersEntier(departTxt);
  } while(pionEJoueur(p->tourJoueur,p->pionsJoueurs,depart));

  pionAdeplacer = (int*) cherchePion(p->pionsJoueurs,depart);

  do
  {
    printf("Vers la case : ");
    arriveeTxt = demanderChaine(2);
    arrivee = coordonneesVersEntier(arriveeTxt);
  } while(mouvementPionPossible(p->plateau,pionAdeplacer,arrivee));



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

void tour(struct s_partie* p)
{
  refreshPlateau(p->pionsJoueurs,p->plateau);
  afficheInfosJeu(p);
  deplacementPion(p);
  encercle(p->plateau,p->tourJoueur,p->pionsJoueurs,p->dernierMouvement);


  p->compteurTour++;
  p->tourJoueur = p->compteurTour % 2;
}
