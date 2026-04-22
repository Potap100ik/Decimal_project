#include "../h_decimal.h"
#include "../h_decimal_compare.h"
#include "../h_decimal_internal.h"
#include "test_suite.h"

// // проверка на равенство всех параметров числа decimal нулю (mantissa, sign,
// exp) int is_empty(h_decimal *x);

START_TEST(test_h_is_empty_0) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 0, 0);

  ck_assert_int_eq(1, is_empty(&x));
}
END_TEST

START_TEST(test_h_is_empty_1) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 1, 0, 0, 0, 0);

  ck_assert_int_ne(1, is_empty(&x));
}
END_TEST

START_TEST(test_h_is_empty_2) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 1, 0, 0, 0);

  ck_assert_int_ne(1, is_empty(&x));
}
END_TEST

START_TEST(test_h_is_empty_3) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 1, 0, 0);

  ck_assert_int_ne(1, is_empty(&x));
}
END_TEST

START_TEST(test_h_is_empty_4) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 1, 0);

  ck_assert_int_ne(1, is_empty(&x));
}
END_TEST

START_TEST(test_h_is_empty_5) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 0, 1);

  ck_assert_int_ne(1, is_empty(&x));
}
END_TEST

// // мантисса равна нулю
// int is_equal_zero(const h_decimal *x);

START_TEST(test_h_is_equal_zero_0) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 0, 0);

  ck_assert_int_eq(1, is_equal_zero(&x));
}
END_TEST

START_TEST(test_h_is_equal_zero_1) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 0, 1);

  ck_assert_int_eq(1, is_equal_zero(&x));
}
END_TEST

START_TEST(test_h_is_equal_zero_2) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 0, 1, 0);

  ck_assert_int_eq(1, is_equal_zero(&x));
}
END_TEST

START_TEST(test_h_is_equal_zero_3) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 1, 0, 0, 0, 0);

  ck_assert_int_ne(1, is_equal_zero(&x));
}
END_TEST

START_TEST(test_h_is_equal_zero_4) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 1, 0, 0, 0);

  ck_assert_int_ne(1, is_equal_zero(&x));
}
END_TEST

START_TEST(test_h_is_equal_zero_5) {
  h_decimal x;
  set_decimal_empty(&x);
  set_decimal_value(&x, 0, 0, 1, 0, 0);

  ck_assert_int_ne(1, is_equal_zero(&x));
}
END_TEST

// // равенство мантисс
// int is_equal_mantissa(const h_decimal *a, const h_decimal *b);

START_TEST(test_h_is_equal_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 0, 0, 0);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

START_TEST(test_h_is_equal_1) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, val, 0, 0);
  set_decimal_value(&b, 0, 0, val, 0, 0);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

START_TEST(test_h_is_equal_2) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, 0, 0);
  set_decimal_value(&b, 0, val, 0, 0, 0);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

START_TEST(test_h_is_equal_3) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val, 0, 0, 0, 0);
  set_decimal_value(&b, val, 0, 0, 0, 0);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

START_TEST(test_h_is_equal_4) {
  h_decimal a, b;
  unsigned int val = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, val, 0);
  set_decimal_value(&b, 0, val, 0, 0, val);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

START_TEST(test_h_is_equal_5) {
  h_decimal a, b;
  unsigned int val = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, 0, val);
  set_decimal_value(&b, 0, val, 0, val, 0);

  ck_assert_int_eq(1, is_equal_mantissa(&a, &b));
}
END_TEST

// // сравнение мантисс a > b
// int is_more_mantissa(const h_decimal *a, const h_decimal *b);

START_TEST(test_h_is_more_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 0, 0, 0);

  ck_assert_int_ne(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '+', 0);
  set_decimal_value(&b, 0, 0, 0, '-', 0);

  ck_assert_int_ne(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_2) {
  h_decimal a, b;
  unsigned int val = 6;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, val, 0, 0);
  set_decimal_value(&b, 0, val, val, 0, 0);

  ck_assert_int_ne(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_3) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, 0, 0);
  set_decimal_value(&b, val_less, 0, 0, 0, 0);

  ck_assert_int_eq(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_4) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, '-', 0);
  set_decimal_value(&b, val_less, 0, 0, '+', 0);

  ck_assert_int_eq(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_5) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 1, 1, 0, 0);

  ck_assert_int_eq(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_6) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, '-', 0);
  set_decimal_value(&b, 0, 1, 1, '+', 0);

  ck_assert_int_eq(1, is_more_mantissa(&a, &b));
  ck_assert_int_ne(1, is_more_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_more_7) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 1, 0, 0);

  ck_assert_int_ne(1, is_more_mantissa(&a, &b));
}
END_TEST

