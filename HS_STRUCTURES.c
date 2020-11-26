#include <stdlib.h>

//Ajout du texte par fichier ?
//location A2
/*struct s_texte
{
  char bienvenue[] = "Hasami Shogi";
  char hr[] = "------------";
  char version[] = "Version Alpha 0.1";

};*/



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


int deconstructionJeu(struct s_jeu* instance)
{
  if (instance->playerNames != NULL)
  {
    free(instance->playerNames);
  }
  free(instance);
}
