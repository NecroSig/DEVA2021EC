#ifndef HS_MECANIQUES

#define HS_MECANIQUES

int** gen_plateau();
void affichePlateau(int **tab);
void affichePionsJoueur(int*** tab);
int*** gen_pionsjoueur();
void refreshPlateau(int*** pionsJoueurs, int** plateau);
int deplacementPion(int** plateau,int*** pions);
void movePion(int** plateau, int* depart, int* arrivee);
int *cherchePion(int*** pionsJoueurs,int* coordonnees); //renvoie pointeur vers le pion
int pionEJoueur(int nbJoueur,int*** pions, int* pionSelect);
int mouvementPionPossible(int** plateau,int* depart, int* arrivee);
void afficheInfosJeu(int** plateau); //fonction a développer



//Fonction a faire -> capture
// 1-> check si capture, 1.1-> détecteur de pions autour de soi
// 2-> remove pion
#endif
