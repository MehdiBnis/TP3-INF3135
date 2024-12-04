#include "parse.h"

/**
 * Fonction: 'charger_donnees'
 * Charge les recettes et les catégories à partir du fichier d'entrée.
 *
 * @param nom_fichier
 * @param file_categories
 */

void charger_donnees(const char *nom_fichier, FileCategories *file_categories) {
   FILE *fichier = fopen(nom_fichier, "r");
   char ligne[121]; // Une ligne ne dépasse pas 120 caractères sans compter '\0'

   while (fgets(ligne, sizeof(ligne), fichier)) {
      traiter_ligne(ligne, file_categories);
   }
   fclose(fichier);
}

/**
 * Fonction: 'traiter_ligne'
 * Traite les données d'une ligne donnée.
 *
 * @param ligne
 * @param file_categories
 */

void traiter_ligne(char *ligne, FileCategories *file_categories) {
   char *debut_categories = strchr(ligne, '[');
   if (debut_categories) {
      *debut_categories = '\0';
      char *nom_recette = rogner_str(ligne);
      enregistrer_donnees(debut_categories, nom_recette, file_categories);
   }
}

/**
 * Fonction: 'enregistrer_donnees'
 * Enregistre les données dans les files et noeuds adaptés.
 *
 * @param debut_categories
 * @param nom_recette
 * @param file_categories
 */

void enregistrer_donnees(char *debut_categories, char *nom_recette, FileCategories *file_categories) {
   char *nom_categorie = strtok(debut_categories + 1, "[]\n");
   while (nom_categorie) {
      rogner_str(nom_categorie);
      Categorie *categorie = obtenir_categorie(file_categories, nom_categorie);
      obtenir_recette(categorie->file_recettes, nom_recette);
      nom_categorie = strtok(NULL, " []\n");
   }
}