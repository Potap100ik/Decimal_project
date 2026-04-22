#include "test_suite.h"

START_TEST(test_h_scale) { ck_assert_int_eq(1, 1); }
END_TEST

Suite* suite_h_scale() {
  Suite* s = suite_create("h_scale");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_scale);

  suite_add_tcase(s, tc_core);
  return s;
}
