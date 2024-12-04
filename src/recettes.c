#include "recettes.h"

/**
 * Fonction: 'initialiser_file_recettes'
 * Initialise les pointeurs de début et de fin d'une file de recettes.
 *
 * @return
 */

FileRecettes *initialiser_file_recettes() {
   // Allouer de l'espace pour une file de recettes
   FileRecettes *file_recettes;
   file_recettes = malloc(sizeof(FileRecettes));

   // Initialiser la valeur des pointeurs
   file_recettes->debut = NULL;
   file_recettes->fin = NULL;
   file_recettes->nb_recettes = 0;

   return file_recettes;
}

/**
 * Fonction: 'file_recettes_vide'
 * Vérifie si la file de recettes est vide.
 *
 * @param file_recettes  File de recettes
 * @return
 */

int file_recettes_vide(FileRecettes *file_recettes) {
   int est_vide = 0;

   // Vérifier s'il n'y a aucune catégorie dans la file de recettes
   if (!(file_recettes->debut && file_recettes->fin)) {
      est_vide = 1;
   }
   return est_vide;
}

/**
 * Fonction: 'creer_recette'
 * Initialise les valeurs d'une recette.
 *
 * @param nom_recette Nom de la recette
 * @return
 */

Recette *creer_recette(FileRecettes *file_recettes, char *nom_recette) {
   // Allouer de l'espace pour la recette
   Recette *recette;
   recette = malloc(sizeof(Recette));

   // Initialiser les valeurs de la recette
   recette->contenu = strdup(nom_recette);
   recette->precedent = NULL;
   recette->suivant = NULL;

   ajouter_recette(file_recettes, recette);
   file_recettes->nb_recettes++;

   return recette;
}

/**
 * Fonction: 'ajouter_recette'
 * Ajoute le pointeur d'une catégorie dans la file de recettes.
 *
 * @param file_recettes   File de recettes
 * @param recette         Recette d'une catégorie
 */

void ajouter_recette(FileRecettes *file_recettes, Recette *recette) {
   if (file_recettes_vide(file_recettes)) {
      // Initialiser les valeurs de la file de recettes si elle est vide
      file_recettes->debut = recette;
      file_recettes->fin = recette;
   } else {
      trouver_ordre_recette(file_recettes, recette);
   }
}

/**
 * Fonction: 'chercher_recette'
 * Cherche une catégorie dans une file de recettes.
 *
 * @param file_recettes     File de recettes
 * @param nom_recette       Nom de la recette
 * @return
 */

Recette *chercher_recette(FileRecettes *file_recettes, char *nom_recette) {
   Recette *pointeur;
   // Initialiser le pointeur au début de la file de recettes
   if (file_recettes->debut != NULL) {
      pointeur = file_recettes->debut;
   } else  {
      pointeur = NULL;
   }

   while (pointeur != NULL) {
      // Retourner le pointeur si le nom de la catégorie est trouvé
      if (pointeur->contenu && strcmp(pointeur->contenu, nom_recette) == 0) {
         return pointeur;
      }
      // Passer à la catégorie suivante
      pointeur = pointeur->suivant;
   }
   // Retourner NULL si la catégorie n'a pas été trouvé
   return NULL;
}

/**
 * Fonction: 'obtenir_recette'
 * Retourne une recette existante ou en crée une.
 *
 * @param file_recettes     File de recettes
 * @param nom_recette       Nom de la recette
 * @return
 */

Recette *obtenir_recette(FileRecettes *file_recettes, char *nom_recette) {
   Recette *recette = chercher_recette(file_recettes, nom_recette);

   if (recette == NULL) {
      recette = creer_recette(file_recettes, nom_recette);
   }

   return recette;
}

/**
 * Fonction: 'trouver_ordre_recette'
 * Retourne le pointeur d'une recette voisine pour en placer un nouvelle.
 *
 * @param file_recettes
 * @param recette
 * @return
 */

void trouver_ordre_recette(FileRecettes *file_recettes, Recette *recette) {
   // Initialiser le pointeur au début de la file
   Recette *pointeur = file_recettes->debut;
   Recette *precedent = NULL;

   // Avancer le pointeur tant qu'il n'est pas dans l'ordre alphabétique
   while (pointeur && strcmp(pointeur->contenu, recette->contenu) < 0) {
      precedent = pointeur;
      pointeur = pointeur->suivant;
   }
   inserer_recette(file_recettes, recette, precedent, pointeur);
}

/**
 * Fonction: 'inserer_recette'
 * Insère une recette dans une file de recettes.
 *
 * @param file_recettes
 * @param recette
 * @param position
 */

void inserer_recette(FileRecettes *file_recettes, Recette *recette, Recette *precedent, Recette *pointeur) {
   if (precedent == NULL) {
      recette->precedent = NULL;
      recette->suivant = file_recettes->debut;
      file_recettes->debut->precedent = recette;
      file_recettes->debut = recette;
   } else if (pointeur == NULL){
      recette->suivant = NULL;
      precedent->suivant = recette;
      recette->precedent = precedent;
      file_recettes->fin = recette;
   } else {
      precedent->suivant = recette;
      recette->precedent = precedent;
      recette->suivant = pointeur;
      pointeur->precedent = recette;
   }
}

/**
 * Fonction: 'liberer_file_recettes'
 * Libère la mémoire allouée à une file de recettes.
 *
 * @param file_recettes  File de recettes
 */

void liberer_file_recettes(FileRecettes *file_recettes) {
   // Initialiser le pointeur au début de la file de recettes
   Recette *pointeur = file_recettes->debut;
   int nb_recettes = file_recettes->nb_recettes;

   // Libérer l'espace alloué pour chaque catégorie de la file de recettes et leur nom
   while (nb_recettes > 0) {
      Recette *a_liberer = pointeur;
      pointeur = pointeur->suivant;
      free(a_liberer->contenu);
      free(a_liberer);
      nb_recettes--;
   }
   // Libérer l'espacer alloué pour la file de recettes
   free(file_recettes);
}