#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "CHAINE.h"
#include "HS_MECANIQUES.h"
#include "HS_STRUCTURES.h"


//Partie IA
int rng(int borneMAX)
{
  static int premierAppel = 0;
  int rn;

  if (premierAppel == 0)
  {
    srand (time (NULL));
    premierAppel = 1;
  }

  rn = rand() % (borneMAX - 1) + 1;

  return (rn);
}

int* selectPionHasard(int*** pions, int tJ)
{
  int rn = rng(9);
  while (pions[tJ][rn-1][0] != -1)
  {
    rn = rng(9);
  }
  return pions[tJ][rn-1];
}


int numEnnemiAutour(int tJ, int* coor, int** plateau)
{
  int sum = 0;
  int pionAdv = ((tJ == 0) ? 1 : 0 ) + 1;
  sum += ( verifCase(plateau,coor[0]+1,coor[1]) == pionAdv ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0]-1,coor[1]) == pionAdv ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0],coor[1]+1) == pionAdv ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0],coor[1]-1) == pionAdv ) ? 1 : 0 ;

  return sum;
}

//parcours le terrain pour voir si un pion de la valeur voulue peut se déplacer a cette case
int parcoursPossible(int* coor, int** plateau, int tJ)
{
  int i;
  int valeurVoulue = (tJ == 0) ? 1 : 2;
  // haut
  if (verifCase(plateau,coor[0]+1,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) )
  {
    i = coor[0] + 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1]) )
    {
      //printf("voyage h\n");
      i++;
    }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      return 1;
    }
  }
  // bas
  if (verifCase(plateau,coor[0]-1,coor[1]) == 0 && pionDansLePlateau(coor[0]-1,coor[1])  )
  {
    i = coor[0] - 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1]))
    {
      //printf("Voyage b\n");
      i--;
    }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      return 1;
    }
  }
  // droite
  if (verifCase(plateau,coor[0],coor[1]+1) == 0 && pionDansLePlateau(coor[0],coor[1]+1) )
  {
    i = coor[1] + 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) )
    {
      //printf("Voyage d\n");
      i++;
    }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      return 1;
    }
  }
  // gauche
  if (verifCase(plateau,coor[0],coor[1]-1) == 0 && pionDansLePlateau(coor[0],coor[1]-1) )
  {
    i = coor[1] - 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) )
    {
      //printf("Voyage g\n");
      i--;
    }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      return 1;
    }
    return 0;
  }
}

//parcours le terrain pour voir si un pion de la valeur voulue peut se déplacer a cette case et renvoi la position du pion
int* parcoursPossibleReturnCoorPion(int* coor, int** plateau, int tJ)
{
  int i;
  int valeurVoulue = (tJ == 0) ? 1 : 2;
  int* coorV = malloc(sizeof(int)*2);
  // haut
  if (verifCase(plateau,coor[0]+1,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) )
  {
    i = coor[0] + 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1]) )
    {
      //printf("voyage h\n");
      i++;
    }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      coorV[0] = i;
      coorV[1] = coor[1];
      return coorV;
    }
  }
  // bas
  if (verifCase(plateau,coor[0]-1,coor[1]) == 0 && pionDansLePlateau(coor[0]-1,coor[1])  )
  {
    i = coor[0] - 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1]))
    {
      //printf("Voyage b\n");
      i--;
    }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      coorV[0] = i;
      coorV[1] = coor[1];
      return coorV;
    }
  }
  // droite
  if (verifCase(plateau,coor[0],coor[1]+1) == 0 && pionDansLePlateau(coor[0],coor[1]+1) )
  {
    i = coor[1] + 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) )
    {
      //printf("Voyage d\n");
      i++;
    }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      coorV[0] = coor[0];
      coorV[1] = i;
      return coorV;
    }
  }
  // gauche
  if (verifCase(plateau,coor[0],coor[1]-1) == 0 && pionDansLePlateau(coor[0],coor[1]-1) )
  {
    i = coor[1] - 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) )
    {
      //printf("Voyage g\n");
      i--;
    }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      coorV[0] = coor[0];
      coorV[1] = i;
      return coorV;
    }
  }
}

