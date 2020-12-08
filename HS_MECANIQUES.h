#ifndef HS_MECANIQUES

#define HS_MECANIQUES


void affichePlateau(int **tab,int tj);
void affichePionsJoueur(int*** tab);
void refreshPlateau(int*** pionsJoueurs, int** plateau);
int deplacementPion(struct s_partie* p);
void movePion(int** plateau, int* depart, int* arrivee);
int *cherchePion(int*** pionsJoueurs,int* coordonnees); //renvoie pointeur vers le pion
int pionEJoueur(int nbJoueur,int*** pions, int* pionSelect);
int mouvementPionPossible(int** plateau,int* depart, int* arrivee);
void afficheInfosJeu(struct s_partie* p);
void tour(struct s_partie* p);



//Fonction a faire -> capture
// 1-> check si capture, 1.1-> détecteur de pions autour de soi
// 2-> remove pion
#endif
