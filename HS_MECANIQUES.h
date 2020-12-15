#ifndef HS_MECANIQUES

#define HS_MECANIQUES

#endif

char* demanderNomJoueur(char* playername, int nbJoueur);
int chargement(char* nomFichier, struct s_jeu* jeu);
int victoire(int* pionsR, int tJ);
void tour(struct s_jeu* j);
void logF(char* txt);