//retourne un ensemble de coordonnées des cases vides
int** prochaineCaseVide(int** plateau, int** tab,int tJ , int num, int* coor)
{
  int i;
  int j = 0;
  // bas
  if (verifCase(plateau,coor[0]+1,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0]+1,coor[1]) != 0 )
  {
    //printf("\tL'ennemi est en bas\n");
    i = coor[0] + 1;
    while (pionDansLePlateau(i,coor[1]) && verifCase(plateau,i,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,i,coor[1]) != 0)
    { i++; }
    if (verifCase(plateau,i,coor[1]) == 0 )
    {
      //printf("\tau tab [%d,%d]\n",i,coor[1] );

      tab[j][0] = i;
      tab[j][1] = coor[1];
      j++;
    }
  }
  // haut
  if (verifCase(plateau,coor[0]-1,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0]-1,coor[1]) != 0 )
  {
    //printf("\tL'ennemi est en haut\n");

    i = coor[0] - 1;
    while (pionDansLePlateau(i,coor[1]) && verifCase(plateau,i,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,i,coor[1]) != 0)
    { i--;}
    if (verifCase(plateau,i,coor[1]) == 0 )
    {
      //printf("au tab [%d,%d]\n",i,coor[1] );

      tab[j][0] = i;
      tab[j][1] = coor[1];
      j++;
    }
  }
  // droite
  if (verifCase(plateau,coor[0],coor[1]+1) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],coor[1]+1) != 0 )
  {
    //printf("\tL'ennemi est a droite\n");

    i = coor[1] + 1;
    while (verifCase(plateau,coor[0],i) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],i) != 0)
    {
      //printf("\ty'a t'il un ennemi en [%d,%d]\n",coor[0],i);
      i++;
    }
    //printf("\ty'a t'il un ennemi en [%d,%d]\n",coor[0],i);

    if (verifCase(plateau,coor[0],i) == 0 )
    {
      //printf("\t\tAjout[%d,%d]\n",i,coor[0] );

      tab[j][0] = coor[0];
      tab[j][1] = i;
      j++;
    }
  }
  // gauche
  //tant qu'il y a de l'ennemi on continu
  if (verifCase(plateau,coor[0],coor[1]-1) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],coor[1]-1) != 0 )
  {
    //printf("\tL'ennemi est a gauche\n");

    i = coor[1] - 1;
    while (verifCase(plateau,coor[0],i) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],i) != 0)
    {
      //printf("\ty'a t'il un ennemi en [%d,%d]\n",coor[0],i);
      i--;
    }
    //printf("\ty'a t'il un ennemi en [%d,%d]\n",coor[0],i);
    if (verifCase(plateau,coor[0],i) == 0 )
    {
      //printf("\t\tAjout[%d,%d]\n",i,coor[0] );

      tab[j][0] = coor[0];
      tab[j][1] = i;
      j++;
    }
  }

  if (j == 0)
  {
    tab[j][0] = -1;
    tab[j][1] = -1;
  }

  return tab;
}

int mouvementAleat(int*** pions,int* coor, int tJ, int** plateau,char* derMove)
{
  int i;
  int rnAxe = rng(2);
  int* coorCap = malloc(sizeof(int)*2);

  if (rnAxe == 1)
  {
    *coorCap = rng(8);
    *(coorCap + 1 ) = coor[1];

    i = 0;
    while ( !(verifCase(plateau,coorCap[0],coorCap[1]) == 0 && parcoursPossible(coorCap,plateau,tJ) == 1 ) )
    {
      *coorCap = rng(8);
      i++;
    }
    if ( verifCase(plateau,coorCap[0],coorCap[1]) == 0 && parcoursPossible(coorCap,plateau,tJ) == 1)
    {
      movePion(plateau,(int*) cherchePion(pions,parcoursPossibleReturnCoorPion(coorCap,plateau,tJ)),coorCap,derMove);
      free(coorCap);
      return 1;
    }
  }
  else
  {
    *coorCap = coor[0];
    *(coorCap + 1 ) = rng(8);

    i = 0;
    while ( !(verifCase(plateau,coorCap[0],coorCap[1]) == 0 && parcoursPossible(coorCap,plateau,tJ) == 1 ) )
    {
      *(coorCap + 1) = rng(8);
      i++;
    }
    if ( verifCase(plateau,coorCap[0],coorCap[1]) == 0 && parcoursPossible(coorCap,plateau,tJ) == 1)
    {
      movePion(plateau,cherchePion(pions,parcoursPossibleReturnCoorPion(coorCap,plateau,tJ)),coorCap,derMove);
      free(coorCap);
      return 1;
    }
  }
  free(coorCap);
  return 0;
}


