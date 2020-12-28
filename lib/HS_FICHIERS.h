#ifndef HS_FICHIERS

#define HS_FICHIERS

int listerSaves(void);
char* renvoiNomSave(int nombre);
int sauvegarde(char* nomFichier, struct s_jeu* jeu);
int chargement(char* nomFichier, struct s_jeu* jeu);

#endif