// // сравнение мантисс a < b
// int is_less_mantissa(const h_decimal *a, const h_decimal *b);

START_TEST(test_h_is_less_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 0, 0, 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_ne(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '+', 0);
  set_decimal_value(&b, 0, 0, 0, '-', 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_ne(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_2) {
  h_decimal a, b;
  unsigned int val = 6;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, val, 0, 0);
  set_decimal_value(&b, 0, val, val, 0, 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_ne(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_3) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, 0, 0);
  set_decimal_value(&b, val_less, 0, 0, 0, 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_eq(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_4) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, '-', 0);
  set_decimal_value(&b, val_less, 0, 0, '+', 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_eq(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_5) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 1, 1, 0, 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_eq(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_6) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, '-', 0);
  set_decimal_value(&b, 0, 1, 1, '+', 0);

  ck_assert_int_ne(1, is_less_mantissa(&a, &b));
  ck_assert_int_eq(1, is_less_mantissa(&b, &a));
}
END_TEST

START_TEST(test_h_is_less_7) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 1, 0, 0);

  ck_assert_int_eq(1, is_less_mantissa(&a, &b));
}
END_TEST

// // проверка равенства decimal a == b (с учетом знака, степени)
// int h_is_equal(h_decimal a,  h_decimal b);

START_TEST(test_h_is_equal_h_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 0, 0, 0);

  ck_assert_int_eq(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_1) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, val, 0, 0);
  set_decimal_value(&b, 0, 0, val, 0, 0);

  ck_assert_int_eq(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_2) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, 0, 0);
  set_decimal_value(&b, 0, val, 0, 0, 0);

  ck_assert_int_eq(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_3) {
  h_decimal a, b;
  unsigned int val = -1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val, 0, 0, 0, 0);
  set_decimal_value(&b, val, 0, 0, 0, 0);

  ck_assert_int_eq(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_4) {
  h_decimal a, b;
  unsigned int val = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, val, 0);
  set_decimal_value(&b, 0, val, 0, 0, val);

  ck_assert_int_ne(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_5) {
  h_decimal a, b;
  unsigned int val = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, 0, 0, val);
  set_decimal_value(&b, 0, val, 0, val, 0);

  ck_assert_int_ne(1, h_is_equal(a, b));
}
END_TEST

START_TEST(test_h_is_equal_h_6) {
  h_decimal a, b;
  unsigned int val = 100;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, val, 1, 0);
  set_decimal_value(&b, 0, 0, val * 100, 1, 2);

  ck_assert_int_eq(1, h_is_equal(a, b));
}
END_TEST

// // сравнение числа decimal a < b (с учетом знака, степени)
// int h_is_less(h_decimal a,  h_decimal b);

START_TEST(test_h_is_less_h_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 0, 0, 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_ne(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_1_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '+', 0);
  set_decimal_value(&b, 0, 0, 0, '-', 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_ne(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_1_2) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '+', 3);
  set_decimal_value(&b, 0, 0, 0, '-', 6);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_ne(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_2) {
  h_decimal a, b;
  unsigned int val = 6;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, val, val, 0, 0);
  set_decimal_value(&b, 0, val, val, 0, 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_ne(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_3) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, 0, 0);
  set_decimal_value(&b, val_less, 0, 0, 0, 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_eq(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_4) {
  h_decimal a, b;
  unsigned int val_more = (1u << 16) - 1;
  unsigned int val_less = 1;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, val_more, 0, 0, '+', 0);
  set_decimal_value(&b, val_less, 0, 0, '-', 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_eq(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_5) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 1, 1, 0, 0);

  ck_assert_int_ne(1, h_is_less(a, b));
  ck_assert_int_eq(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_6) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 1, 0, 0, '-', 0);
  set_decimal_value(&b, 0, 1, 1, '+', 0);

  ck_assert_int_eq(1, h_is_less(a, b));
  ck_assert_int_ne(1, h_is_less(b, a));
}
END_TEST