//Deplacement qui mange un pion si il est en difficulte
int deplacementOpportuniste(int*** pions,int* coor, int tJ, int** plateau,char* derMove)
{
  int i;
  int num = numEnnemiAutour(tJ,coor,plateau);
  if (num > 0)
  {
  //printf("IA : deplacement Opportuniste :\n");
    //printf("il y a %d ennemis autour du pion coor\n",num);
    int** tableauCaseAVerifier = malloc(sizeof(int*)*num);
    for (i = 0; i < num; i++)
    {
      tableauCaseAVerifier[i] = malloc(sizeof(int)*2);
    }

    tableauCaseAVerifier = prochaineCaseVide(plateau,tableauCaseAVerifier,tJ,num,coor);
    if (tableauCaseAVerifier[0][0] == -1)
    {
      num = 0;
    }

    for (i = 0; i < num ; i++)
    {
      //printf("\t\tCase a verifier : [%d,%d] \n",tableauCaseAVerifier[i][0],tableauCaseAVerifier[i][1]);
      if (!pionDansLePlateau(tableauCaseAVerifier[i][0],tableauCaseAVerifier[i][1]))
      {
        //printf("pas dans le plateau\n");
        continue;
      }
      if ( parcoursPossible(tableauCaseAVerifier[i],plateau,tJ))
      {
        int* potentielPion = parcoursPossibleReturnCoorPion(tableauCaseAVerifier[i],plateau,tJ);
        int* pion =  cherchePion(pions,potentielPion);
        if (!mouvementPionPossible(plateau,coor,pion))
        {
          //printf("pas possible\n");
          break;
        }
        movePion(plateau,pion,tableauCaseAVerifier[i],derMove);

        for (i = 0; i < num; i++)
        {
          free(tableauCaseAVerifier[i]);
        }
        free(tableauCaseAVerifier);
        free(potentielPion);
        return 1;
      }
    }

    for (i = 0; i < num; i++)
    {
      free(tableauCaseAVerifier[i]);
    }
    free(tableauCaseAVerifier);
  }
  return 0;
}

void ia_heuristiqueSimple(struct s_partie* p)
{
  /*
    COMPORTEMENT BASIQUE DE L IA

    - SI ELLE PEUT MANGER UN PION ELLE LE MANGE
    - SINON ELLE VERIFIE QU ELLE N EST PAS EN DANGER
    - SINON ELLE SE DEPLACE HORS DE SA BASE
    - SINON ELLE REALISE UN MOUVEMENT ALEATOIRE
  */

  //faire chaque action pour chaque pion #chronophage

  int i;
  int j;
  //Deplacement Opportuniste
  for (i = 0; i < 9; i++)
  {
    if (deplacementOpportuniste(p->pionsJoueurs,p->pionsJoueurs[1][i],p->tourJoueur,p->plateau,p->dernierMouvement))
    {
      //puts("IA : deplacement Opportuniste reussi");
      return;
    }
  }
  //puts("IA : deplacement Opportuniste Impossible");

  //mouvement Aleatoire
  for (i = 0; i < 9; i++)
  {
    if (mouvementAleat(p->pionsJoueurs,p->pionsJoueurs[1][rng(9)],p->tourJoueur,p->plateau,p->dernierMouvement))
    {
      //puts("IA : deplacement Aleatoire reussi");
      return;
    }
  }
  //puts("IA : deplacement Aleatoire Impossible");

}
