#include "test_statistiques.h"

int test_statistiques() {
   CU_initialize_registry();
//   CU_pSuite suite = CU_add_suite("Suite de tests pour statistiques.c", NULL, NULL);

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
