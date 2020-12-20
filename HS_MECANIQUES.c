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
  if (pionsR[( (tJ == 0) ? 1 : 0 )] < 2)
  {
    return 1;
  }
  return 0;
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

int sauvegarde(char* nomFichier,struct s_jeu* jeu)
{
  int i;
  int j;
  FILE* fichier = NULL;
  fichier = fopen(nomFichier,"w+");

  if (fichier != NULL)
  {
    //S_jeu
    fprintf(fichier,"%d %d",jeu->solo,jeu->difficulte);

    //s_partie
    fprintf(fichier," %d %d %d %d ",
      jeu->partie->tourJoueur,
      jeu->partie->compteurTour,
      jeu->partie->pionsRestants[0],
      jeu->partie->pionsRestants[1]);

    //inutile de sauvegarder le plateau avec le rafraichissement de plateau
    for (i=0; i<2;i++)
    {
      for (j=0; j<9; j++)
      {
        fprintf(fichier,"[%d,%d]",
        jeu->partie->pionsJoueurs[i][j][0],
        jeu->partie->pionsJoueurs[i][j][1]);
      }
    }
    fprintf(fichier,"%s",jeu->partie->dernierMouvement);
    fclose(fichier);
  }
  else
  {
    printf("Impossible d'ouvrir le fichier %s",nomFichier);
    return 1;
  }

  return 0;
}

int chargement(char* nomFichier, struct s_jeu* jeu)
{
  int i;
  int j;
  FILE* fichier = NULL;
  fichier = fopen(nomFichier,"r");

  if (fichier != NULL)
  {
    fscanf(fichier,"%d %d",&jeu->solo,&jeu->difficulte);
    fscanf(fichier," %d %d %d %d ",
      &jeu->partie->tourJoueur,
      &jeu->partie->compteurTour,
      &jeu->partie->pionsRestants[0],
      &jeu->partie->pionsRestants[1]);

    for (i=0; i<2;i++)
    {
      for (j=0; j<9; j++)
      {
        fscanf(fichier,"[%d,%d]",
          &jeu->partie->pionsJoueurs[i][j][0],
          &jeu->partie->pionsJoueurs[i][j][1]);
      }
    }
    fgets(jeu->partie->dernierMouvement,9,fichier);

    fclose(fichier);
    viderBuffer();
    return 0;
  }
  else
  {
    printf("Impossible d'ouvrir le fichier %s",nomFichier);
    return 1;
  }
}

char* demanderNomJoueur(char* playername, int nbJoueur)
{
  printf("\nNom du joueur %d : ", nbJoueur);
  playername = demanderChaine(10);
  logF(playername);
  return playername;
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
          !(tj == 0) ? printf(" /\\ |") : printf(" /\\*|");
        }
        else if (tab[i][j] == 2)
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

void refreshPlateau(int*** pionsJoueurs, int** plateau)
{
  logF("f_refreshPlateau : 1 / 2");
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

  logF("f_refreshPlateau : 2 / 2");
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

void afficheInfosJeu(struct s_partie* p)
{
  //CLEARSCREEN();
  printf("--- Tour : %2d ---\n\n",p->compteurTour + 1 );
  printf("Tour du joueur %d \n",p->tourJoueur + 1);
  printf("Pions restants : %d\n",p->pionsRestants[p->tourJoueur] );

  if (p->compteurTour == 0){viderBuffer();}
  else {
    printf("\nDernier coup joue : %s",p->dernierMouvement);

  }
  affichePlateau(p->plateau,p->tourJoueur);
  printf("\n");
  logF(" 2 / 4 : Infos affichées");
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

  logF("4 / 4 : Encercle");
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
      p->save = 1;
      return 1;
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
    logF("Debut du tour");

    refreshPlateau(j->partie->pionsJoueurs,j->partie->plateau);

    do {
      afficheInfosJeu(j->partie);
    }
    while(deplacementPion(j->partie) && j->partie->save != 1);

    if (j->partie->save == 1)
    {
      sauvegarde("save",j);
      return;
    }

    if (j->partie->compteurTour <= 1) {}
    else{ encercle(j->partie); }

    logF("Fin du tour");
}

//Partie IA

int numEnnemiAutour(int tJ, int* coor, int** plateau)
{
  int sum = 0;
  sum += ( verifCase(plateau,coor[0]+1,coor[1]) == (tJ == 0) ? 2 : 1 ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0]-1,coor[1]) == (tJ == 0) ? 2 : 1 ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0],coor[1]+1) == (tJ == 0) ? 2 : 1 ) ? 1 : 0 ;
  sum += ( verifCase(plateau,coor[0],coor[1]-1) == (tJ == 0) ? 2 : 1 ) ? 1 : 0 ;

  return sum;
}

