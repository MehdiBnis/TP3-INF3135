#include "test_recettes.h"

void test_initialiser_file_recettes() {
   FileRecettes *fr = initialiser_file_recettes();
   CU_ASSERT_PTR_NOT_NULL(fr);
   CU_ASSERT_PTR_NULL(fr->debut);
   CU_ASSERT_PTR_NULL(fr->fin);
   CU_ASSERT_EQUAL(fr->nb_recettes, 0);
   liberer_file_recettes(fr);
}

void test_file_recettes_vide() {
   FileRecettes *fr = initialiser_file_recettes();
   CU_ASSERT_TRUE(file_recettes_vide(fr));
   liberer_file_recettes(fr);
}

void test_creer_et_ajouter_recette() {
   FileRecettes *fr = initialiser_file_recettes();
   creer_recette(fr, "Fruits");
   CU_ASSERT_EQUAL(fr->nb_recettes, 1);
   CU_ASSERT_STRING_EQUAL(fr->debut->contenu, "Fruits");
   liberer_file_recettes(fr);
}

void test_chercher_recette() {
   FileRecettes *fr = initialiser_file_recettes();
   creer_recette(fr, "Legumes");
   Recette *rec = chercher_recette(fr, "Legumes");
   CU_ASSERT_PTR_NOT_NULL(rec);
   CU_ASSERT_STRING_EQUAL(rec->contenu, "Legumes");
   liberer_file_recettes(fr);
}

int test_recettes() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour recettes.c", NULL, NULL);

   CU_add_test(suite, "Test de 'initialiser_file_recettes'", test_initialiser_file_recettes);
   CU_add_test(suite, "Test de 'file_recettes_vide'", test_file_recettes_vide);
   CU_add_test(suite, "Test de 'creer_recette' et 'ajouter_recette", test_creer_et_ajouter_recette);
   CU_add_test(suite, "Test de 'chercher_recette'", test_chercher_recette);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
