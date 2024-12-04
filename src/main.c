#include "interface.h"

/**
 * Fonction main
 *
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char **argv) {
   char *fichier_stats = NULL;
   int avec_stats = 0;

   int erreur_entree = est_invalide(argc, argv, &fichier_stats, &avec_stats);

   if (erreur_entree) {
      imprimer_erreur(erreur_entree);
      return 1;
   }

   const char *fichier_entree = argv[1];
   lancer_interface(fichier_entree);

   return 0;
}