#include "h_decimal_arithmetic.h"

#include <stdio.h>
#include <stdlib.h>

#include "h_decimal_bit_logic.h"
#include "h_decimal_compare.h"
#include "h_decimal_convert.h"
#include "h_decimal_internal.h"
#include "h_decimal_print.h"
#include "h_decimal_rounding.h"
#include "h_decimal_scale.h"

int sum_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result) {
  int er = 0;
  unsigned int carry_last = 0;
  h_decimal result_buff;
  set_decimal_empty(&result_buff);
  for (unsigned int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
    long unsigned int buffer =
        (long unsigned int)a->bits[i] + b->bits[i] +
        carry_last;  // надо привести хоть один операнд к ulong, чтобы
                     // дальнейшие вычисления не обрезались автоматически

    result_buff.bits[i] = (unsigned int)buffer;
    carry_last = (unsigned int)(buffer >> UINT_BITS);
  }
  // if (carry == 1)
  // переполнение на последнем регистре
  set_sign(&result_buff, get_sign(a));
  if (carry_last == 0) {
    copy_mantissa(&result_buff, result);
  } else {
    errors__(ERR_OVERFLOW, &er);
  }
  return er;
}

int sub_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  int er = 0;
  if (is_less_mantissa(a, b) == 1) {
    errors__(ERR_STANDART, &er);
  } else if (is_equal_mantissa(a, b)) {
    set_decimal_empty(result);
  } else {
    unsigned int carry_last = 0;

    h_decimal result_buff;
    set_decimal_empty(&result_buff);
    for (unsigned int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
      long int buffer =
          (long int)a->bits[i] - b->bits[i] -
          carry_last;  // надо привести хоть один операнд к ulong, чтобы
                       // дальнейшие вычисления не обрезались автоматически
      result_buff.bits[i] = (unsigned int)buffer;
      carry_last = (buffer >> UINT_BITS) != 0 ? 1 : 0;
    }
    copy_mantissa(&result_buff, result);
  }
  return er;
}

int mult_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result) {
  int er = 0;
  h_decimal buffer, result_buff;
  set_decimal_empty(&buffer);
  set_decimal_empty(&result_buff);
  for (unsigned int i = 0; i < DECIMAL_BITS; ++i) {
    if (check_decimal_bit(b, i) == 1) {
      errors__(dec_shift_left(a, i, &buffer), &er);
      if (er == 0) {
        errors__(sum_mantissa(&result_buff, &buffer, &result_buff), &er);
      }
    }
  }
  if (er == 0) {
    copy_mantissa(&result_buff, result);
  }
  return er;
}

int div_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result,
                 h_decimal* mod_dec) {
  h_decimal div_buff, mod_buff, one;
  set_decimal_empty(&div_buff);
  set_decimal_empty(&mod_buff);
  set_decimal_one(&one);

  unsigned int index = msb_index(a);
  for (int i = index; i >= 0; --i) {
    bit_shift_left(&mod_buff, 1);
    if (check_decimal_bit(a, i) == 1) {
      dec_or(&mod_buff, &one, &mod_buff);
    }

    bit_shift_left(&div_buff, 1);
    if (is_less_mantissa(&mod_buff, b) == 0) {
      dec_or(&div_buff, &one, &div_buff);
      sub_mantissa(&mod_buff, b, &mod_buff);
    }
  }
  if (result != NULL) {
    copy_mantissa(&div_buff, result);
  }
  if (mod_dec != NULL) {
    copy_mantissa(&mod_buff, mod_dec);
  }
  return 0;
}

int h_add(h_decimal a, h_decimal b, h_decimal* result) {
  if (result == NULL) return ERR_STANDART;
  int er = 0;
  if (is_equal_zero(&a) == 1 && is_equal_zero(&b) == 1) {
    set_decimal_empty(result);
  } else {
    big_decimal a_bd, b_bd, result_bd;
    decimal_to_bd(&a, &a_bd);
    decimal_to_bd(&b, &b_bd);
    set_decimal_empty_bd(&result_bd);

    errors__(align_scales(&a_bd, &b_bd), &er);
    result_bd.exp = a_bd.exp;

    if (a_bd.sign == b_bd.sign) {
      errors__(sum_mantissa_bd(&a_bd, &b_bd, &result_bd), &er);
      result_bd.sign = a_bd.sign;

    } else {
      if (is_less_mantissa_bd(&b_bd, &a_bd)) {
        errors__(sub_mantissa_bd(&a_bd, &b_bd, &result_bd), &er);
        result_bd.sign = a_bd.sign;
      } else {
        errors__(sub_mantissa_bd(&b_bd, &a_bd, &result_bd), &er);
        result_bd.sign = b_bd.sign;
      }
    }
    if (er == 0) {
      errors__(reduce_scale_to_decimal_bd(&result_bd, result, bank_decision),
               &er);
    }
  }
  return er;
}

