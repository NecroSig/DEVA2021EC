#ifndef HS_MECANIQUES

#define HS_MECANIQUES

int victoire(int* pionsR, int tJ);
void refreshPlateau(int*** pionsJoueurs, int** plateau);
void tour(struct s_jeu* j);

void logF(char* txt);
void checkPionsEtPlateau(struct s_jeu* jeu);

#endif
