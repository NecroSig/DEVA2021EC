#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "HS_STRUCTURES.h"
#include "CHAINE.h"

#ifndef WIN32
    #include <sys/types.h>
#endif

void listerSaves(void)
{
    int i = 1;
    DIR* rep = NULL;
    struct dirent* fichierLu = NULL;
    rep = opendir("save"); // choix arbitraire du dossier pour mon jeu

    if (rep == NULL)
        perror("");

    //Je skip le retour du dossier et le dossier actuel
    fichierLu = readdir(rep);
    fichierLu = readdir(rep);

    while ((fichierLu = readdir(rep)) != NULL)
    {
      printf("%d - %s\n",i,fichierLu->d_name);
      i++;
    }

    if (closedir(rep) == -1)
        perror("");
}

char* renvoiNomSave(int nombre)
{
  int i = 0;
  DIR* rep = NULL;
  struct dirent* fichierLu = NULL;
  rep = opendir("save"); // choix arbitraire du dossier pour mon jeu

  if (rep == NULL)
      perror("");

  //Je skip le retour du dossier et le dossier actuel
  fichierLu = readdir(rep);
  fichierLu = readdir(rep);

  while (i != nombre)
  {
    fichierLu = readdir(rep);
    i++;
  }

  if (closedir(rep) == -1)
      perror("");

  return fichierLu->d_name;
}

int sauvegarde(char* nomFichier,struct s_jeu* jeu)
{
  int i;
  int j;
  FILE* fichier = NULL;
  char path[40];
  recop("save/",path);
  concat(path,nomFichier);
  fichier = fopen(path,"w+");

  if (fichier != NULL)
  {
    //S_jeu
    fprintf(fichier,"%d %d",jeu->solo,jeu->difficulte);

    //s_partie
    fprintf(fichier," %d %d %d %d ",
      jeu->partie->tourJoueur,
      jeu->partie->compteurTour,
      jeu->partie->pionsRestants[0],
      jeu->partie->pionsRestants[1]);

    //inutile de sauvegarder le plateau avec le rafraichissement de plateau
    for (i=0; i<2;i++)
    {
      for (j=0; j<9; j++)
      {
        fprintf(fichier,"[%d,%d]",
        jeu->partie->pionsJoueurs[i][j][0],
        jeu->partie->pionsJoueurs[i][j][1]);
      }
    }
    fprintf(fichier,"%s",jeu->partie->dernierMouvement);
    fclose(fichier);
  }
  else
  {
    printf("Impossible d'ouvrir le fichier %s",nomFichier);
    return 1;
  }
  printf("Sauvegarde reussie !\n");
  return 0;
}

int chargement(char* nomFichier, struct s_jeu* jeu)
{
  int i;
  int j;
  FILE* fichier = NULL;
  char path[40];
  recop("save/",path);
  concat(path,nomFichier);
  fichier = fopen(path,"r");

  if (fichier != NULL)
  {
    fscanf(fichier,"%d %d",&jeu->solo,&jeu->difficulte);
    fscanf(fichier," %d %d %d %d ",
      &jeu->partie->tourJoueur,
      &jeu->partie->compteurTour,
      &jeu->partie->pionsRestants[0],
      &jeu->partie->pionsRestants[1]);

    for (i=0; i<2;i++)
    {
      for (j=0; j<9; j++)
      {
        fscanf(fichier,"[%d,%d]",
          &jeu->partie->pionsJoueurs[i][j][0],
          &jeu->partie->pionsJoueurs[i][j][1]);
      }
    }
    fgets(jeu->partie->dernierMouvement,9,fichier);

    fclose(fichier);
    return 0;
  }
  else
  {
    printf("Impossible d'ouvrir le fichier '%s' \n",nomFichier);
    return 1;
  }
}
