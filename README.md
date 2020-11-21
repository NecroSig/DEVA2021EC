Projet DEVA 2021
================

Objectif
--------

### Implémenter ou créer un jeu avec les conditions suivantes

+ Solo et Multijoueur possible
+ Au moins 2 niveaux de difficultés pour le Solo
+ Allocation Dynamique oblige
+ Sauvegarde + Charge possible
+ Lancement du jeu avec paramètres possible


Jeu Choisi : Hasami Shogi
-------------------------

Le Hasami Shogi est une variante du jeu d'échecs traditionnel japonais, il est plus communément appelé jeu "d'échecs d'interception", il a l'avantage de se jouer sur un plateau de 9x9 avec 2 rangées de 9 pions.

Le but de manger toutes les pièces de l'adversaire, pour manger une pièce il faut la "prendre en sandwich" que ce soit horizontalement que verticalement.

### Déplacement des pièces

+ Chaque joueur joue 1 pion par tour, n'importe lequel
+ Les pions se déplacent horizontalement et verticalement sans limite de cases, elles ne peuvent sauter de pions
+ Un pion par tour ne peut se déplacer qu'une seule fois

### Conditions de prise de pièce

+ Deux pièces d'un joueur doit englober sur une ligne ou colonne, des pions ennemis sans espace entre chaque pièce

### Conditions de victoire

Capturer toutes les pièces sauf une de de l'adversaire
