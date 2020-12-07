#include <stdlib.h>

struct s_partie
{
  int tourJoueur; // 0=J1, 1=J2
  int compteurTour;
  int *pionsCaptures; //[nbPionsJ1,nbPionsJ2]
  int **plateau;
  int ***pionsJoueurs; //[ [ [1,1],[1,2] ] [ [9,1][9,2] ] ]
  char *dernierMouvement; //Format : A2 -> D2
};

struct s_jeu
{
  int solo; //0=n 1=y
  int difficulte;
  char *nameFile; //NULL
  char **playerNames; //["Trevor","Bryan"]
  struct s_partie *partie;
};


struct s_jeu* initialisationJeu()
{
  //Malloc à rajouter
  struct s_jeu* jeu = malloc(sizeof(struct s_jeu));
  if (jeu == NULL) {exit(0);}

  jeu -> solo = 2;
  jeu -> difficulte = 0;
  jeu -> nameFile = NULL;
  jeu -> playerNames = NULL;
  jeu -> partie = NULL;

  return jeu;
}

struct s_partie* initialisationPartie()
{
  struct s_partie* partie = malloc(sizeof(struct s_partie));
  if (partie == NULL) {exit(0);}

  partie -> tourJoueur = 0;
  partie -> compteurTour = 0;
  partie -> pionsCaptures = NULL;
  partie -> plateau = NULL;
  partie -> pionsJoueurs = NULL;
  partie -> dernierMouvement = malloc(sizeof(char)*8);
}

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


int deconstructionJeu(struct s_jeu* instance)
{
  if (instance->playerNames != NULL)
  {
    free(instance->playerNames);
  }
  free(instance);
}
