#include "h_decimal_compare.h"

#include <stdlib.h>

#include "h_decimal_convert.h"
#include "h_decimal_internal.h"
#include "h_decimal_scale.h"

int is_equal_mantissa(const h_decimal* a, const h_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1;
  for (int i = 0; i < DECIMAL_DATA_PARTS && result == 1; ++i)
    if (a->bits[i] != b->bits[i]) result = 0;
  return result;
}
int is_more_mantissa(const h_decimal* a, const h_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1, at_least_one_part_is_more = 0;

  for (int i = DECIMAL_DATA_PARTS - 1;
       i >= 0 && result == 1 && at_least_one_part_is_more == 0; --i) {
    if (a->bits[i] < b->bits[i])
      result = 0;
    else if (a->bits[i] > b->bits[i])
      at_least_one_part_is_more = 1;
  }
  if (at_least_one_part_is_more == 0) result = 0;
  return result;
}

int is_less_mantissa(const h_decimal* a, const h_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1, at_least_one_part_is_less = 0;

  for (int i = DECIMAL_DATA_PARTS - 1;
       i >= 0 && result == 1 && at_least_one_part_is_less == 0; --i) {
    if (a->bits[i] > b->bits[i])
      result = 0;
    else if (a->bits[i] < b->bits[i])
      at_least_one_part_is_less = 1;
  }
  if (at_least_one_part_is_less == 0) result = 0;
  return result;
}

int is_empty(const h_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int result = 1;
  for (int i = 0; i < DECIMAL_PARTS && result == 1; ++i) {
    if (x->bits[i] != 0) result = 0;
  }
  return result;
}

int is_equal_zero(const h_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int result = 1;
  for (int i = 0; i < DECIMAL_DATA_PARTS && result == 1; ++i) {
    if (x->bits[i] != 0) result = 0;
  }
  return result;
}

int h_is_less(h_decimal a, h_decimal b) {
  int result = 0;
  if (!(is_equal_zero(&a) == 1 && is_equal_zero(&b) == 1)) {
    int a_sign = get_sign(&a);
    int b_sign = get_sign(&b);
    if (a_sign != b_sign) {
      if (a_sign == DECIMAL_SIGN_MINUS_VAL) result = 1;
    } else {
      // рассуждение о положительных числах
      int a_exp = get_exp(&a);
      int b_exp = get_exp(&b);
      if (a_exp == b_exp) {
        result = a_sign == DECIMAL_SIGN_PLUS_VAL ? is_less_mantissa(&a, &b)
                                                 : is_more_mantissa(&a, &b);

      } else {
        big_decimal copy_a, copy_b;
        decimal_to_bd(&a, &copy_a);
        decimal_to_bd(&b, &copy_b);
        align_scales(&copy_a, &copy_b);
        result = copy_a.sign == DECIMAL_SIGN_PLUS_VAL
                     ? is_less_mantissa_bd(&copy_a, &copy_b)
                     : is_more_mantissa_bd(&copy_a, &copy_b);
      }
    }
  }
  return result;
}

int h_is_less_or_equal(h_decimal a, h_decimal b) {
  return h_is_less(a, b) || h_is_equal(a, b);
}

int h_is_greater(h_decimal a, h_decimal b) {
  return (h_is_less(a, b) == 1 || h_is_equal(a, b) == 1) ? 0 : 1;
}

int h_is_greater_or_equal(h_decimal a, h_decimal b) {
  return h_is_greater(a, b) || h_is_equal(a, b);
}

int h_is_equal(h_decimal a, h_decimal b) {
  int result = 0;
  if (is_equal_zero(&a) == 1 && is_equal_zero(&b) == 1) {
    result = 1;
  } else {
    int a_sign = get_sign(&a);
    int b_sign = get_sign(&b);
    if (a_sign != b_sign) {
      result = 0;
    } else {
      // рассуждение о положительных числах
      int a_exp = get_exp(&a);
      int b_exp = get_exp(&b);
      if (a_exp == b_exp) {
        result = is_equal_mantissa(&a, &b);
      } else {
        big_decimal copy_a, copy_b;
        decimal_to_bd(&a, &copy_a);
        decimal_to_bd(&b, &copy_b);
        align_scales(&copy_a, &copy_b);
        result = is_equal_mantissa_bd(&copy_a, &copy_b);
      }
    }
  }
  return result;
}

int h_is_not_equal(h_decimal a, h_decimal b) {
  return h_is_equal(a, b) == 0 ? 1 : 0;
}

/// BIG DECIMAL PART

int is_equal_mantissa_bd(const big_decimal* a, const big_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1;
  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS && result == 1; ++i)
    if (a->bits[i] != b->bits[i]) result = 0;
  return result;
}

int is_equal_zero_bd(const big_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int result = 1;
  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS && result == 1; ++i) {
    if (x->bits[i] != 0) result = 0;
  }
  return result;
}

int is_less_mantissa_bd(const big_decimal* a, const big_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1, at_least_one_part_is_less = 0;

  for (int i = BIG_DECIMAL_DATA_PARTS - 1;
       i >= 0 && result == 1 && at_least_one_part_is_less == 0; --i) {
    if (a->bits[i] > b->bits[i])
      result = 0;
    else if (a->bits[i] < b->bits[i])
      at_least_one_part_is_less = 1;
  }
  if (at_least_one_part_is_less == 0) result = 0;
  return result;
}

int is_more_mantissa_bd(const big_decimal* a, const big_decimal* b) {
  if (a == NULL || b == NULL) return ERR_STANDART;
  int result = 1, at_least_one_part_is_more = 0;

  for (int i = BIG_DECIMAL_DATA_PARTS - 1;
       i >= 0 && result == 1 && at_least_one_part_is_more == 0; --i) {
    if (a->bits[i] < b->bits[i])
      result = 0;
    else if (a->bits[i] > b->bits[i])
      at_least_one_part_is_more = 1;
  }
  if (at_least_one_part_is_more == 0) result = 0;
  return result;
}