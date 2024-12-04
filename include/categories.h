#ifndef CATEGORIES_H
#define CATEGORIES_H

#define _POSIX_C_SOURCE 200809L

#include "util.h"
#include "recettes.h"
#include <stdlib.h>
#include <string.h>

// Structure de noeud pour une catégorie
typedef struct categorie {
   char *contenu;                         // Nom de la catégorie
   FileRecettes *file_recettes;           // Pointeur vers la liste de recettes de la catégorie
   struct categorie *precedent;           // Pointeur vers la catégorie précédente
   struct categorie *suivant;             // Pointeur vers la catégorie suivante
} Categorie;

// Structure pour une file de catégories
typedef struct file_categories {
   Categorie *debut;    // Pointeur vers la première catégorie
   Categorie *fin;      // Pointeur vers la dernière catégorie
   int nb_categories;
} FileCategories;

// Prototypes de fonctions
FileCategories *initialiser_file_categories();
int file_categories_vide(FileCategories *file_categories);
Categorie *creer_categorie(FileCategories *file_categories, char *nom_categorie);
void ajouter_categorie(FileCategories *file_categories, Categorie *categorie);
Categorie *chercher_categorie(FileCategories *file_categories, char *nom_categorie);
Categorie *obtenir_categorie(FileCategories *file_categories, char *nom_categorie);
void trouver_ordre_categorie(FileCategories *file_categories, Categorie *categorie);
void inserer_categorie(FileCategories *file_categories, Categorie *categorie, Categorie *precedent, Categorie *pointeur);
void liberer_file_categories(FileCategories *file_categories);

#endif
