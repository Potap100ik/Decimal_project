#include "../h_decimal.h"
#include "../h_decimal_bit_logic.h"
#include "../h_decimal_internal.h"
#include "test_suite.h"
/*
TODO:
- проверка получения знака/степени из числа, которое устанавливается
конвертацией из int, float
*/

int digits_ulong(unsigned long int n);

// get_exp()

START_TEST(test_get_exp_0) {
  int exp = 0;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  x.bits[DECIMAL_EXP_SIGN_INDEX] = exp << DECIMAL_EXP_INDEX_START;
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST
START_TEST(test_get_exp_mid_val1) {
  int exp = 1;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  x.bits[DECIMAL_EXP_SIGN_INDEX] = exp << DECIMAL_EXP_INDEX_START;
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST
START_TEST(test_get_exp_mid_val28) {
  int exp = 28;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  x.bits[DECIMAL_EXP_SIGN_INDEX] = exp << DECIMAL_EXP_INDEX_START;
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST

// искусственно можно установить и получить любое значение в пределах 2^(23-16)
START_TEST(test_get_exp_max) {
  int exp = (2 << 7) - 1;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  x.bits[DECIMAL_EXP_SIGN_INDEX] = exp << DECIMAL_EXP_INDEX_START;
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST

// искусственно можно установить и получить любое значение в пределах 2^(23-16 +
// 1)
START_TEST(test_get_exp_err) {
  int exp = 2 << 7;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  x.bits[DECIMAL_EXP_SIGN_INDEX] = exp << DECIMAL_EXP_INDEX_START;
  ck_assert_int_ne(exp, get_exp(&x));
}
END_TEST

// set_exp()

START_TEST(test_set_exp_min) {
  int exp = DECIMAL_EXP_MIN_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(0, set_exp(&x, exp));
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST
START_TEST(test_set_exp_mid_val_1) {
  int exp = (DECIMAL_EXP_MAX_VAL + DECIMAL_EXP_MIN_VAL) / 2;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(0, set_exp(&x, exp));
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST
START_TEST(test_set_exp_max) {
  int exp = DECIMAL_EXP_MAX_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(0, set_exp(&x, exp));
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST

// значение остается прежним, при попытке изменить его не запрещенное
START_TEST(test_set_exp_err_less_then_min) {
  int exp = 4;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(0, set_exp(&x, exp));

  int err_exp = DECIMAL_EXP_MIN_VAL - 1;
  ck_assert_int_ne(0, set_exp(&x, err_exp));
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST

START_TEST(test_set_exp_err_more_than_max) {
  int exp = 4;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(0, set_exp(&x, exp));

  int err_exp = DECIMAL_EXP_MAX_VAL + 1;
  ck_assert_int_ne(0, set_exp(&x, err_exp));
  ck_assert_int_eq(exp, get_exp(&x));
}
END_TEST

// get_sign

START_TEST(test_get_sign_minus) {
  int sign = DECIMAL_SIGN_MINUS_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};

  bit_set_1(&(x.bits[DECIMAL_EXP_SIGN_INDEX]), DECIMAL_SIGN_INDEX);

  ck_assert_int_eq(sign, get_sign(&x));
}
END_TEST

START_TEST(test_get_sign_plus) {
  int sign = DECIMAL_SIGN_PLUS_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  bit_set_0(&(x.bits[DECIMAL_EXP_SIGN_INDEX]), DECIMAL_SIGN_INDEX);

  ck_assert_int_eq(sign, get_sign(&x));
}
END_TEST

START_TEST(test_set_sign_minus) {
  int sign = DECIMAL_SIGN_MINUS_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};

  ck_assert_int_eq(0, set_sign(&x, sign));
  ck_assert_int_eq(sign, get_sign(&x));
}
END_TEST

START_TEST(test_set_sign_plus) {
  int sign = DECIMAL_SIGN_PLUS_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};

  ck_assert_int_eq(0, set_sign(&x, sign));
  ck_assert_int_eq(sign, get_sign(&x));
}
END_TEST

START_TEST(test_set_sign_err) {
  int sign = DECIMAL_SIGN_PLUS_VAL;
  h_decimal x = {.bits = {0, 0, 0, 0}};

  ck_assert_int_eq(0, set_sign(&x, sign));

  int err_sign = 325;
  ck_assert_int_ne(0, set_sign(&x, err_sign));

  ck_assert_int_eq(sign, get_sign(&x));
}
END_TEST

// // индекс самого старшего бита во всем числе
// unsigned int msb_index(const h_decimal *x);

START_TEST(test_msb_index_0) {
  int index = -1;
  h_decimal x = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_1) {
  int index = 0;
  h_decimal x;
  set_decimal_mantissa(&x, 0, 0, 1);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_2) {
  int index = UINT_BITS;
  h_decimal x;
  set_decimal_mantissa(&x, 0, 1, 1);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_3) {
  int index = UINT_BITS * 2;
  h_decimal x;
  set_decimal_mantissa(&x, 1, 1, 1);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_4) {
  int index = UINT_BITS - 1;
  h_decimal x;
  set_decimal_mantissa(&x, 0, 0, (unsigned int)-1);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_5) {
  int index = UINT_BITS * 2 - 1;
  h_decimal x;
  set_decimal_mantissa(&x, 0, (unsigned int)-1, 0);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_6) {
  int index = UINT_BITS * 3 - 1;
  h_decimal x;
  set_decimal_mantissa(&x, (unsigned int)-1, 0, 0);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_7) {
  unsigned int shift = 16;
  unsigned int value = 1 << shift;
  int index = UINT_BITS * 0 + shift;

  h_decimal x;
  set_decimal_mantissa(&x, 0, 0, value);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_8) {
  unsigned int shift = 16;
  unsigned int value = 1 << shift;
  int index = UINT_BITS * 1 + shift;

  h_decimal x;
  set_decimal_mantissa(&x, 0, value, 0);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

START_TEST(test_msb_index_9) {
  unsigned int shift = 16;
  unsigned int value = 1 << shift;
  int index = UINT_BITS * 2 + shift;

  h_decimal x;
  set_decimal_mantissa(&x, value, 0, 0);
  ck_assert_int_eq(index, msb_index(&x));
}
END_TEST

// // подсчет значащих десятичных цифр в числе
// unsigned int count_significant_digits(const h_decimal *x);

int digits_ulong(unsigned long int n) {
  int digits = 0;
  while (n != 0UL) {
    n /= 10UL;
    digits++;
  }
  return digits;
}

START_TEST(test_count_significant_digits_0) {
  unsigned int count = 0;

  h_decimal x;
  set_decimal_value(&x, 0, 0, 0, '+', 0);
  ck_assert_int_eq(count, count_significant_digits(&x));
}
END_TEST

START_TEST(test_count_significant_digits_1) {
  h_decimal x;
  for (unsigned int i = 0; i < UINT_BITS; ++i) {
    unsigned int value = 1u << i;
    unsigned int count = digits_ulong(value);
    set_decimal_value(&x, 0, 0, value, '+', 0);
    ck_assert_uint_eq(count, count_significant_digits(&x));
  }
}
END_TEST

START_TEST(test_count_significant_digits_2_0) {
  unsigned int shift = UINT_BITS;
  h_decimal x;
  for (unsigned int i = 0; i < (int)UINT_BITS; ++i) {
    unsigned long int value = 1UL << (i + shift);
    unsigned int count = digits_ulong(value);
    set_decimal_value(&x, 0, value >> shift, 0, '+', 0);
    ck_assert_uint_eq(count, count_significant_digits(&x));
  }
}
END_TEST

// проверка с отрицательными числами меньше нуля
START_TEST(test_count_significant_digits_2_1) {
  unsigned int shift = UINT_BITS;
  h_decimal x;
  for (unsigned int i = 0; i < (int)UINT_BITS; ++i) {
    unsigned long int value = 1UL << (i + shift);
    unsigned int count = digits_ulong(value);
    set_decimal_value(&x, 0, value >> shift, 0, '-', 28);
    ck_assert_uint_eq(count, count_significant_digits(&x));
  }
}
END_TEST

START_TEST(test_count_significant_digits_3) {
  unsigned int count = 29;
  h_decimal x;
  set_decimal_value(&x, -1, -1, -1, '+', 0);
  ck_assert_uint_eq(count, count_significant_digits(&x));
}
END_TEST

START_TEST(test_count_significant_digits_4) {
  unsigned int count = 4 + 1;
  unsigned int value = 10 * 10 * 10 * 10;
  h_decimal x;
  set_decimal_value(&x, 0, 0, value, '+', 0);
  ck_assert_uint_eq(count, count_significant_digits(&x));
}
END_TEST

Suite* suite_h_internal() {
  Suite* s = suite_create("h_internal");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_get_exp_0);
  tcase_add_test(tc_core, test_get_exp_mid_val1);
  tcase_add_test(tc_core, test_get_exp_mid_val28);
  tcase_add_test(tc_core, test_get_exp_max);
  tcase_add_test(tc_core, test_get_exp_err);
  tcase_add_test(tc_core, test_set_exp_min);
  tcase_add_test(tc_core, test_set_exp_mid_val_1);
  tcase_add_test(tc_core, test_set_exp_max);
  tcase_add_test(tc_core, test_set_exp_err_less_then_min);
  tcase_add_test(tc_core, test_set_exp_err_more_than_max);
  tcase_add_test(tc_core, test_get_sign_minus);
  tcase_add_test(tc_core, test_get_sign_plus);
  tcase_add_test(tc_core, test_set_sign_minus);
  tcase_add_test(tc_core, test_set_sign_plus);
  tcase_add_test(tc_core, test_set_sign_err);
  tcase_add_test(tc_core, test_msb_index_0);
  tcase_add_test(tc_core, test_msb_index_1);
  tcase_add_test(tc_core, test_msb_index_2);
  tcase_add_test(tc_core, test_msb_index_3);
  tcase_add_test(tc_core, test_msb_index_4);
  tcase_add_test(tc_core, test_msb_index_5);
  tcase_add_test(tc_core, test_msb_index_6);
  tcase_add_test(tc_core, test_msb_index_7);
  tcase_add_test(tc_core, test_msb_index_8);
  tcase_add_test(tc_core, test_msb_index_9);
  tcase_add_test(tc_core, test_count_significant_digits_0);
  tcase_add_test(tc_core, test_count_significant_digits_1);
  tcase_add_test(tc_core, test_count_significant_digits_2_0);
  tcase_add_test(tc_core, test_count_significant_digits_2_1);
  tcase_add_test(tc_core, test_count_significant_digits_3);
  tcase_add_test(tc_core, test_count_significant_digits_4);

  suite_add_tcase(s, tc_core);
  return s;
}
