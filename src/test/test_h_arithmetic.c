#include "../h_decimal.h"
#include "../h_decimal_arithmetic.h"
#include "../h_decimal_compare.h"
#include "../h_decimal_internal.h"
#include "test_suite.h"

// сумма мантисс (с переносом разрядов)
// int sum_mantissa_bd(const big_decimal *a, const big_decimal *b,
//                  big_decimal*result);

START_TEST(test_h_sum_mantissa_bd_0) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_1) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 1, 1, 1, 1, 1, 0);
  set_decimal_mantissa_bd(&b, 2, 2, 2, 2, 2, 0);
  set_decimal_mantissa_bd(&result, 3, 3, 3, 3, 3, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_2) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 1, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_3) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, -1, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 1, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 1, 0, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_4) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, -1, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 1, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 1, 0, 0, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_5) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, -1, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 1, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 1, 0, 0, 0, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_6) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, -1, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 1, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 1, 0, 0, 0, 0, 0);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

START_TEST(test_h_sum_mantissa_bd_7) {
  big_decimal a, b, sum, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, -1, -1, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&result, 0, 0, 1, 0, 0, 1);
  sum_mantissa_bd(&a, &b, &sum);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sum));
}
END_TEST

// ошибка переполнения. сохранение предыдущего результата
START_TEST(test_h_sum_mantissa_bd_err) {
  big_decimal a, b, sum;
  set_decimal_empty_bd(&sum);
  set_decimal_mantissa_bd(&a, -1, -1, -1, -1, -1, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  ck_assert_int_eq(ERR_STANDART, sum_mantissa_bd(&a, &b, &sum));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&sum, &sum));
}
END_TEST

// вычитание мантисс a - b (с переносом разрядов)
// int sub_mantissa_bd(const big_decimal *a, const big_decimal *b,
//                     big_decimal *result);

START_TEST(test_h_sub_mantissa_bd_0) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_1) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_2) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 10, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 4, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 6, 0, 0, 0);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_3) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 1, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_4) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 1, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, -1, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_5) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 0, 1, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, 0, -1, -1, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_6) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 0, 1, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, -1, -1, -1, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_7) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 1, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, -1, -1, -1, -1, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

START_TEST(test_h_sub_mantissa_bd_8) {
  big_decimal a, b, sub, result;
  set_decimal_mantissa_bd(&a, 1, 0, 2, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 1, 0, 1, -1, -1, -1);
  sub_mantissa_bd(&a, &b, &sub);
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &sub));
}
END_TEST

// умножение мантисс a*b (с переносом разрядов)
// int mult_mantissa_bd(const big_decimal *a, const big_decimal *b,
//                      big_decimal *result);

START_TEST(test_h_mult_mantissa_bd_0) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_1) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 1, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_2) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 1, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_3) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 4);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 12);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_4) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 4, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 12, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_5) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 4, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 12, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_6) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 4, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 0, 12, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_7) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 4, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 12, 0, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_8) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 4, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 12, 0, 0, 0, 0, 0);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_9) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, -1);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_10) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 1, -2);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_11) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, -1, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 1, -1, -2);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_12) {
  big_decimal a, b, mul, result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, -1, -1, -1);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&result, 0, 0, 1, -1, -1, -2);
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

START_TEST(test_h_mult_mantissa_bd_err) {
  big_decimal a, b, mul, result;
  set_decimal_one_bd(&mul);
  copy_decimal_bd(&mul, &result);
  set_decimal_mantissa_bd(&a, -1, 0, 0, 0, 0, -1);
  set_decimal_mantissa_bd(&b, 0, -1, 0, 0, 0, -1);
  ck_assert_int_eq(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
  ck_assert_int_eq(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
}
END_TEST

// аналитический метод заполнения разрядов (планшет->конспект)
// START_TEST(test_h_mult_mantissa_bd_10) {
//   big_decimal a, b, mul, result;
//   unsigned int a0, a1, a2, b0, b1, b2, m0, m1, m2,m3,m4;
//   a0 =
//   a1 =
//   a2 =
//   b0 =
//   b1 =
//   b2 =

//   m0 = (unsigned long int)a0 * b0;
//   m1 =
//   m2 =
//   m3 =
//   m4 =
//   m5 =
//   set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 2, 0);
//   set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 2, 0);
//   set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 1, -2);
//   ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&a, &b, &mul));
//   ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
//   ck_assert_int_ne(ERR_STANDART, mult_mantissa_bd(&b, &a, &mul));
//   ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &mul));
// }
// END_TEST

// деление мантисс a/b = result и a%b = mod_dec
// int div_mantissa_bd(const big_decimal *a, const big_decimal *b,
//                  big_decimal *result, big_decimal *mod_dec);

START_TEST(test_h_div_mantissa_bd_zero_div) {
  big_decimal a, b, div_, mod_;
  big_decimal result, mod_result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 6);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 0);
  set_decimal_mantissa_bd(&mod_result, 0, 0, 0, 0, 0, 0);

  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&a, &b, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));

  ck_assert_int_eq(ERR_STANDART, div_mantissa_bd(&b, &a, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));
}
END_TEST

