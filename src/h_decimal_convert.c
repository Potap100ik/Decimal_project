#include "h_decimal_convert.h"

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "h_decimal_arithmetic.h"
#include "h_decimal_bit_logic.h"
#include "h_decimal_compare.h"
#include "h_decimal_internal.h"
#include "h_decimal_rounding.h"
#include "h_decimal_scale.h"

int h_from_int_to_decimal(int src, h_decimal* dst) {
  if (dst == NULL) return ERR_CONVERT;
  int er = 0;
  set_decimal_empty(dst);
  if (src != 0) {
    long int value = src;
    int sign = DECIMAL_SIGN_PLUS_VAL;
    if (value < 0) {
      sign = DECIMAL_SIGN_MINUS_VAL;
      value = -value;
    }
    set_decimal_mantissa(dst, 0, 0, (unsigned int)value);
    set_exp(dst, 0);
    set_sign(dst, sign);
  }
  return er;
}

int h_from_float_to_decimal(float src, h_decimal* dst) {
  if (dst == NULL) return ERR_STANDART;
  int er = 0;
  if (isnan(src) || isinf(src)) {
    errors__(ERR_CONVERT, &er);
  } else if (fabsf(src) < 1e-28 && src != 0.0f) {
    set_decimal_empty(dst);
    errors__(ERR_CONVERT, &er);
  } else if (src == 0.0f) {
    set_decimal_empty(dst);
  } else {
    h_decimal dst_buffer;
    set_decimal_empty(&dst_buffer);

    unsigned int u;
    memcpy(&u, &src, sizeof(u));
    unsigned int sign = 1u & (u >> 31);
    unsigned int exp = (u >> 23) & ((1u << 8) - 1u);
    unsigned int frac = u & ((1u << 23) - 1u);

    int e = (int)exp - 127 - 23;
    unsigned mantissa = frac | (1u << 23);

    big_decimal scale_bd, mantissa_bd, result_bd;
    set_decimal_empty_bd(&scale_bd);
    set_decimal_empty_bd(&mantissa_bd);
    set_decimal_empty_bd(&result_bd);

    shift_one_bd(&scale_bd, e > 0 ? e : -e);
    mantissa_bd.bits[0] = mantissa;

    if (e < 0) {
      errors__(
          long_div_to_fit_mantissa_exp(&mantissa_bd, &scale_bd, &result_bd),
          &er);
    } else {
      errors__(mult_mantissa_bd(&mantissa_bd, &scale_bd, &result_bd), &er);
    }
    errors__(round_decimal_to_bd(&result_bd, 7, &result_bd, bank_decision_bd),
             &er);
    errors__(reduce_scale_to_decimal_bd(&result_bd, &dst_buffer, bank_decision),
             &er);
    errors__(normalize(&dst_buffer, &dst_buffer), &er);
    if (er == 0) {
      set_sign(&dst_buffer, sign);
      copy_decimal(&dst_buffer, dst);
    }
  }
  return er;
}

int h_from_decimal_to_int(h_decimal src, int* dst) {
  if (dst == NULL) return ERR_CONVERT;
  int er = 0;
  *dst = 0;

  errors__(reduce_scale(&src, &src, truncate_decision), &er);

  for (unsigned int i = 1; i < DECIMAL_DATA_PARTS && er == 0; ++i) {
    if (src.bits[i] != 0) {
      er = ERR_CONVERT;
    }
  }
  if (er == 0) {
    long int value = src.bits[0];
    if (get_sign(&src) == DECIMAL_SIGN_MINUS_VAL) {
      value = -value;
      if (value < INT_MIN) {
        er = ERR_CONVERT;
      } else {
        *dst = (int)value;
      }
    } else {
      if (value > INT_MAX) {
        er = ERR_CONVERT;
      } else {
        *dst = (int)value;
      }
    }
  }
  return er;
}

int h_from_decimal_to_float(h_decimal src, float* dst) {
  if (dst == NULL) return ERR_STANDART;
  int er = 0;
  if (is_equal_zero(&src)) {
    *dst = 0;
  } else {
    double dst_d;
    int buffer = 0;

    errors__(round_decimal_to(&src, 7, &src, bank_decision), &er);
    errors__(normalize(&src, &src), &er);

    if (get_exp(&src) == 0) {
      h_decimal mod_dec, ten;
      set_decimal_empty(&mod_dec);
      set_decimal_ten(&ten);
      div_mantissa(&src, &ten, NULL, &mod_dec);
      int exp = 0;
      while (is_equal_zero(&mod_dec) == 1) {
        div_mantissa(&src, &ten, &src, NULL);
        exp++;
        div_mantissa(&src, &ten, NULL, &mod_dec);
      }

      errors__(h_from_decimal_to_int(src, &buffer), &er);
      dst_d = buffer;
      for (int i = 0; i < exp; ++i) {
        dst_d *= 10.0;
      }
    } else {
      int scale = get_exp(&src);
      errors__(set_exp(&src, 0), &er);
      errors__(h_from_decimal_to_int(src, &buffer), &er);
      dst_d = buffer;
      for (int i = 0; i < scale; ++i) {
        dst_d /= 10.0;
      }
    }
    *dst = (float)dst_d;
  }
  return er;
}

int decimal_to_int_mantissa(const h_decimal* x, int* result) {
  int er = 0;
  *result = 0;
  // проверка старших разрядов decimal
  for (unsigned int i = 1; i < DECIMAL_DATA_PARTS && er == 0; ++i) {
    if (x->bits[i] != 0) {
      errors__(ERR_CONVERT, &er);
    }
  }
  unsigned int value = x->bits[0];
  if (er == 0 && !(value > INT_MAX)) {
    *result = value;
  } else {
    errors__(ERR_CONVERT, &er);
  }
  return er;
}

int decimal_to_bd(const h_decimal* x, big_decimal* result) {
  if (x == NULL || result == NULL) return ERR_STANDART;
  set_decimal_empty_bd(result);
  for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
    result->bits[i] = x->bits[i];
  }
  result->exp = get_exp(x);
  result->sign = get_sign(x);
  return 0;
}

int bd_to_decimal(const big_decimal* x, h_decimal* result) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  // проверка пустоты старшей части big decimal
  for (int i = DECIMAL_DATA_PARTS; i < BIG_DECIMAL_DATA_PARTS && er == 0; ++i) {
    if (x->bits[i] != 0) {
      errors__(ERR_OVERFLOW, &er);
    }
  }
  if (er == 0) {
    if (result != NULL) {
      set_decimal_empty(result);
      for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
        result->bits[i] = x->bits[i];
      }
      errors__(set_exp(result, x->exp), &er);
      errors__(set_sign(result, x->sign), &er);
    }
  }
  return er;
}
