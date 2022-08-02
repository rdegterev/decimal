#include "check_decimal.h"

int main(void) {
  int problems_count = 0;
  Suite *main_suite;
  SRunner *runner;

  main_suite = suite_create("All_tests");
  suite_add_tcase(main_suite, decimal_utils_tests());
  suite_add_tcase(main_suite, decimal_arthm_tests());
  suite_add_tcase(main_suite, decimal_compr_tests());
  suite_add_tcase(main_suite, decimal_convrt_tests());
  suite_add_tcase(main_suite, decimal_other_tests());
  runner = srunner_create(main_suite);

  srunner_run_all(runner, CK_VERBOSE);
  problems_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (problems_count == 0) ? 0 : 1;
}
