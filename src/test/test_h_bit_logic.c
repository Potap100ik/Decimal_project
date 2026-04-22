#include "../h_decimal.h"
#include "../h_decimal_bit_logic.h"
#include "../h_decimal_compare.h"
#include "../h_decimal_internal.h"
#include "test_suite.h"

// // проверка конктерного бита внутри long int
// int check_bit(long unsigned int x, unsigned int index);

START_TEST(test_h_check_bit_0) {
  unsigned long int val = 0;
  unsigned int index = 22;
  ck_assert_int_eq(0, check_bit(val, index));
}
END_TEST

START_TEST(test_h_check_bit_1) {
  unsigned int shift = 0;
  unsigned int index = shift;
  unsigned long int val = 1UL << shift;
  ck_assert_int_eq(1, check_bit(val, index));
}
END_TEST

START_TEST(test_h_check_bit_2) {
  unsigned int shift = 0;
  unsigned int index = shift + 1;
  unsigned long int val = 1UL << shift;
  ck_assert_int_ne(1, check_bit(val, index));
}
END_TEST

START_TEST(test_h_check_bit_63) {
  unsigned int shift = 63;
  unsigned int index = shift;
  unsigned long int val = 1UL << shift;
  ck_assert_int_eq(1, check_bit(val, index));
}
END_TEST

START_TEST(test_h_check_bit_minus) {
  unsigned int shift = 63;
  unsigned int index = (unsigned int)(ULONG_BITS - ULONG_BITS / 2);
  unsigned long int val = (1UL << shift) - 1;
  ck_assert_int_eq(1, check_bit(val, index));
}
END_TEST

START_TEST(test_h_check_bit_err) {
  unsigned int shift = 63;
  unsigned int index = shift * 2;
  unsigned long int val = 1UL << shift;
  ck_assert_int_eq(ERR_STANDART, check_bit(val, index));
}
END_TEST

// // установка 0 по индексу в unsigned int
// int bit_set_0(unsigned int *x, unsigned int index);

START_TEST(test_h_bit_set_0) {
  unsigned int shift = 31;
  unsigned int index = (unsigned int)(UINT_BITS - UINT_BITS / 2);
  unsigned int val = (1u << shift) - 1;
  bit_set_0(&val, index);
  ck_assert_int_eq(0, check_bit(val, index));
}
END_TEST

// // установка 1 по индексу в unsigned int
// int bit_set_1(unsigned int *x, unsigned int index);

START_TEST(test_h_bit_set_1) {
  unsigned int index = (unsigned int)(UINT_BITS - UINT_BITS / 2);
  unsigned int val = 0;
  bit_set_1(&val, index);
  ck_assert_int_eq(1, check_bit(val, index));
}
END_TEST

// // проверка конкретного бита внутри decimal
// int check_decimal_bit(const h_decimal *x, unsigned int index);

// // сдвиг единицы внутри decimal на индекс (аналог 2^i)
// int shift_one(h_decimal *buffer, unsigned int index);

// // побитовый & для decimal
// int dec_and(const h_decimal *a, const h_decimal *b, h_decimal *result);
// // побитовый | для decimal
// int dec_or(const h_decimal *a, const h_decimal *b, h_decimal *result);

// // побитовый ~ для decimal
// int dec_not(const h_decimal *x, h_decimal *result);

START_TEST(test_h_dec_not) {
  unsigned int x0 = -12345, x1 = -123456, x2 = -1234567;
  unsigned int y0 = ~x0, y1 = ~x1, y2 = ~x2;

  h_decimal x, y;
  set_decimal_empty(&x);
  set_decimal_empty(&y);
  set_decimal_mantissa(&x, x2, x1, x0);
  set_decimal_mantissa(&y, y2, y1, y0);

  ck_assert_int_eq(0, dec_not(&x, &x));
  ck_assert_int_eq(1, is_equal_mantissa(&x, &y));
}
END_TEST

// // сдвиг влево всего decimal на индекс (аналог <<)
// int dec_shift_left(const h_decimal *x, unsigned int shift,
//                    h_decimal *buffer);

