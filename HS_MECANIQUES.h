#ifndef HS_MECANIQUES

#define HS_MECANIQUES

int** gen_plateau();
void affichePlateau(int **tab);
int* coordonneesVersEntier(char* coordonnees);
char* entierVersCoordonnees(int* coordonnees);
int*** gen_pionsjoueur();
void placementPionsPlateau(int*** pionsJoueurs, int** plateau);

#endif
