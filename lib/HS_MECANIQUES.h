#ifndef HS_MECANIQUES

#define HS_MECANIQUES

int victoire(int* pionsR, int tJ);
void refreshPlateau(int*** pionsJoueurs, int** plateau);
int verifCase(int** plateau, int x, int y);
void logF(char* txt);
int pionDansLePlateau(int x, int y);
int* cherchePion(int*** pionsJoueurs,int* coordonnees);
void movePion(int** plateau, int* depart, int* arrivee, char* derMove);
void checkPionsEtPlateau(struct s_jeu* jeu);
int mouvementPionPossible(int** plateau,int* depart, int* arrivee);
void tour(struct s_jeu* j);


#endif
