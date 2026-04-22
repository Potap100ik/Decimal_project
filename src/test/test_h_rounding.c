#include "../h_decimal.h"
#include "../h_decimal_compare.h"
#include "../h_decimal_internal.h"
#include "../h_decimal_rounding.h"
#include "test_suite.h"

START_TEST(test_h_trunc_zero) {
  h_decimal x, y, trunc;

  set_decimal_empty(&trunc);

  set_decimal_value(&x, 0, 0, 0, 0, 0);
  set_decimal_value(&y, 0, 0, 0, 0, 0);

  ck_assert_int_eq(0, h_truncate(x, &trunc));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &trunc));
}
END_TEST

START_TEST(test_h_trunc_0) {
  h_decimal x, y, trunc;

  set_decimal_empty(&trunc);

  set_decimal_value(&x, 0, 0, 100, 1, 0);
  set_decimal_value(&y, 0, 0, 100, 1, 0);

  ck_assert_int_eq(0, h_truncate(x, &trunc));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &trunc));
}
END_TEST

START_TEST(test_h_trunc_1) {
  h_decimal x, y, trunc;

  set_decimal_empty(&trunc);

  set_decimal_value(&x, 0, 0, 25, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_truncate(x, &trunc));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &trunc));
}
END_TEST

START_TEST(test_h_trunc_2) {
  h_decimal x, y, trunc;

  set_decimal_empty(&trunc);

  set_decimal_value(&x, 0, 0, 20, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_truncate(x, &trunc));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &trunc));
}
END_TEST

START_TEST(test_h_trunc_3) {
  h_decimal x, y, trunc;

  set_decimal_empty(&trunc);

  set_decimal_value(&x, 0, 0, 29, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_truncate(x, &trunc));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &trunc));
}
END_TEST

//

START_TEST(test_h_floor_zero) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 0, 0, 0);
  set_decimal_value(&y, 0, 0, 0, 0, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_0) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 100, 1, 0);
  set_decimal_value(&y, 0, 0, 100, 1, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_1) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 25, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_2) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 20, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_3) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 29, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST
START_TEST(test_h_floor_4) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 25, 1, 1);
  set_decimal_value(&y, 0, 0, 3, 1, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST
START_TEST(test_h_floor_5) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 21, 1, 1);
  set_decimal_value(&y, 0, 0, 3, 1, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_6) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 20, 1, 1);
  set_decimal_value(&y, 0, 0, 2, 1, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

START_TEST(test_h_floor_7) {
  h_decimal x, y, floor;

  set_decimal_empty(&floor);

  set_decimal_value(&x, 0, 0, 29, 1, 1);
  set_decimal_value(&y, 0, 0, 3, 1, 0);

  ck_assert_int_eq(0, h_floor(x, &floor));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &floor));
}
END_TEST

//

START_TEST(test_h_round_zero) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 0, 0, 0);
  set_decimal_value(&y, 0, 0, 0, 0, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_0) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 100, 1, 0);
  set_decimal_value(&y, 0, 0, 100, 1, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_1) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 25, 0, 1);
  set_decimal_value(&y, 0, 0, 3, 0, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_2) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 20, 0, 1);
  set_decimal_value(&y, 0, 0, 2, 0, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_3) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 29, 0, 1);
  set_decimal_value(&y, 0, 0, 3, 0, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_4) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 25, 1, 1);
  set_decimal_value(&y, 0, 0, 3, 1, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_5) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 21, 1, 1);
  set_decimal_value(&y, 0, 0, 2, 1, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_round_6) {
  h_decimal x, y, round;

  set_decimal_empty(&round);

  set_decimal_value(&x, 0, 0, 29, 1, 1);
  set_decimal_value(&y, 0, 0, 3, 1, 0);

  ck_assert_int_eq(0, h_round(x, &round));
  ck_assert_int_eq(1, is_equal_mantissa(&y, &round));
}
END_TEST

