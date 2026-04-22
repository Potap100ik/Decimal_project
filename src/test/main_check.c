#include "test_suite.h"

int main() {
  SRunner* sr = srunner_create(NULL);

  srunner_add_suite(sr, suite_h_arithmetic());
  srunner_add_suite(sr, suite_h_bit_logic());
  srunner_add_suite(sr, suite_h_compare());
  srunner_add_suite(sr, suite_h_convert());
  srunner_add_suite(sr, suite_h_internal());
  srunner_add_suite(sr, suite_h_rounding());
  srunner_add_suite(sr, suite_h_scale());

  srunner_run_all(sr, CK_NORMAL);  // CK_VERBOSE CK_NORMAL
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? 0 : 1;
}
