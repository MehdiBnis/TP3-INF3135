#ifndef PARSE_H
#define PARSE_H

#include "recettes.h"
#include "categories.h"

void charger_donnees(const char *nom_fichier, FileCategories *file_categories);
void traiter_ligne(char *ligne, FileCategories *file_categories);
void enregistrer_donnees(char *debut_categories, char *nom_recette, FileCategories *file_categories);

#endif