START_TEST(test_h_div_mantissa_bd_0) {
  big_decimal a, b, div_, mod_;
  big_decimal result, mod_result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 0, 0, 6);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 0, 3);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 2);
  set_decimal_mantissa_bd(&mod_result, 0, 0, 0, 0, 0, 0);

  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&a, &b, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));

  set_decimal_empty_bd(&result);
  copy_decimal_bd(&b, &mod_result);
  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&b, &a, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));
}
END_TEST

START_TEST(test_h_div_mantissa_bd_1) {
  big_decimal a, b, div_, mod_;
  big_decimal result, mod_result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 6, 0, 3);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 0, 1, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 6, 0);
  set_decimal_mantissa_bd(&mod_result, 0, 0, 0, 0, 0, 3);

  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&a, &b, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));

  set_decimal_empty_bd(&result);
  copy_decimal_bd(&b, &mod_result);
  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&b, &a, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));
}
END_TEST

START_TEST(test_h_div_mantissa_bd_2) {
  big_decimal a, b, div_, mod_;
  big_decimal result, mod_result;
  set_decimal_mantissa_bd(&a, 0, 0, 0, 154, 0, 0);
  set_decimal_mantissa_bd(&b, 0, 0, 0, 154, 0, 0);
  set_decimal_mantissa_bd(&result, 0, 0, 0, 0, 0, 1);
  set_decimal_mantissa_bd(&mod_result, 0, 0, 0, 0, 0, 0);

  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&a, &b, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));

  ck_assert_int_ne(ERR_STANDART, div_mantissa_bd(&b, &a, &div_, &mod_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&result, &div_));
  ck_assert_int_eq(1, is_equal_mantissa_bd(&mod_result, &mod_));
}
END_TEST

// int h_add(h_decimal value_1, h_decimal value_2, h_decimal *result);

START_TEST(test_h_add_err_plus_inf) {
  h_decimal x, y;
  set_decimal_value(&x, -1, -1, -1, 0, 0);
  set_decimal_value(&y, 0, 0, 1, 0, 0);

  h_decimal sum;
  set_decimal_empty(&sum);

  ck_assert_int_eq(ERR_PLUS_INF, h_add(x, y, &sum));
  ck_assert_int_eq(1, h_is_equal(sum, sum));
}
END_TEST

START_TEST(test_h_add_err_minus_inf) {
  h_decimal x, y;
  set_decimal_value(&x, -1, -1, -1, 1, 0);
  set_decimal_value(&y, 0, 0, 1, 1, 0);

  h_decimal sum;
  set_decimal_empty(&sum);

  ck_assert_int_eq(ERR_MINUS_INF, h_add(x, y, &sum));
  ck_assert_int_eq(1, h_is_equal(sum, sum));
}
END_TEST

START_TEST(test_h_add_1) {
  h_decimal x, y, result;
  set_decimal_value(&x, -1, -1, -1, 0, 0);
  set_decimal_value(&y, 0, 0, 6, 1, 1);
  set_decimal_value(&result, -1, -1, -2, 0, 0);

  h_decimal sum;
  set_decimal_empty(&sum);

  ck_assert_int_eq(0, h_add(x, y, &sum));
  ck_assert_int_eq(1, h_is_equal(result, sum));
}
END_TEST

//

START_TEST(test_h_sub_1) {
  h_decimal x, y, result;
  set_decimal_value(&x, -1, -1, -1, 0, 0);
  set_decimal_value(&y, 0, 0, 6, 0, 1);
  set_decimal_value(&result, -1, -1, -2, 0, 0);

  h_decimal sub;
  set_decimal_empty(&sub);

  ck_assert_int_eq(0, h_sub(x, y, &sub));
  ck_assert_int_eq(1, h_is_equal(result, sub));
}
END_TEST

//

