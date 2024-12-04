#ifndef RECETTES_H
#define RECETTES_H

#define _POSIX_C_SOURCE 200809L

#include "util.h"
#include <stdlib.h>
#include <string.h>

typedef struct recette {
   char *contenu;
   struct recette *precedent;
   struct recette *suivant;
} Recette;

typedef struct file_recettes {
   Recette *debut;
   Recette *fin;
   int nb_recettes;
} FileRecettes;

// Prototypes de fonctions
FileRecettes *initialiser_file_recettes();
int file_recettes_vide(FileRecettes *file_recettes);
Recette *creer_recette(FileRecettes *file_recettes, char *nom_recette);
void ajouter_recette(FileRecettes *file_recettes, Recette *recette);
Recette *chercher_recette(FileRecettes *file_recettes, char *nom_recette);
Recette *obtenir_recette(FileRecettes *file_recettes, char *nom_recette);
void trouver_ordre_recette(FileRecettes *file_recettes, Recette *recette);
void inserer_recette(FileRecettes *file_recettes, Recette *recette, Recette *precedent, Recette *pointeur);
void liberer_file_recettes(FileRecettes *file_recettes);

#endif