int h_sub(h_decimal a, h_decimal b, h_decimal* result) {
  int er = 0;
  h_negate(b, &b);
  errors__(h_add(a, b, result), &er);
  return er;
}

int h_mul(h_decimal a, const h_decimal b, h_decimal* result) {
  int er = 0;
  big_decimal a_bd, b_bd, result_bd;
  decimal_to_bd(&a, &a_bd);
  decimal_to_bd(&b, &b_bd);
  set_decimal_empty_bd(&result_bd);

  result_bd.exp = a_bd.exp + b_bd.exp;
  result_bd.sign =
      a_bd.sign == b_bd.sign ? DECIMAL_SIGN_PLUS_VAL : DECIMAL_SIGN_MINUS_VAL;

  errors__(mult_mantissa_bd(&a_bd, &b_bd, &result_bd), &er);
  if (er == 0) {
    errors__(reduce_scale_to_decimal_bd(&result_bd, result, bank_decision),
             &er);
  }
  return er;
}

int h_div(h_decimal a, h_decimal b, h_decimal* result) {
  int er = 0;
  if (is_equal_zero(&b) == 1) {
    errors__(ERR_ZERO_DIV, &er);

  } else if (is_equal_zero(&a) == 1) {
    set_decimal_empty(result);
  } else {
    big_decimal a_bd, b_bd, result_bd, mod_bd, ten, buffer;
    decimal_to_bd(&a, &a_bd);
    decimal_to_bd(&b, &b_bd);
    set_decimal_empty_bd(&result_bd);
    set_decimal_empty_bd(&mod_bd);
    set_decimal_empty_bd(&buffer);
    set_decimal_ten_bd(&ten);

    errors__(align_scales(&a_bd, &b_bd), &er);
    result_bd.sign =
        a_bd.sign == b_bd.sign ? DECIMAL_SIGN_PLUS_VAL : DECIMAL_SIGN_MINUS_VAL;
    int flag = 0;

    errors__(div_mantissa_bd(&a_bd, &b_bd, &result_bd, &mod_bd), &er);

    unsigned int exp = 0;
    for (unsigned int i = 0; i < DECIMAL_EXP_MAX_VAL + 1 &&
                             is_equal_zero_bd(&mod_bd) == 0 && flag == 0;
         ++i) {
      errors__(mult_mantissa_bd(&result_bd, &ten, &result_bd), &flag);
      errors__(mult_mantissa_bd(&mod_bd, &ten, &mod_bd), &flag);
      errors__(div_mantissa_bd(&mod_bd, &b_bd, &buffer, &mod_bd), &flag);
      errors__(sum_mantissa_bd(&result_bd, &buffer, &result_bd), &flag);
      exp += flag == 0 ? 1 : 0;
    }

    if (er == 0) {
      result_bd.exp = exp;
      errors__(reduce_scale_to_decimal_bd(&result_bd, result, bank_decision),
               &er);
    }
  }
  return er;
}

int sum_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  int er = 0;
  unsigned int carry_last = 0;
  big_decimal result_buff;
  set_decimal_empty_bd(&result_buff);
  for (unsigned int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
    long unsigned int buffer =
        (long unsigned int)a->bits[i] + b->bits[i] +
        carry_last;  // надо привести хоть один операнд к ulong, чтобы
                     // дальнейшие вычисления не обрезались автоматически

    result_buff.bits[i] = (unsigned int)buffer;
    carry_last = (unsigned int)(buffer >> UINT_BITS);
  }
  if (carry_last == 0) {
    copy_mantissa_bd(&result_buff, result);
  } else {
    errors__(ERR_STANDART, &er);
  }
  return er;
}

