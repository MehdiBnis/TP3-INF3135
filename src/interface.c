#include "interface.h"

/**
 * Fonction: 'afficher_prompt'
 * Demande à l'utilisateur d'entrer un critère de recherche.
 */

void afficher_prompt() {
   printf("Entrez votre critère de recherche : ");
}

/**
 * Fonction: 'entrer_mot_cle'
 * Récupère l'entrée de l'utilisateur.
 *
 * @return
 */

char *entrer_mot_cle() {
   char *entree = malloc(121 * sizeof(char));
   fgets(entree, 121, stdin);
   rogner_str(entree);
   for (size_t i = 0; i < strlen(entree); i++) {
      entree[i] = tolower(entree[i]);
   }
   return entree;
}

/**
 * Fonction: 'chercher_mot'
 * Cherche le mot clé entré par l'utilisateur dans la file de catégories.
 *
 * @param entree
 * @param file_categories
 */

void chercher_entree(char *entree, FileCategories *file_categories) {
   Categorie *categorie = chercher_categorie(file_categories, entree);
   if (categorie) {
      afficher_recettes_categorie(categorie);
      return;
   } else {
      categorie = file_categories->debut;
      while (categorie) {
         Recette *recette = categorie->file_recettes->debut;
         while (recette) {
            if (verifier_recette(entree, recette->contenu)) {
               printf("%s\n", recette->contenu);
               return;
            }
            recette = recette->suivant;
         }
         categorie = categorie->suivant;
      }
      printf("Aucun résultat trouvé.\n");
   }
}

/**
 * Fonction: 'afficher_recettes_categorie'
 * Affiche toutes les recettes d'une catégorie.
 *
 * @param categorie
 */

void afficher_recettes_categorie(Categorie *categorie) {
   Recette *recette = categorie->file_recettes->debut;

   while (recette) {
      printf("%s\n", recette->contenu);
      recette = recette->suivant;
   }
}

/**
 * Fonction: 'verifier_recette'
 * Vérifie que la valeur entrée correspond à un boût de recettes.
 *
 * @param entree
 * @param nom_recette
 * @return
 */

int verifier_recette(char *entree, char *nom_recette) {
   char temp_entree[120];
   char temp_recette[120];

   strncpy(temp_recette, nom_recette, strlen(entree));
   strcpy(temp_entree, entree);

   for (size_t i = 0; i < strlen(entree) ; i++) {
      temp_recette[i] = tolower(temp_recette[i]);
      temp_entree[i] = tolower(temp_entree[i]);
   }

   if (strcmp(temp_entree, temp_recette) == 0) return 1;

   return 0;
}


/**
 * Fonction: 'continuer'
 * Demande à l'utilisateur s'il souhaite continuer.
 *
 * @return
 */

int continuer() {
   char reponse[10];

   do {
      printf("Voulez-vous continuer ? (Y/N) : ");
      fgets(reponse, sizeof(reponse), stdin);
   } while (reponse[0] != 'y' && reponse[0] != 'Y' && reponse[0] != 'n' && reponse[0] != 'N');
   return (reponse[0] == 'y' || reponse[0] == 'Y');
}

/**
 * Fonction: 'lancer_interface'
 * Exécute l'interface utilisateur;
 *
 * @param fichier_entree
 */

void lancer_interface(const char *fichier_entree) {
   FileCategories *file_categories = initialiser_file_categories();
   charger_donnees(fichier_entree, file_categories);

   do {
      afficher_prompt();
      char *entree = entrer_mot_cle();
      chercher_entree(entree, file_categories);
      free(entree);
   } while (continuer());

   liberer_file_categories(file_categories);
}