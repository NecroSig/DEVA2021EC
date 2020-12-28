Projet DEVA 2021
================

Objectif
--------

### Implémenter ou créer un jeu avec les conditions suivantes

+ Jouable en Solo et Multijoueur
+ Au moins 2 niveaux de difficultés pour le Solo
+ Sauvegarde & Chargement
+ Démarrage par argument
+ Au moins 1 structure de données dynamique


Jeu Choisi : Hasami Shogi
-------------------------

Le Hasami Shogi est une variante du jeu d'échecs traditionnel japonais, il est plus communément appelé jeu "d'échecs d'interception", se joue sur un plateau de 9x9 cases avec 2 rangées de 9 pions.

Le but de manger toutes les pièces de l'adversaire, pour manger une pièce il faut la "prendre en sandwich" que ce soit horizontalement que verticalement.

### Déplacement des pièces

+ Chaque joueur joue 1 pion par tour, n'importe lequel
+ Les pions se déplacent horizontalement et verticalement sans limite de cases, elles ne peuvent sauter de pions

### Conditions de prise de pièce

+ Deux pièces d'un joueur doit englober sur une ligne ou colonne, des pions ennemis sans espace entre chaque pièce

### Remarques

+ Si un pion va entre deux pièces ennemis, il ne se fait pas capturer, la capture se fait par le joueur qui joue

### Conditions de victoire

Que l'adversaire possède plus que deux pièces ou moins