int sub_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  int er = 0;
  if (is_less_mantissa_bd(a, b) == 1) {
    errors__(ERR_STANDART, &er);
  } else if (is_equal_mantissa_bd(a, b)) {
    set_decimal_empty_bd(result);
  } else {
    unsigned int carry_last = 0;

    big_decimal result_buff;
    set_decimal_empty_bd(&result_buff);
    for (unsigned int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
      long int buffer =
          (long int)a->bits[i] - b->bits[i] -
          carry_last;  // надо привести хоть один операнд к ulong, чтобы
                       // дальнейшие вычисления не обрезались автоматически
      result_buff.bits[i] = (unsigned int)buffer;
      carry_last = (buffer >> UINT_BITS) != 0 ? 1 : 0;
    }
    copy_mantissa_bd(&result_buff, result);
  }
  return er;
}

int mult_mantissa_bd(const big_decimal* a, const big_decimal* b,
                     big_decimal* result) {
  int er = 0;
  big_decimal buffer, result_buff;
  set_decimal_empty_bd(&buffer);
  set_decimal_empty_bd(&result_buff);
  for (unsigned int i = 0; i < BIG_DECIMAL_BITS; ++i) {
    if (check_decimal_bit_bd(b, i) == 1) {
      errors__(dec_shift_left_bd(a, i, &buffer), &er);
      if (er == 0) {
        errors__(sum_mantissa_bd(&result_buff, &buffer, &result_buff), &er);
      }
    }
  }
  if (er == 0) {
    copy_mantissa_bd(&result_buff, result);
  }
  return er;
}

int div_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result, big_decimal* mod_dec) {
  int er = 0;
  if (is_equal_zero_bd(b) == 1) {
    errors__(ERR_STANDART, &er);
  } else {
    big_decimal div_buff, mod_buff, one;
    set_decimal_empty_bd(&div_buff);
    set_decimal_empty_bd(&mod_buff);
    set_decimal_one_bd(&one);

    unsigned int index = msb_index_bd(a);
    for (int i = index; i >= 0 && er == 0; --i) {
      errors__(bit_shift_left_bd(&mod_buff, 1), &er);
      if (check_decimal_bit_bd(a, i) == 1) {
        dec_or_bd(&mod_buff, &one, &mod_buff);
      }

      errors__(bit_shift_left_bd(&div_buff, 1), &er);
      if (is_less_mantissa_bd(&mod_buff, b) == 0) {
        dec_or_bd(&div_buff, &one, &div_buff);
        errors__(sub_mantissa_bd(&mod_buff, b, &mod_buff), &er);
      }
    }
    if (er == 0) {
      if (result != NULL) {
        copy_mantissa_bd(&div_buff, result);
      }
      if (mod_dec != NULL) {
        copy_mantissa_bd(&mod_buff, mod_dec);
      }
    }
  }
  return er;
}

int long_div_to_fit_mantissa_exp(const big_decimal* a, const big_decimal* b,
                                 big_decimal* result) {
  int er = 0;
  big_decimal result_buff, mod_bd, ten, buffer;
  set_decimal_ten_bd(&ten);
  set_decimal_empty_bd(&result_buff);
  set_decimal_empty_bd(&mod_bd);
  set_decimal_empty_bd(&buffer);

  errors__(div_mantissa_bd(a, b, &result_buff, &mod_bd), &er);

  unsigned int exp = 0;
  int flag = 0;
  for (unsigned int i = 0; i < DECIMAL_EXP_MAX_VAL + 1 &&
                           is_equal_zero_bd(&mod_bd) == 0 && flag == 0;
       ++i) {
    errors__(mult_mantissa_bd(&result_buff, &ten, &result_buff), &flag);
    errors__(mult_mantissa_bd(&mod_bd, &ten, &mod_bd), &flag);
    errors__(div_mantissa_bd(&mod_bd, b, &buffer, &mod_bd), &flag);
    errors__(sum_mantissa_bd(&result_buff, &buffer, &result_buff), &flag);
    exp += flag == 0 ? 1 : 0;
  }

  if (er == 0) {
    copy_mantissa_bd(&result_buff, result);
    result->exp = exp;
  }
  return er;
}