START_TEST(test_h_is_less_h_7) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, 0, 0);
  set_decimal_value(&b, 0, 0, 1, 0, 0);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_0) {
  h_decimal a, b;
  char sign_a = '+';
  char sign_b = '+';
  int exp_a = 0;
  int exp_b = 0;

  unsigned int val_a = 0;
  unsigned int val_b = 0;
  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_1) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_2) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_3) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 12345;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_4) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;  // 123.4
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_5) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;  // 1234.5
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_6) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12340;  // 1234.0
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_7) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;  // 1234.5
  unsigned int val_b = 12340;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_8) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;  // 123.4
  unsigned int val_b = 12345;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_9) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 1234;  // 123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_10) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;
  unsigned int val_b = 1234;  // 123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_11) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 12340;  // 1234.0

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_12) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 123;
  unsigned int val_b = 1234;  // 123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_1_13) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '+';
  char sign_b = '+';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 125;
  unsigned int val_b = 1234;  // 123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_0) {
  h_decimal a, b;
  char sign_a = '-';
  char sign_b = '-';
  int exp_a = 0;
  int exp_b = 0;

  unsigned int val_a = 0;
  unsigned int val_b = 0;
  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_1) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_2) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;  // -12345
  unsigned int val_b = 1234;   // -1234

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_3) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) = exp(b)
  int exp_a = 0;
  int exp_b = 0;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 12345;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_4) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;  // -123.4
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_5) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;  // -1234.5
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_6) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 1235;  // -123.5
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_7) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) > abs(b)
  unsigned int val_a = 12340;  // -1234.0
  unsigned int val_b = 1234;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_8) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) > exp(b)
  int exp_a = 1;
  int exp_b = 0;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;  // -123.4
  unsigned int val_b = 12345;

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_9) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) = abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 1234;  // -123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_10) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) > abs(b)
  unsigned int val_a = 12345;
  unsigned int val_b = 1234;  // -123.4

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_11) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 12340;  // -1234.0

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_12) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 1235;  // -123.5

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(1, h_is_less(a, b));
}
END_TEST

START_TEST(test_h_is_less_h_case_2_13) {
  h_decimal a, b;
  // sign(a) = sign(b) = '+'
  char sign_a = '-';
  char sign_b = '-';
  // exp(a) < exp(b)
  int exp_a = 0;
  int exp_b = 1;
  // abs(a) < abs(b)
  unsigned int val_a = 1234;
  unsigned int val_b = 12345;  // -1234.5

  set_decimal_value(&a, 0, 0, val_a, sign_a, exp_a);
  set_decimal_value(&b, 0, 0, val_b, sign_b, exp_b);

  ck_assert_int_eq(0, h_is_less(a, b));
}
END_TEST

// // сравнение числа decimal a <= b (с учетом знака, степени)
// int h_is_less_or_equal(h_decimal a,  h_decimal b);

START_TEST(test_h_is_less_or_equal_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 125, '+', 2);
  set_decimal_value(&b, 0, 0, 125, '+', 2);

  ck_assert_int_eq(1, h_is_less_or_equal(a, b));
}
END_TEST

START_TEST(test_h_is_less_or_equal_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 1, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(1, h_is_less_or_equal(a, b));
}
END_TEST

START_TEST(test_h_is_less_or_equal_2) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 5, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(0, h_is_less_or_equal(a, b));
}
END_TEST

// // сравнение числа decimal a > b (с учетом знака, степени)
// int h_is_greater(h_decimal a,  h_decimal b);

START_TEST(test_h_is_greater_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 5, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(1, h_is_greater(a, b));
}
END_TEST

START_TEST(test_h_is_greater_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 5, '+', 0);
  set_decimal_value(&b, 0, 0, 5, '+', 0);

  ck_assert_int_eq(0, h_is_greater(a, b));
}
END_TEST

START_TEST(test_h_is_greater_2) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 1, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(0, h_is_greater(a, b));
}
END_TEST

// // сравнение числа decimal a >= b (с учетом знака, степени)
// int h_is_greater_or_equal(h_decimal a,  h_decimal b);

START_TEST(test_h_is_greater_or_equal_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 5, '+', 0);
  set_decimal_value(&b, 0, 0, 5, '+', 0);

  ck_assert_int_eq(1, h_is_greater_or_equal(a, b));
}
END_TEST

START_TEST(test_h_is_greater_or_equal_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 5, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(1, h_is_greater_or_equal(a, b));
}
END_TEST

START_TEST(test_h_is_greater_or_equal_2) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 1, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(0, h_is_greater_or_equal(a, b));
}
END_TEST

// // прооверка неравенства decimal a != b (с учетом знака, степени)
// int h_is_not_equal(h_decimal a,  h_decimal b);

START_TEST(test_h_is_not_equal_0) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '+', 0);
  set_decimal_value(&b, 0, 0, 0, '+', 0);

  ck_assert_int_eq(0, h_is_not_equal(a, b));
}
END_TEST

START_TEST(test_h_is_not_equal_1) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 1, '+', 0);
  set_decimal_value(&b, 0, 0, 2, '+', 0);

  ck_assert_int_eq(1, h_is_not_equal(a, b));
}
END_TEST

START_TEST(test_h_is_not_equal_2) {
  h_decimal a, b;
  set_decimal_empty(&a);
  set_decimal_empty(&b);
  set_decimal_value(&a, 0, 0, 0, '-', 0);
  set_decimal_value(&b, 0, 0, 0, '+', 0);

  ck_assert_int_eq(0, h_is_not_equal(a, b));
}
END_TEST

