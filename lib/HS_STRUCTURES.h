#ifndef HS_STRUCTURES

#define HS_STRUCTURES

struct s_partie
{
  int pause;
  int load;
  int save;
  int tourJoueur; // 0=J1, 1=J2
  int compteurTour;
  int *pionsRestants; //[nbPionsJ1,nbPionsJ2]
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

int** gen_plateau();
int*** gen_pionsjoueur();
struct s_jeu* initialisationJeu();
struct s_partie* initialisationPartie();

void deconstructionPartie(struct s_partie* instance);

#endif
