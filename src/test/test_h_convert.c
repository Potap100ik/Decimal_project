#include "../h_decimal_compare.h"
#include "../h_decimal_convert.h"
#include "../h_decimal_internal.h"
#include "test_suite.h"

START_TEST(test_h_from_int_to_decimal_zero) {
  int src = 0;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 0, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_int_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_int_to_decimal_neg) {
  int src = -12345;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 12345, DECIMAL_SIGN_MINUS_VAL, 0);

  ck_assert_int_eq(0, h_from_int_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_zero) {
  float src = 0.0f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 0, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_rounding_1) {
  float src = -123.45671234567f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1234567, DECIMAL_SIGN_MINUS_VAL,
                    4);  // 123.4567, exp = 4

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_rounding_2_0) {
  float src = 1234566590.0f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1234566000, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_rounding_2_2) {
  float src = 1234567890.0f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1234568000, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_rounding_2_1) {
  float src = 1234567890.0f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1234568000, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_0) {
  float src = 23e-30f;
  h_decimal dst;
  set_decimal_empty(&dst);

  ck_assert_int_eq(ERR_CONVERT, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_empty(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_1) {
  float src = 1e-28f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1, DECIMAL_SIGN_PLUS_VAL, 28);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_2) {
  float src = 10e-29f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1, DECIMAL_SIGN_PLUS_VAL, 28);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_3) {
  float src = 12e-29f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 1, DECIMAL_SIGN_PLUS_VAL, 28);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_4) {
  float src = 16e-29f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 2, DECIMAL_SIGN_PLUS_VAL, 28);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_small_e28_5) {
  float src = 16e-29f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 2, DECIMAL_SIGN_PLUS_VAL, 28);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_float_to_decimal_pos) {
  float src = 123.0f;
  h_decimal dst, expected;
  set_decimal_empty(&dst);
  set_decimal_value(&expected, 0, 0, 123, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_float_to_decimal(src, &dst));
  ck_assert_int_eq(1, is_equal_mantissa(&expected, &dst));
  ck_assert_int_eq(get_sign(&expected), get_sign(&dst));
  ck_assert_int_eq(get_exp(&expected), get_exp(&dst));
}
END_TEST

START_TEST(test_h_from_decimal_to_int_zero) {
  h_decimal src;
  int dst = 1;
  set_decimal_value(&src, 0, 0, 0, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_decimal_to_int(src, &dst));
  ck_assert_int_eq(0, dst);
}
END_TEST

START_TEST(test_h_from_decimal_to_int_neg) {
  h_decimal src;
  int dst = 0;
  set_decimal_value(&src, 0, 0, 42, DECIMAL_SIGN_MINUS_VAL, 0);

  ck_assert_int_eq(0, h_from_decimal_to_int(src, &dst));
  ck_assert_int_eq(-42, dst);
}
END_TEST

START_TEST(test_h_from_decimal_to_float_zero) {
  h_decimal src;
  float dst = 1.0f;
  set_decimal_value(&src, 0, 0, 0, DECIMAL_SIGN_PLUS_VAL, 0);

  ck_assert_int_eq(0, h_from_decimal_to_float(src, &dst));
  ck_assert_int_eq(0, (int)dst);
}
END_TEST

START_TEST(test_h_from_decimal_to_float_neg) {
  h_decimal src;
  float dst = 0.0f;
  set_decimal_value(&src, 0, 0, 321, DECIMAL_SIGN_MINUS_VAL, 0);

  ck_assert_int_eq(0, h_from_decimal_to_float(src, &dst));
  ck_assert_int_eq(-321, (int)dst);
}
END_TEST

START_TEST(test_h_from_decimal_to_float_scale_0) {
  h_decimal src;
  float expected = -1234568000.0f, dst;
  set_decimal_value(&src, 0, 0, 1234567890, DECIMAL_SIGN_MINUS_VAL, 0);

  ck_assert_int_eq(0, h_from_decimal_to_float(src, &dst));
  ck_assert_float_eq(expected, dst);
}
END_TEST

START_TEST(test_h_from_decimal_to_float_scale_1) {
  h_decimal src;
  float expected = -0.1234568f, dst;
  set_decimal_value(&src, 0, 0, 1234567890, DECIMAL_SIGN_MINUS_VAL, 10);

  ck_assert_int_eq(0, h_from_decimal_to_float(src, &dst));
  ck_assert_float_eq(expected, dst);
}
END_TEST

Suite* suite_h_convert() {
  Suite* s = suite_create("h_convert");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_from_int_to_decimal_zero);
  tcase_add_test(tc_core, test_h_from_int_to_decimal_neg);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_zero);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_pos);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_rounding_1);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_rounding_2_0);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_rounding_2_1);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_rounding_2_2);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_0);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_1);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_2);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_3);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_4);
  tcase_add_test(tc_core, test_h_from_float_to_decimal_small_e28_5);
  tcase_add_test(tc_core, test_h_from_decimal_to_float_scale_0);
  tcase_add_test(tc_core, test_h_from_decimal_to_float_scale_1);

  tcase_add_test(tc_core, test_h_from_decimal_to_int_zero);
  tcase_add_test(tc_core, test_h_from_decimal_to_int_neg);
  tcase_add_test(tc_core, test_h_from_decimal_to_float_zero);
  tcase_add_test(tc_core, test_h_from_decimal_to_float_neg);

  suite_add_tcase(s, tc_core);
  return s;
}
