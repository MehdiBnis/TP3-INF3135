#include "categories.h"

/**
 * Fonction: 'initialiser_file_categories'
 * Initialise les pointeurs de début et de fin d'une file de catégories.
 *
 * @return
 */

FileCategories *initialiser_file_categories() {
   // Allouer de l'espace pour une file de catégories
   FileCategories *file_categories;
   file_categories = malloc(sizeof(FileCategories));

   // Initialiser la valeur des pointeurs
   file_categories->debut = NULL;
   file_categories->fin = NULL;
   file_categories->nb_categories = 0;

   return file_categories;
}

/**
 * Fonction: 'file_categories_vide'
 * Vérifie si la file de catégories est vide.
 *
 * @param file_categories  File de catégories
 * @return
 */

int file_categories_vide(FileCategories *file_categories) {
   int est_vide = 0;

   // Vérifier s'il n'y a aucune catégorie dans la file de catégories
   if (!(file_categories->debut && file_categories->fin)) {
      est_vide = 1;
   }
   return est_vide;
}

/**
 * Fonction: 'creer_categorie'
 * Initialise les valeurs d'une catégorie.
 *
 * @param file_categories   File de catégories
 * @param nom_categorie     Nom de la catégorie
 * @return
 */

Categorie *creer_categorie(FileCategories *file_categories, char *nom_categorie) {
   // Allouer de l'espace pour la catégorie
   Categorie *categorie;
   categorie = malloc(sizeof(Categorie));

   // Initialiser les valeurs de la catégorie
   categorie->contenu = strdup(nom_categorie);
   categorie->file_recettes = initialiser_file_recettes();
   categorie->precedent = NULL;
   categorie->suivant = NULL;

   ajouter_categorie(file_categories, categorie);
   file_categories->nb_categories++;

   return categorie;
}

/**
 * Fonction: 'ajouter_categorie'
 * Ajoute le pointeur d'une catégorie dans la file de catégories et retourne la catégorie.
 *
 * @param file_categories   File de catégories
 * @param categorie         Noeud d'une catégorie
 */

void ajouter_categorie(FileCategories *file_categories, Categorie *categorie) {
   if (file_categories_vide(file_categories)) {
      // Initialiser les valeurs de la file de catégories si elle est vide
      file_categories->debut = categorie;
      file_categories->fin = categorie;
   } else {
      trouver_ordre_categorie(file_categories, categorie);
   }
}

/**
 * Fonction: 'chercher_categorie'
 * Cherche une catégorie dans une file de catégories.
 *
 * @param file_categories   File de catégories
 * @param nom_categorie     Nom de la catégorie
 * @return
 */

Categorie *chercher_categorie(FileCategories *file_categories, char *nom_categorie) {
   if (file_categories == NULL || file_categories->debut == NULL) {
      return NULL;
   }

   // Initialiser le pointeur au début de la file de catégories
   Categorie *pointeur = file_categories->debut;

   while (pointeur) {
      // Retourner le pointeur si le nom de la catégorie est trouvé
      if (pointeur->contenu && strcmp(pointeur->contenu, nom_categorie) == 0) {
         return pointeur;
      }
      // Passer à la catégorie suivante
      pointeur = pointeur->suivant;
   }
   // Retourner NULL si la catégorie n'a pas été trouvé
   return NULL;
}

/**
 * Fonction: 'obtenir_categorie'
 * Retourne une catégorie existante ou en crée une.
 *
 * @param file_categories   File de catégories
 * @param nom_categorie     Nom de la catégorie
 * @return
 */

Categorie *obtenir_categorie(FileCategories *file_categories, char *nom_categorie) {
   Categorie *categorie = chercher_categorie(file_categories, nom_categorie);

   if (categorie == NULL) {
      categorie = creer_categorie(file_categories, nom_categorie);
   }

   return categorie;
}

/**
 * Fonction: 'trouver_ordre_categorie'
 * Retourne le pointeur d'une catégorie voisine pour en placer une nouvelle.
 *
 * @param file_categories
 * @param categorie
 * @return
 */

void trouver_ordre_categorie(FileCategories *file_categories, Categorie *categorie) {
   // Initialiser le pointeur au début de la file
   Categorie *pointeur = file_categories->debut;
   Categorie *precedent = NULL;

   // Avancer le pointeur tant qu'il n'est pas dans l'ordre alphabétique
   while (pointeur && strcmp(pointeur->contenu, categorie->contenu) < 0) {
      precedent = pointeur;
      pointeur = pointeur->suivant;
   }
   inserer_categorie(file_categories, categorie, precedent, pointeur);
}

/**
 * Fonction: 'inserer_categorie'
 * Insère une recette dans une file de catégories.
 *
 * @param file_categories
 * @param categorie
 * @param position
 */

void inserer_categorie(FileCategories *file_categories, Categorie *categorie, Categorie *precedent, Categorie *pointeur) {
   if (precedent == NULL) {
      categorie->precedent = NULL;
      categorie->suivant = file_categories->debut;
      file_categories->debut->precedent = categorie;
      file_categories->debut = categorie;
   } else if (pointeur == NULL){
      categorie->suivant = NULL;
      precedent->suivant = categorie;
      categorie->precedent = precedent;
      file_categories->fin = categorie;
   } else {
      precedent->suivant = categorie;
      categorie->precedent = precedent;
      categorie->suivant = pointeur;
      pointeur->precedent = categorie;
   }
}

/**
 * Fonction: 'liberer_file_categories'
 * Libère la mémoire allouée à une file de catégories et aux catégories qu'elle contient.
 *
 * @param file_categories  File de catégories
 */

void liberer_file_categories(FileCategories *file_categories) {
   // Initialiser le pointeur au début de la file de catégories
   Categorie *pointeur = file_categories->debut;
   int nb_categories = file_categories->nb_categories;

   // Libérer l'espace alloué pour chaque catégorie de la file de catégories et leur nom
   while (nb_categories > 0) {
      Categorie *a_liberer = pointeur;
      pointeur = pointeur->suivant;
      free(a_liberer->contenu);
      liberer_file_recettes(a_liberer->file_recettes);
      free(a_liberer);
      nb_categories--;
   }
   // Libérer l'espacer alloué pour la file de catégories
   free(file_categories);
}

