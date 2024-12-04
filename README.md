# Recherche de recettes

Ce projet contient les fichiers source, les modules, les tests unitaires et un fichier Makefile nécessaires à l'assemblage d'un logiciel servant à effectuer des recherches dans une banque de recettes.

## Installation des modules nécessaires
```
apt-get update
apt install -y libcunit1 libcunit1-doc libcunit1-dev
apt install -y git build-essential pkg-config
```

## Importation du projet

Avant de commencer, veuillez importer ce projet sur votre branche locale:
```
cd votre_dossier
git clone https://gitlab.info.uqam.ca/bennis.mehdi/inf3135-hiver2024-tp3.git
```
## Assemblage et exécution du jeu

1. Assemblez l'exécutable `recherche` avec le fichier `Makefile`: exécutez simplement la commande `make` sur le terminal.
2. Lancez le jeu en entrant sur le terminal la commande suivi d'un fichier texte contenant la banque de recettes. Par exemple: 
```
./recherche liste.txt
```
3. *(Il est également possible de lancer le jeu avec l'option `-S` suivie d'un nom de fichier de sortie pour enregistrer les statistiques des données du fichier d'entrée. Par exemple:) 
```
./recherche liste.txt -S stats.txt
```
4. Pour supprimer les fichiers objets `.o` et l'exécutable `recherche`, entrez sur le terminal la commande `make clean`.

## Structure du projet

    inf3135-hiver2024-tp3
    │
    ├── include: fichiers d'entête
    │   ├── categories.h
    │   ├── interface.h
    │   ├── parse.h
    │   ├── recettes.h
    │   ├── statistiques.h
    │   └── util.h
    │
    ├── (obj): fichiers objets générés
    │
    ├── src: fichiers source C
    │   ├── categories.c: gère les catégories de recettes
    │   ├── interface.c: gère les interactions avec l'utilisateur
    │   ├── main.c: fonction main du projet
    │   ├── parse.c: gère les données du fichier d'entrée
    │   ├── recettes.c: charge les recettes à partir du fichier d'entrée
    │   ├── *(statistiques.c: écrit les statistiques des données du fichier d'entrée)
    │   └── util.c: fonctions générales à utiliser
    │
    ├── tests: fichiers tests CUnit
    │   ├── tests.c
    │   ├── test_categories.c
    │   ├── test_categories.h
    │   ├── test_recettes.c
    │   ├── test_recettes.h
    │   ├── *(test_statistiques.c)
    │   └── *(test_statistiques.h)
    │
    ├── Makefile
    ├── README.md
    ├── .gitignore
    └── .gitlab-ci.yml

## Tests

Pour faire tester le jeu à l'aide de CUnit, entrez la commande suivante: `make test`.

## Limitations du projet

Bien que l'interface utilisateur fonctionne correctement, le message d'erreur sera toujours le même, qu'il s'agisse d'une catégorie ou d'une recette introuvable.\
**Par manque de temps, je n'ai pas pu intégrer les fonctionnalités "statistiques" du projet, ni les tester.*