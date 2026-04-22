#include "h_decimal_scale.h"

#include <stdlib.h>

#include "h_decimal_arithmetic.h"
#include "h_decimal_compare.h"
#include "h_decimal_convert.h"
#include "h_decimal_internal.h"
#include "h_decimal_rounding.h"

int scale_up_to_bd(big_decimal* x, int exp_new) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  if (exp_new > x->exp) {
    big_decimal ten, result_buff;
    copy_decimal_bd(x, &result_buff);
    set_decimal_ten_bd(&ten);
    for (int i = x->exp; i < exp_new && er == 0; ++i) {
      errors__(mult_mantissa_bd(&result_buff, &ten, &result_buff), &er);
    }
    if (er == 0) {
      result_buff.exp = exp_new;
      copy_decimal_bd(&result_buff, x);
    }
  }

  return er;
}

int align_scales(big_decimal* a, big_decimal* b) {
  if (a == NULL || b == NULL) {
    return ERR_CONVERT;
  }
  int er = 0;
  if (a->exp > b->exp) {
    errors__(scale_up_to_bd(b, a->exp), &er);
  } else if (b->exp > a->exp) {
    errors__(scale_up_to_bd(a, b->exp), &er);
  }
  return er;
}

int reduce_scale(const h_decimal* x, h_decimal* result,
                 int (*floor_func)(h_decimal*, unsigned int)) {
  int er = 0;
  h_decimal result_buf, ten, mod_;
  set_decimal_empty(&mod_);
  set_decimal_ten(&ten);
  copy_decimal(x, &result_buf);
  int exp = get_exp(&result_buf);
  while (exp > 0) {
    div_mantissa(&result_buf, &ten, &result_buf, &mod_);
    // no errors??????
    exp--;
  }
  set_exp(&result_buf, exp);
  if (is_equal_zero(&result_buf) == 1 && is_equal_zero(&mod_) == 1) {
    set_decimal_empty(&result_buf);
  } else {
    int mod_int = 0;
    errors__(decimal_to_int_mantissa(&mod_, &mod_int), &er);
    errors__(floor_func(&result_buf, mod_int), &er);
  }
  if (er == 0) {
    copy_decimal(&result_buf, result);
  } else {
    er = er == ERR_OVERFLOW
             ? (get_sign(&result_buf) == DECIMAL_SIGN_MINUS_VAL ? ERR_MINUS_INF
                                                                : ERR_PLUS_INF)
             : er;
  }

  return er;
}

int reduce_scale_to_decimal_bd(const big_decimal* x, h_decimal* result,
                               int (*floor_func)(h_decimal*, unsigned int)) {
  int er = 0;
  if (is_equal_zero_bd(x) == 1) {
    set_decimal_empty(result);
  } else {
    big_decimal ten, result_bd, mod_bd;
    set_decimal_ten_bd(&ten);
    copy_decimal_bd(x, &result_bd);
    set_decimal_empty_bd(&mod_bd);
    h_decimal result_dec, mod_dec;
    set_decimal_empty(&result_dec);
    set_decimal_empty(&mod_dec);
    int mod_int = 0;

    while ((bd_to_decimal(&result_bd, NULL) != 0 ||
            result_bd.exp > DECIMAL_EXP_MAX_VAL) &&
           result_bd.exp > 0) {
      div_mantissa_bd(&result_bd, &ten, &result_bd, &mod_bd);
      result_bd.exp--;
    }
    errors__(bd_to_decimal(&result_bd, &result_dec), &er);
    errors__(bd_to_decimal(&mod_bd, &mod_dec), &er);
    errors__(decimal_to_int_mantissa(&mod_dec, &mod_int), &er);
    errors__(floor_func(&result_dec, mod_int), &er);
    if (is_equal_zero(&result_dec)) {
      set_decimal_empty(&result_dec);
    } else {
      errors__(normalize(&result_dec, &result_dec), &er);
    }

    if (er == 0) {
      copy_decimal(&result_dec, result);
    } else {
      er = er == ERR_OVERFLOW
               ? (x->sign == DECIMAL_SIGN_MINUS_VAL ? ERR_MINUS_INF
                                                    : ERR_PLUS_INF)
               : er;
    }
  }
  return er;
}