Suite* suite_h_compare() {
  Suite* s = suite_create("h_compare");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_is_empty_0);
  tcase_add_test(tc_core, test_h_is_empty_1);
  tcase_add_test(tc_core, test_h_is_empty_2);
  tcase_add_test(tc_core, test_h_is_empty_3);
  tcase_add_test(tc_core, test_h_is_empty_4);
  tcase_add_test(tc_core, test_h_is_empty_5);
  tcase_add_test(tc_core, test_h_is_equal_zero_0);
  tcase_add_test(tc_core, test_h_is_equal_zero_1);
  tcase_add_test(tc_core, test_h_is_equal_zero_2);
  tcase_add_test(tc_core, test_h_is_equal_zero_3);
  tcase_add_test(tc_core, test_h_is_equal_zero_4);
  tcase_add_test(tc_core, test_h_is_equal_zero_5);
  tcase_add_test(tc_core, test_h_is_equal_0);
  tcase_add_test(tc_core, test_h_is_equal_1);
  tcase_add_test(tc_core, test_h_is_equal_2);
  tcase_add_test(tc_core, test_h_is_equal_3);
  tcase_add_test(tc_core, test_h_is_equal_4);
  tcase_add_test(tc_core, test_h_is_equal_5);
  tcase_add_test(tc_core, test_h_is_more_0);
  tcase_add_test(tc_core, test_h_is_more_1);
  tcase_add_test(tc_core, test_h_is_more_2);
  tcase_add_test(tc_core, test_h_is_more_3);
  tcase_add_test(tc_core, test_h_is_more_4);
  tcase_add_test(tc_core, test_h_is_more_5);
  tcase_add_test(tc_core, test_h_is_more_6);
  tcase_add_test(tc_core, test_h_is_more_7);
  tcase_add_test(tc_core, test_h_is_less_0);
  tcase_add_test(tc_core, test_h_is_less_1);
  tcase_add_test(tc_core, test_h_is_less_2);
  tcase_add_test(tc_core, test_h_is_less_3);
  tcase_add_test(tc_core, test_h_is_less_4);
  tcase_add_test(tc_core, test_h_is_less_5);
  tcase_add_test(tc_core, test_h_is_less_6);
  tcase_add_test(tc_core, test_h_is_less_7);
  tcase_add_test(tc_core, test_h_is_equal_h_0);
  tcase_add_test(tc_core, test_h_is_equal_h_1);
  tcase_add_test(tc_core, test_h_is_equal_h_2);
  tcase_add_test(tc_core, test_h_is_equal_h_3);
  tcase_add_test(tc_core, test_h_is_equal_h_4);
  tcase_add_test(tc_core, test_h_is_equal_h_5);
  tcase_add_test(tc_core, test_h_is_equal_h_6);
  tcase_add_test(tc_core, test_h_is_less_h_0);
  tcase_add_test(tc_core, test_h_is_less_h_1_1);
  tcase_add_test(tc_core, test_h_is_less_h_1_2);
  tcase_add_test(tc_core, test_h_is_less_h_2);
  tcase_add_test(tc_core, test_h_is_less_h_3);
  tcase_add_test(tc_core, test_h_is_less_h_4);
  tcase_add_test(tc_core, test_h_is_less_h_5);
  tcase_add_test(tc_core, test_h_is_less_h_6);
  tcase_add_test(tc_core, test_h_is_less_h_7);
  tcase_add_test(tc_core, test_h_is_less_or_equal_0);
  tcase_add_test(tc_core, test_h_is_less_or_equal_1);
  tcase_add_test(tc_core, test_h_is_less_or_equal_2);
  tcase_add_test(tc_core, test_h_is_greater_0);
  tcase_add_test(tc_core, test_h_is_greater_1);
  tcase_add_test(tc_core, test_h_is_greater_2);
  tcase_add_test(tc_core, test_h_is_greater_or_equal_0);
  tcase_add_test(tc_core, test_h_is_greater_or_equal_1);
  tcase_add_test(tc_core, test_h_is_greater_or_equal_2);
  tcase_add_test(tc_core, test_h_is_not_equal_0);
  tcase_add_test(tc_core, test_h_is_not_equal_1);
  tcase_add_test(tc_core, test_h_is_not_equal_2);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_0);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_1);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_2);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_3);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_4);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_5);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_6);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_7);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_8);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_9);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_10);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_11);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_12);
  tcase_add_test(tc_core, test_h_is_less_h_case_1_13);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_0);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_1);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_2);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_3);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_4);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_5);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_6);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_7);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_8);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_9);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_10);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_11);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_12);
  tcase_add_test(tc_core, test_h_is_less_h_case_2_13);

  suite_add_tcase(s, tc_core);
  return s;
}
