#include "test_categories.h"

void test_initialiser_file_categories() {
   FileCategories *fc = initialiser_file_categories();
   CU_ASSERT_PTR_NOT_NULL(fc);
   CU_ASSERT_PTR_NULL(fc->debut);
   CU_ASSERT_PTR_NULL(fc->fin);
   CU_ASSERT_EQUAL(fc->nb_categories, 0);
   liberer_file_categories(fc);
}

void test_file_categories_vide() {
   FileCategories *fc = initialiser_file_categories();
   CU_ASSERT_TRUE(file_categories_vide(fc));
   liberer_file_categories(fc);
}

void test_creer_et_ajouter_categorie() {
   FileCategories *fc = initialiser_file_categories();
   creer_categorie(fc, "Fruits");
   CU_ASSERT_EQUAL(fc->nb_categories, 1);
   CU_ASSERT_STRING_EQUAL(fc->debut->contenu, "Fruits");
   liberer_file_categories(fc);
}

void test_chercher_categorie() {
   FileCategories *fc = initialiser_file_categories();
   creer_categorie(fc, "Legumes");
   Categorie *cat = chercher_categorie(fc, "Legumes");
   CU_ASSERT_PTR_NOT_NULL(cat);
   CU_ASSERT_STRING_EQUAL(cat->contenu, "Legumes");
   liberer_file_categories(fc);
}

int test_categories() {
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite de tests pour categories.c", NULL, NULL);

   CU_add_test(suite, "Test de 'initialiser_file_categories'", test_initialiser_file_categories);
   CU_add_test(suite, "Test de 'file_categories_vide'", test_file_categories_vide);
   CU_add_test(suite, "Test de 'creer_categorie' et 'ajouter_categorie", test_creer_et_ajouter_categorie);
   CU_add_test(suite, "Test de 'chercher_categorie'", test_chercher_categorie);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

