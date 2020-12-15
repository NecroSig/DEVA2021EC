#ifndef CHAINE

#define CHAINE

int longueur(char* string);
int compare(char* str1, char* str2);
char* concat(char* str1, char* str2);
void recop(char* str1, char* str2);
void minToMaj(char chaine[]);
int* coordonneesVersEntier(char* coordonnees);
char* entierVersCoordonnees(int* coordonnees);
char* demanderChaine(int nbCaracteres);
void viderBuffer();
char* extraction(char* src, int debut, int fin);

#endif
