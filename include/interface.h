#ifndef INTERFACE_H
#define INTERFACE_H

#include "util.h"
#include "categories.h"
#include "parse.h"

#include <string.h>
#include <stdio.h>

void afficher_prompt();
char *entrer_mot_cle();
void chercher_entree(char *entree, FileCategories *file_categories);
void afficher_recettes_categorie(Categorie *categorie);
int verifier_recette(char *entree, char *nom_recette);
int continuer();
void lancer_interface(const char *fichier_entree);

#endif