START_TEST(test_h_dec_shift_left_0) {
  unsigned int shift = 0, sh0 = 2, sh1 = 3, sh2 = 4;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << (sh2 + shift), 1 << (sh1 + shift),
                       1 << (sh0 + shift));

  ck_assert_int_eq(0, dec_shift_left(&x1, shift, &x1));

  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_bitshift) {
  unsigned int shift = 2, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << (sh2 + shift), 1 << (sh1 + shift),
                       1 << (sh0 + shift));

  ck_assert_int_eq(0, dec_shift_left(&x1, shift, &x1));

  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_wordshift_1) {
  unsigned int shift = UINT_BITS, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << sh1, 1 << sh0, 0);

  ck_assert_int_eq(0, dec_shift_left(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_wordshift_2) {
  unsigned int shift = UINT_BITS * 2, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << sh0, 0, 0);

  ck_assert_int_eq(0, dec_shift_left(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_wordshift_err) {
  unsigned int shift = UINT_BITS * 3, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  copy_decimal(&x1, &x2);

  ck_assert_int_eq(ERR_STANDART, dec_shift_left(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_bitshift_through) {
  unsigned int bit_shift = 3;
  unsigned int x1_sh2 = -12345, x1_sh1 = -123456, x1_sh0 = -1234567;
  unsigned int val2 = x1_sh2 << bit_shift, val1 = x1_sh1 << bit_shift,
               val0 = x1_sh0 << bit_shift;
  val1 |= x1_sh0 >> (UINT_BITS - bit_shift);
  val2 |= x1_sh1 >> (UINT_BITS - bit_shift);

  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, x1_sh2, x1_sh1, x1_sh0);
  set_decimal_mantissa(&x2, val2, val1, val0);

  ck_assert_int_eq(0, dec_shift_left(&x1, bit_shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_left_shift_through) {
  unsigned int word_shift = UINT_BITS;
  unsigned int bit_shift = 3;
  unsigned int shift = word_shift + bit_shift;
  unsigned int x1_sh0 = -12345, x1_sh1 = -123456, x1_sh2 = -1234567;
  unsigned int val0 = 0, val1 = x1_sh0 << bit_shift, val2 = x1_sh1 << bit_shift;
  val2 |= x1_sh1 >> (UINT_BITS - bit_shift);

  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, x1_sh2, x1_sh1, x1_sh0);
  set_decimal_mantissa(&x2, val2, val1, val0);

  ck_assert_int_eq(0, dec_shift_left(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

// // сдвиг вправо всего decimal на индекс (аналог >>)
// int dec_shift_right(const h_decimal *x, unsigned int shift,
//                     h_decimal *buffer);

START_TEST(test_h_dec_shift_right_0) {
  unsigned int shift = 0, sh0 = 2, sh1 = 3, sh2 = 4;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << (sh2 - shift), 1 << (sh1 - shift),
                       1 << (sh0 - shift));

  ck_assert_int_eq(0, dec_shift_right(&x1, shift, &x1));

  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_bitshift) {
  unsigned int shift = 2, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 1 << (sh2 - shift), 1 << (sh1 - shift),
                       1 << (sh0 - shift));

  ck_assert_int_eq(0, dec_shift_right(&x1, shift, &x1));

  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_wordshift_1) {
  unsigned int shift = UINT_BITS, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 0, 1 << sh2, 1 << sh1);

  ck_assert_int_eq(0, dec_shift_right(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_wordshift_2) {
  unsigned int shift = UINT_BITS * 2, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  set_decimal_mantissa(&x2, 0, 0, 1 << sh2);

  ck_assert_int_eq(0, dec_shift_right(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_wordshift_err) {
  unsigned int shift = UINT_BITS * 3, sh0 = 16, sh1 = 17, sh2 = 18;
  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, 1 << sh2, 1 << sh1, 1 << sh0);
  copy_decimal(&x1, &x2);

  ck_assert_int_eq(ERR_STANDART, dec_shift_right(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_bitshift_through) {
  unsigned int bit_shift = 3;
  unsigned int x1_sh0 = 12345, x1_sh1 = 123456, x1_sh2 = 1234567;
  unsigned int val0 = x1_sh0 >> bit_shift, val1 = x1_sh1 >> bit_shift,
               val2 = x1_sh2 >> bit_shift;
  val0 |= x1_sh1 << (UINT_BITS - bit_shift);
  val1 |= x1_sh2 << (UINT_BITS - bit_shift);

  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, x1_sh2, x1_sh1, x1_sh0);
  set_decimal_mantissa(&x2, val2, val1, val0);

  ck_assert_int_eq(0, dec_shift_right(&x1, bit_shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

START_TEST(test_h_dec_shift_right_shift_through) {
  unsigned int word_shift = UINT_BITS;
  unsigned int bit_shift = 3;
  unsigned int shift = word_shift + bit_shift;
  unsigned int x1_sh0 = 12345, x1_sh1 = 123456, x1_sh2 = 1234567;
  unsigned int val0 = x1_sh1 >> bit_shift, val1 = x1_sh2 >> bit_shift, val2 = 0;
  val0 |= x1_sh2 << (UINT_BITS - bit_shift);

  h_decimal x1, x2;
  set_decimal_empty(&x1);
  set_decimal_empty(&x2);
  set_decimal_mantissa(&x1, x1_sh2, x1_sh1, x1_sh0);
  set_decimal_mantissa(&x2, val2, val1, val0);

  ck_assert_int_eq(0, dec_shift_right(&x1, shift, &x1));
  ck_assert_int_eq(1, is_equal_mantissa(&x1, &x2));
}
END_TEST

// // вспомогательные функции для реализации сдвига влево/вправо в decimal
// // сдвиг на несколько разрядов - перенос значений разрядов и очищение
// // (зануление)
// int word_shift_left(h_decimal *x, unsigned int words);

// // сдвиг внутри разрядов
// int bit_shift_left(h_decimal *x, unsigned int shift);

// // сдвиг на несколько разрядов - перенос значений разрядов и очищение
// // (зануление)
// int word_shift_right(h_decimal *x, unsigned int words);

// // сдвиг внутри разрядов
// int bit_shift_right(h_decimal *x, unsigned int shift);

Suite* suite_h_bit_logic() {
  Suite* s = suite_create("h_bit_logic");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, test_h_check_bit_0);
  tcase_add_test(tc_core, test_h_check_bit_1);
  tcase_add_test(tc_core, test_h_check_bit_2);
  tcase_add_test(tc_core, test_h_check_bit_63);
  tcase_add_test(tc_core, test_h_check_bit_minus);
  tcase_add_test(tc_core, test_h_check_bit_err);
  tcase_add_test(tc_core, test_h_bit_set_0);
  tcase_add_test(tc_core, test_h_bit_set_1);
  tcase_add_test(tc_core, test_h_dec_not);
  tcase_add_test(tc_core, test_h_dec_shift_left_0);
  tcase_add_test(tc_core, test_h_dec_shift_left_bitshift);
  tcase_add_test(tc_core, test_h_dec_shift_left_wordshift_1);
  tcase_add_test(tc_core, test_h_dec_shift_left_wordshift_2);
  tcase_add_test(tc_core, test_h_dec_shift_left_wordshift_err);
  tcase_add_test(tc_core, test_h_dec_shift_left_bitshift_through);
  tcase_add_test(tc_core, test_h_dec_shift_left_shift_through);
  tcase_add_test(tc_core, test_h_dec_shift_right_0);
  tcase_add_test(tc_core, test_h_dec_shift_right_bitshift);
  tcase_add_test(tc_core, test_h_dec_shift_right_wordshift_1);
  tcase_add_test(tc_core, test_h_dec_shift_right_wordshift_2);
  tcase_add_test(tc_core, test_h_dec_shift_right_wordshift_err);
  tcase_add_test(tc_core, test_h_dec_shift_right_bitshift_through);
  tcase_add_test(tc_core, test_h_dec_shift_right_shift_through);

  suite_add_tcase(s, tc_core);
  return s;
}
