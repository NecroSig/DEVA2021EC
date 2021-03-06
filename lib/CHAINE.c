#include <stdio.h>
#include <stdlib.h>


int longueur(char* string)
{
  if ( *string == '\0')
    return 0;
  else
    return 1 + longueur(string + 1);
}

int compare(char* str1, char* str2)
{
  if (*str1 == '\0' && *str2 == '\0' )
  {
    return 1;
  }
  if (*str1 != *str2)
  {
    return 0;
  }
  return compare(str1 + 1,str2 + 1);
}


void recop(char* str1, char* str2)
{
   if ( *str1 == '\0' )
   {
     *str2 = '\0';
     return;
   }
   *str2 = *str1;
   return recop(str1 + 1, str2 + 1);
}

char* extraction(char* src, int debut, int fin)
{
  char *extract = NULL;
  extract = malloc(sizeof(char)*(fin-debut));

  int i = debut;
  while (i <= fin)
  {
    extract[i-debut] = src[i];
    i++;
  }
  return extract;
}

char* concat(char* str1, char* str2)
{
  recop(str2,str1 + longueur(str1));
  return str1;
}

void minToMaj(char chaine[])
{
  int i = 0;
  while (chaine[i] != '\0')
  {
    if (chaine[i] >= 97 && chaine[i] <= 122) {chaine[i] -= 32;}
    i++;
  }
}

int* coordonneesVersEntier(char* coordonnees)
{
  int i;
  int* tab = NULL;
  tab = malloc(sizeof(int)*3);
  if (tab == NULL) {exit(0);}

  for (i=0; i<2; i++)
  {
    if (coordonnees[i] >=  '0' && coordonnees[i] <= '9')
    {
      *tab = (int) *(coordonnees + i) - '0' - 1; //ligne
    }
    else if (coordonnees[i] >=  'A' && coordonnees[i] <= 'I')
    {
      *(tab +1) = (int) *(coordonnees + i) - 'A' ; //colonne
    }
    else if (coordonnees[i] >=  'a' && coordonnees[i] <= 'i')
    {
      *(tab +1) = (int) *(coordonnees + i) - 'a' ;
    }
  }
  if (*tab > 8 || *(tab+1) > 8 || *tab < 0 || *(tab+1) < 0 ) //dans la limite du plateau
  {
    *tab = -1;
    *(tab + 1) = -1;
  }

  //printf("sortie Char to int : [%d,%d]\n",tab[0],tab[1] );
  free(coordonnees);
  return tab;
}

char* entierVersCoordonnees(int* coordonnees)
{
  char* tab = NULL;
  tab = malloc(sizeof(char)*3);
  if (tab == NULL) {exit(0);}

  *tab = (char) *(coordonnees+1) + 'A';
  *(tab + 1) = (char) *(coordonnees) +'0' + 1;
  *(tab + 2) = '\0';

  return tab;
}

void viderBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

char* strsrch(char* chaine,char charac)
{
  int i=0;
  while(chaine[i] != charac)
  {
    i++;
  }
  return (chaine + i);
}

char get_c(int longueur)
{
  char* buffer = NULL;
  char lettre;

  buffer = malloc(sizeof(char)*longueur);

  if (buffer == NULL)
   exit(0);

  if ( fgets(buffer,longueur,stdin) != NULL)
  {
    while (*buffer != '\0')
    {
      if (*buffer != ' ' && *(buffer) != '\n')
      {
        lettre = *buffer;
        break;
      }
      buffer++;
    }
  }
  else
  {
    viderBuffer();
  }

  free(buffer);
  return lettre;
}


char* demanderChaine(int nbCaracteres)
{
  int i = 0;
  char *chaine = NULL;
  nbCaracteres++;

  chaine = malloc(sizeof(char) * nbCaracteres); //DANGER
  fgets(chaine,nbCaracteres,stdin);
  viderBuffer();

  for (i=0; i<=nbCaracteres+1; i++)
  {
    if (chaine[i] == '\n')
    {
      chaine[i] = '\0';
    }
  }

  //printf("Sortie demander Chaine : %s\n",chaine );
  return chaine;
}
