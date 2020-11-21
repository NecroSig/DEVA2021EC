#include <stdio.h>
#include <stdlib.h>

typedef struct s_partie
{
  int tourJoueur; // 0=J1, 1=J2
  int compteurTour;
  int *pionsCaptures; //[nbPionsJ1,nbPionsJ2]
  int **plateau;
  int ****pionsJoueurs; //[  [ [1,1],[1,2] ] [ [9,1][9,2] ]  ]
  char *dernierMouvement; //Format : A2 -> D2
}t_partie;

typedef struct s_jeu
{
  int solo; //0=n 1=y
  int difficulte;
  char *nameFile; //NULL
  char **playerNames; //["Trevor","Bryan"]
  t_partie *partie;
}t_jeu;

t_jeu* initialisation()
{
  t_jeu* jeu = malloc( sizeof(t_partie) );
  if (jeu == NULL) {exit(0);}

  jeu -> solo = 1;
  jeu -> difficulte = 0;
  jeu -> nameFile = NULL;
  jeu -> playerNames = NULL;
  jeu -> partie = NULL;

  return jeu;
}

int main()
{
  t_jeu *jeu = initialisation();

  return 0;
}