START_TEST(test_h_mult_1) {
  h_decimal x, y, result;

  set_decimal_value(&x, 0, 124000, -2000, 0, 0);
  set_decimal_value(&y, 0, 112, 1112300004, 1, 5);
  set_decimal_value(&result, 13920225, 2027795038, 193051328, 1, 5);

  h_decimal mult;
  set_decimal_empty(&mult);

  ck_assert_int_eq(0, h_mul(x, y, &mult));
  ck_assert_int_eq(1, h_is_equal(result, mult));
}
END_TEST

//

START_TEST(test_h_div_zero) {
  h_decimal x, y, result;

  set_decimal_value(&x, 0, 0, 0, 1, 3);
  set_decimal_value(&y, 2, 2, 1, 0, 0);
  set_decimal_empty(&result);

  h_decimal div;
  set_decimal_empty(&div);

  ck_assert_int_eq(0, h_div(x, y, &div));
  ck_assert_int_eq(1, h_is_equal(result, div));
}
END_TEST

START_TEST(test_h_div_zero_div) {
  h_decimal x, y, result;

  set_decimal_value(&x, 0, 0, 1000, 1, 3);
  set_decimal_value(&y, 0, 0, 0, 0, 0);
  set_decimal_value(&result, 0, 0, 1, 0, 0);

  h_decimal div;
  set_decimal_empty(&div);

  ck_assert_int_eq(ERR_ZERO_DIV, h_div(x, y, &div));
  ck_assert_int_eq(1, h_is_equal(div, div));
}
END_TEST

START_TEST(test_h_div_1) {
  h_decimal x, y, result;

  set_decimal_value(&x, 0, -1, -1, 0, 0);
  set_decimal_value(&y, 0, -1, -1, 1, 5);
  set_decimal_value(&result, 0, 0, 100000, 1, 0);

  h_decimal div;
  set_decimal_empty(&div);

  ck_assert_int_eq(0, h_div(x, y, &div));
  ck_assert_int_eq(1, h_is_equal(result, div));
}
END_TEST

START_TEST(test_h_div_2) {
  h_decimal x, y, result;

  set_decimal_value(&x, -1, -1, -1, 1, 0);
  set_decimal_value(&y, -1, -1, -1, 0, 1);
  set_decimal_value(&result, 0, 0, 10, 1, 0);

  h_decimal div;
  set_decimal_empty(&div);

  ck_assert_int_eq(0, h_div(x, y, &div));
  ck_assert_int_eq(1, h_is_equal(result, div));
}
END_TEST

START_TEST(test_h_div_3) {
  h_decimal x, y, result;

  set_decimal_value(&x, 0, 0, 1000, 1, 3);
  set_decimal_value(&y, 0, 0, 1, 1, 0);
  set_decimal_value(&result, 0, 0, 1, 0, 0);

  h_decimal div;
  set_decimal_empty(&div);

  ck_assert_int_eq(0, h_div(x, y, &div));
  ck_assert_int_eq(1, h_is_equal(result, div));
}
END_TEST

Suite* suite_h_arithmetic() {
  Suite* s = suite_create("h_arithmetic");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_sum_mantissa_bd_0);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_1);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_2);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_3);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_4);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_5);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_6);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_7);
  tcase_add_test(tc_core, test_h_sum_mantissa_bd_err);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_0);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_1);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_2);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_3);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_4);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_5);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_6);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_7);
  tcase_add_test(tc_core, test_h_sub_mantissa_bd_8);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_0);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_1);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_2);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_3);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_4);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_5);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_6);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_7);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_8);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_9);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_10);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_11);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_12);
  tcase_add_test(tc_core, test_h_mult_mantissa_bd_err);
  tcase_add_test(tc_core, test_h_div_mantissa_bd_zero_div);
  tcase_add_test(tc_core, test_h_div_mantissa_bd_0);
  tcase_add_test(tc_core, test_h_div_mantissa_bd_1);
  tcase_add_test(tc_core, test_h_div_mantissa_bd_2);
  tcase_add_test(tc_core, test_h_add_err_plus_inf);
  tcase_add_test(tc_core, test_h_add_err_minus_inf);
  tcase_add_test(tc_core, test_h_add_1);
  tcase_add_test(tc_core, test_h_sub_1);
  tcase_add_test(tc_core, test_h_mult_1);
  tcase_add_test(tc_core, test_h_div_zero);
  tcase_add_test(tc_core, test_h_div_zero_div);
  tcase_add_test(tc_core, test_h_div_1);
  tcase_add_test(tc_core, test_h_div_2);
  tcase_add_test(tc_core, test_h_div_3);

  suite_add_tcase(s, tc_core);
  return s;
}
