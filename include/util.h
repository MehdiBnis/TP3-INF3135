#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
   VALIDE                     = 0,
   ERREUR_ARGUMENTS_MANQUANTS = 1,
   ERREUR_ARGUMENTS_INVALIDES = 2,
   ERREUR_OPTION_INVALIDE	   = 3,
   ERREUR_FICHIER_MANQUANT	   = 4,
   ERREUR_FICHIER_INTROUVABLE	= 5
} Statut;

// Prototypes de fonctions
int fichier_existe(char *nom_fichier);
int est_invalide(int nb_arguments, char **arguments, char **fichier_stats, int *avec_stats);
void imprimer_erreur(int no_erreur);
char *rogner_str(char *str);

#endif
