#include "util.h"

/**
 * Fonction: 'fichier_existe'
 * Vérifie que le nom de fichier entré par l'utilisateur est valide.
 *
 * @param nom_fichier
 * @return
 */

int fichier_existe(char *nom_fichier) {
   FILE *fichier = fopen(nom_fichier, "r");
   // Vérifier que le fichier d'entrée existe
   if (fichier != NULL) {
      fclose(fichier);
      return 1;
   }
   return 0;
}

/**
 * Fonction: 'est_invalide'
 * Retourne un code d'erreur spécifique si l'entrée est invalide.
 *
 * @param nb_arguments
 * @param arguments
 * @return
 */

int est_invalide(int nb_arguments, char **arguments, char **fichier_stats, int *avec_stats) {
   if (nb_arguments < 2) {
      // Retourner une erreur si le fichier d'entrée n'est pas inclus
      return ERREUR_ARGUMENTS_MANQUANTS;
   } else if (nb_arguments > 2) {
      if (nb_arguments > 4) {
         // Retourner une erreur si trop d'arguments sont entrés
         return ERREUR_ARGUMENTS_INVALIDES;
      } else {
         if (strcmp(arguments[2], "-S") != 0) {
            // Retourner une erreur si le premier argument n'est pas '-S'
            return ERREUR_OPTION_INVALIDE;
         } else if (strcmp(arguments[2], "-S") == 0 && nb_arguments == 3) {
            // Retourner une erreur si le fichier de sortie n'est pas spécifié après "-S"
            return ERREUR_FICHIER_MANQUANT;
         }
      }
   }
   if (!fichier_existe(arguments[1])) {
      // Retourner une erreur si le fichier d'entrée est introuvable
      return ERREUR_FICHIER_INTROUVABLE;
   }
   if (nb_arguments == 4) {
      *fichier_stats = arguments[3];
      *avec_stats = 1;
   }
   return VALIDE;
}

/**
 * Fonction: 'imprimer_erreur'
 * Imprime le message associé au code d'erreur obtenu.
 *
 * @param code_erreur
 */

void imprimer_erreur(int code_erreur) {
   switch (code_erreur) {
      case ERREUR_ARGUMENTS_MANQUANTS:
         fprintf(stderr,
                 "Erreur: Veuillez au minimum inclure un fichier d'entrée."
                 "\n(ex: ./recherche liste.txt)"
                 "\n"
         );
         break;
      case ERREUR_ARGUMENTS_INVALIDES:
         fprintf(stderr,
                "Erreur:"
                "\n- Pour simplement exécuter ce logiciel, veuillez entrer \"./recherche (fichierdentree.txt)\" sur la console."
                "\n- Pour écrire les statistiques des données du fichier d'entrée, veuillez entrer \"/.recherche (fichierdentree.txt) -S (fichierdesortie.txt)\""
                "\n"
         );
         break;
      case ERREUR_OPTION_INVALIDE:
         fprintf(stderr, "Erreur: Argument optionnel invalide.\n");
         break;
      case ERREUR_FICHIER_MANQUANT:
         fprintf(stderr, "Erreur: Veuillez entrer un fichier de sortie.\n");
         break;
      case ERREUR_FICHIER_INTROUVABLE:
         fprintf(stderr, "Erreur: Le fichier d'entrée est introuvable.\n");
         break;
   }
}

/**
 * Fonction: 'rogner_str'
 * Enlève les espaces au début et à la fin d'une chaîne de caractères
 *
 * @param str
 * @return
 */

char *rogner_str(char *str) {
   // Espace en début de chaîne
   while (isspace(*str)) str++;

   // Espace en fin de chaîne
   char *fin_str = str + strlen(str) - 1;
   while (fin_str > str && isspace(*fin_str)) fin_str--;
   fin_str[1] = '\0';

   return str;
}