int parcoursPossible(int* coor, int** plateau, int tJ) //parcours le terrain dans les 4 directions
{
  int i;
  int valeurVoulue = (tJ == 0) ? 1 : 2;
  // haut
  if (verifCase(plateau,coor[0]+1,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) )
  {
    i = coor[0] + 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) ) { i++; }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      return 1;
    }
  }
  // bas
  if (verifCase(plateau,coor[0]-1,coor[1]) == 0 && pionDansLePlateau(coor[0]-1,coor[1])  )
  {
    i = coor[0] - 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1])) { i--; }
    if (verifCase(plateau,i,coor[1]) == valeurVoulue )
    {
      return 1;
    }
  }
  // droite
  if (verifCase(plateau,coor[0],coor[1]+1) == 0 && pionDansLePlateau(coor[0],coor[1]+1) )
  {
    i = coor[1] + 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) ) { i++; }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      return 1;
    }
  }
  // gauche
  if (verifCase(plateau,coor[0],coor[1]-1) == 0 && pionDansLePlateau(coor[0],coor[1]-1) )
  {
    i = coor[1] - 1;
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) ) { i++; }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      return 1;
    }
    return 0;
  }
}

int* parcoursPossibleReturnCoorPion(int* coor, int** plateau, int tJ)
{
  int i;
  int valeurVoulue = (tJ == 0) ? 1 : 2;
  int* coorV = malloc(sizeof(int)*2);
  // haut
  if (verifCase(plateau,coor[0]+1,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) )
  {
    i = coor[0] + 1;
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(coor[0]+1,coor[1]) ) { i++; }
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
    while (verifCase(plateau,i,coor[1]) == 0 && pionDansLePlateau(i,coor[1])) { i--; }
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
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) ) { i++; }
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
    while (verifCase(plateau,coor[0],i) == 0 && pionDansLePlateau(coor[0],i) ) { i++; }
    if (verifCase(plateau,coor[0],i) == valeurVoulue )
    {
      coorV[0] = coor[0];
      coorV[1] = i;
      return coorV;
    }
  }
}

int** prochaineCaseVide(int** plateau, int** tab,int tJ , int num, int* coor)
{
  int i;
  int j = 0;
  // haut
  if (verifCase(plateau,coor[0]+1,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0]+1,coor[1]) != 0 )
  {
    i = coor[0] + 1;
    while (verifCase(plateau,i,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,i,coor[1]) != 0) { i++; }
    if (verifCase(plateau,i,coor[1]) == 0 )
    {
      tab[j][0] = i;
      tab[j][1] = coor[1];
      j++;
    }
  }
  // bas
  if (verifCase(plateau,coor[0]-1,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0]-1,coor[1]) != 0 )
  {
    i = coor[0] - 1;
    while (verifCase(plateau,i,coor[1]) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,i,coor[1]) != 0) { i--; }
    if (verifCase(plateau,i,coor[1]) == 0 )
    {
      tab[j][0] = i;
      tab[j][1] = coor[1];
      j++;
    }
  }
  // droite
  if (verifCase(plateau,coor[0],coor[1]+1) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],coor[1]+1) != 0 )
  {
    i = coor[1] + 1;
    while (verifCase(plateau,coor[0],i) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],i) != 0) { i++; }
    if (verifCase(plateau,coor[0],i) == 0 )
    {
      tab[j][0] = coor[0];
      tab[j][1] = j;
      j++;
    }
  }
  // gauche
  if (verifCase(plateau,coor[0],coor[1]-1) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],coor[1]-1) != 0 )
  {
    i = coor[1] - 1;
    while (verifCase(plateau,coor[0],i) != ( (tJ == 0) ? 1 : 2 ) && verifCase(plateau,coor[0],i) != 0) { i++; }
    if (verifCase(plateau,coor[0],i) == 0 )
    {
      tab[j][0] = coor[0];
      tab[j][1] = j;
      j++;
    }
  }
  return tab;
}

void deplacementOpportuniste(int* coor, int tJ, int** plateau)
{
  int i;
  int num = numEnnemiAutour(tJ,coor,plateau);
  if (num > 0)
  {
    int** tableauCaseAVerifier = malloc(sizeof(int*)*num);
    for (i = 0; i < num; i++)
    {
      tableauCaseAVerifier[i] = malloc(sizeof(int)*2);
    }

    tableauCaseAVerifier = prochaineCaseVide(plateau,tableauCaseAVerifier,tJ,num,coor);

    for (i = 0; i < num ; i++)
    {
      if ( parcoursPossible(tableauCaseAVerifier[i],plateau,tJ) )
      {
        movePion(plateau,parcoursPossibleReturnCoorPion(tableauCaseAVerifier[i],plateau,tJ),tableauCaseAVerifier[i]);
        return;
      }
    }
  }
}