START_TEST(test_h_floor_case_1) {
  h_decimal value = {.bits = {1, 2, 3, 917504}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_floor(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(553402, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_floor_case_2) {
  h_decimal value = {.bits = {1, 2, 3, -2146566144}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_floor(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(553403, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(INT_MIN, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_floor_case_3) {
  h_decimal value = {.bits = {33, 2, 3000, -2146107392}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_floor(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(56, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(INT_MIN, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_round_case_1) {
  h_decimal value = {.bits = {1, 2, 3, 917504}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_round(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(553402, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_round_case_2) {
  h_decimal value = {.bits = {10, 100, 3, 1376256}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_round(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(0, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_round_case_3) {
  h_decimal value = {.bits = {16, 100, 3, 851968}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_round(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(5534023, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_truncate_case_1) {
  h_decimal value = {.bits = {32444, 100, 343253, -2145976320}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_truncate(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(63, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(INT_MIN, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_truncate_case_2) {
  h_decimal value = {.bits = {1, 1, 1, 917504}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_truncate(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(184467, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_truncate_case_3) {
  h_decimal value = {.bits = {0, 0, 0, 851968}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_truncate(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(0, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_int_eq(0, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_negate_case_1) {
  h_decimal value = {.bits = {32444, 100, 343253, -2145976320}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_negate(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(32444, (int)result.bits[0]);
  ck_assert_int_eq(100, (int)result.bits[1]);
  ck_assert_int_eq(343253, (int)result.bits[2]);
  ck_assert_int_eq(1507328, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_negate_case_2) {
  h_decimal value = {.bits = {1, 1, 1, 917504}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_negate(value, &result);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1, (int)result.bits[0]);
  ck_assert_int_eq(1, (int)result.bits[1]);
  ck_assert_int_eq(1, (int)result.bits[2]);
  ck_assert_int_eq(-2146566144, (int)result.bits[3]);
}
END_TEST

START_TEST(test_h_negate_case_3) {
  h_decimal value = {.bits = {0, 0, 0, 917504}};
  h_decimal result = {{0, 0, 0, 0}};
  int code = h_negate(value, &result);
  int bits3 = (int)result.bits[3];

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(0, (int)result.bits[0]);
  ck_assert_int_eq(0, (int)result.bits[1]);
  ck_assert_int_eq(0, (int)result.bits[2]);
  ck_assert_msg(
      bits3 == -2146566144 || result.bits[3] == 0 || result.bits[3] == 917504,
      "unexpected bits[3]=%u", result.bits[3]);
}
END_TEST

START_TEST(test_h_bank_dec_0) {
  h_decimal value = {.bits = {126, 0, 0, 0}};
  int code = bank_decision(&value, 7);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(127, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bank_dec_1) {
  h_decimal value = {.bits = {126, 0, 0, 0}};
  int code = bank_decision(&value, 5);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(126, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bank_dec_2) {
  h_decimal value = {.bits = {127, 0, 0, 0}};
  int code = bank_decision(&value, 5);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(128, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_norm_0) {
  h_decimal value = {.bits = {123000, 0, 0, 0}};
  set_exp(&value, 3);
  int code = normalize(&value, &value);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(123, (int)value.bits[0]);
  ck_assert_int_eq(0, get_exp(&value));
}
END_TEST

START_TEST(test_h_norm_1) {
  h_decimal value = {.bits = {123000, 0, 0, 0}};
  set_exp(&value, 6);
  int code = normalize(&value, &value);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(123, (int)value.bits[0]);
  ck_assert_int_eq(3, get_exp(&value));
}
END_TEST

START_TEST(test_h_round_to_0) {
  h_decimal value;
  int scale_to = 5;

  set_decimal_value(&value, 0, 0, 1234567890, '+', 0);
  int code = round_decimal_to(&value, scale_to, &value, truncate_decision);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1234500000, (int)value.bits[0]);
}
END_TEST

// BIG DECIMAL

START_TEST(test_h_bd_bank_dec_0) {
  big_decimal value;
  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 126, '+', 0);
  int code = bank_decision_bd(&value, 7);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(127, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_bank_dec_1) {
  big_decimal value;
  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 126, '+', 0);
  int code = bank_decision_bd(&value, 5);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(126, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_bank_dec_2) {
  big_decimal value;
  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 127, '+', 0);
  int code = bank_decision_bd(&value, 5);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(128, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_round_to_0) {
  big_decimal value;
  int scale_to = 5;

  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 1234567890, '+', 0);
  int code =
      round_decimal_to_bd(&value, scale_to, &value, truncate_decision_bd);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1234500000, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_round_to_1_1) {
  big_decimal value;
  int scale_to = 4;

  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 1234567890, '+', 0);
  int code = round_decimal_to_bd(&value, scale_to, &value, floor_decision_bd);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1234000000, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_round_to_1_2) {
  big_decimal value;
  int scale_to = 4;

  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 1234567890, '-', 0);
  int code = round_decimal_to_bd(&value, scale_to, &value, floor_decision_bd);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1235000000, (int)value.bits[0]);
}
END_TEST

START_TEST(test_h_bd_round_to_2) {
  big_decimal value;
  int scale_to = 4;

  set_decimal_value_bd(&value, 0, 0, 0, 0, 0, 1234567890, '+', 0);
  int code = round_decimal_to_bd(&value, scale_to, &value, round_decision_bd);

  ck_assert_int_eq(0, code);
  ck_assert_int_eq(1235000000, (int)value.bits[0]);
}
END_TEST

Suite* suite_h_rounding() {
  Suite* s = suite_create("h_rounding");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_trunc_zero);
  tcase_add_test(tc_core, test_h_trunc_0);
  tcase_add_test(tc_core, test_h_trunc_1);
  tcase_add_test(tc_core, test_h_trunc_2);
  tcase_add_test(tc_core, test_h_trunc_3);
  tcase_add_test(tc_core, test_h_floor_zero);
  tcase_add_test(tc_core, test_h_floor_0);
  tcase_add_test(tc_core, test_h_floor_1);
  tcase_add_test(tc_core, test_h_floor_2);
  tcase_add_test(tc_core, test_h_floor_3);
  tcase_add_test(tc_core, test_h_floor_4);
  tcase_add_test(tc_core, test_h_floor_5);
  tcase_add_test(tc_core, test_h_floor_6);
  tcase_add_test(tc_core, test_h_floor_7);
  tcase_add_test(tc_core, test_h_round_zero);
  tcase_add_test(tc_core, test_h_round_0);
  tcase_add_test(tc_core, test_h_round_1);
  tcase_add_test(tc_core, test_h_round_2);
  tcase_add_test(tc_core, test_h_round_3);
  tcase_add_test(tc_core, test_h_round_4);
  tcase_add_test(tc_core, test_h_round_5);
  tcase_add_test(tc_core, test_h_round_6);
  tcase_add_test(tc_core, test_h_floor_case_1);
  tcase_add_test(tc_core, test_h_floor_case_2);
  tcase_add_test(tc_core, test_h_floor_case_3);
  tcase_add_test(tc_core, test_h_round_case_1);
  tcase_add_test(tc_core, test_h_round_case_2);
  tcase_add_test(tc_core, test_h_round_case_3);
  tcase_add_test(tc_core, test_h_truncate_case_1);
  tcase_add_test(tc_core, test_h_truncate_case_2);
  tcase_add_test(tc_core, test_h_truncate_case_3);
  tcase_add_test(tc_core, test_h_negate_case_1);
  tcase_add_test(tc_core, test_h_negate_case_2);
  tcase_add_test(tc_core, test_h_negate_case_3);
  tcase_add_test(tc_core, test_h_bank_dec_0);
  tcase_add_test(tc_core, test_h_bank_dec_1);
  tcase_add_test(tc_core, test_h_bank_dec_2);
  tcase_add_test(tc_core, test_h_norm_0);
  tcase_add_test(tc_core, test_h_norm_1);
  tcase_add_test(tc_core, test_h_round_to_0);

  tcase_add_test(tc_core, test_h_bd_bank_dec_0);
  tcase_add_test(tc_core, test_h_bd_bank_dec_1);
  tcase_add_test(tc_core, test_h_bd_bank_dec_2);
  tcase_add_test(tc_core, test_h_bd_round_to_0);
  tcase_add_test(tc_core, test_h_bd_round_to_1_1);
  tcase_add_test(tc_core, test_h_bd_round_to_1_2);
  tcase_add_test(tc_core, test_h_bd_round_to_2);

  suite_add_tcase(s, tc_core);
  return s;
}
