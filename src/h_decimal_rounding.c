#include "h_decimal_rounding.h"

#include <stdlib.h>

#include "h_decimal_arithmetic.h"
#include "h_decimal_compare.h"
#include "h_decimal_convert.h"
#include "h_decimal_internal.h"
#include "h_decimal_scale.h"

int h_floor(h_decimal x, h_decimal* result) {
  if (result == NULL) return ERR_STANDART;

  int er = 0;
  errors__(reduce_scale(&x, result, floor_decision), &er);
  return er;
}

int h_round(h_decimal x, h_decimal* result) {
  if (result == NULL) return ERR_STANDART;

  int er = 0;
  errors__(reduce_scale(&x, result, round_decision), &er);
  return er;
}

int h_truncate(h_decimal x, h_decimal* result) {
  if (result == NULL) return ERR_STANDART;

  int er = 0;
  errors__(reduce_scale(&x, result, truncate_decision), &er);
  return er;
}

int h_negate(h_decimal x, h_decimal* result) {
  if (result == NULL) return ERR_STANDART;
  int sign = get_sign(&x) == DECIMAL_SIGN_PLUS_VAL ? DECIMAL_SIGN_MINUS_VAL
                                                   : DECIMAL_SIGN_PLUS_VAL;

  set_sign(&x, sign);
  copy_decimal(&x, result);
  return 0;
}

int round_decimal_to(h_decimal* x, int scale, h_decimal* result,
                     int (*floor_func)(h_decimal*, unsigned int)) {
  if (x == NULL || result == NULL) return ERR_STANDART;
  int er = 0;

  h_decimal buffer, ten, mod_buff;
  copy_decimal(x, &buffer);
  set_decimal_empty(&mod_buff);
  set_decimal_ten(&ten);

  int exp_buffer = get_exp(&buffer);
  int scale_diff = (int)count_significant_digits(&buffer) - scale;
  if (scale > 0) {
    if (scale_diff > 0) {
      for (unsigned int i = 0; i < (unsigned int)scale_diff; ++i) {
        div_mantissa(&buffer, &ten, &buffer, &mod_buff);
        exp_buffer--;
      }
      int mod_int;
      errors__(decimal_to_int_mantissa(&mod_buff, &mod_int), &er);

      if (er == 0) {
        errors__(floor_func(&buffer, (unsigned int)mod_int), &er);
      }
      for (unsigned int i = 0;
           i < (unsigned int)scale_diff && exp_buffer < 0 && er == 0; ++i) {
        errors__(mult_mantissa(&buffer, &ten, &buffer), &er);
        exp_buffer++;
      }
      errors__(set_exp(&buffer, (unsigned int)exp_buffer), &er);
      if (er == 0) {
        copy_decimal(&buffer, x);
      }
    }
  } else {
    errors__(ERR_STANDART, &er);
  }

  if (er == 0) {
    copy_decimal(&buffer, result);
  } else {
    errors__(ERR_STANDART, &er);
  }
  return er;
}

int normalize(const h_decimal* x, h_decimal* result) {
  if (x == NULL || result == NULL) return ERR_STANDART;
  h_decimal buffer, ten, mod_buff;

  copy_decimal(x, &buffer);
  set_decimal_empty(&mod_buff);
  set_decimal_ten(&ten);
  div_mantissa(&buffer, &ten, NULL, &mod_buff);
  unsigned int exp = get_exp(&buffer);

  while (exp > 0 && is_equal_zero(&mod_buff)) {
    div_mantissa(&buffer, &ten, &buffer, NULL);
    exp--;

    div_mantissa(&buffer, &ten, NULL, &mod_buff);
  }
  set_exp(&buffer, exp);
  copy_decimal(&buffer, result);
  return 0;
}

int floor_decision(h_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  if (mod_int != 0) {
    h_decimal one;
    set_decimal_one(&one);
    if (get_sign(x) == DECIMAL_SIGN_MINUS_VAL) {
      errors__(sum_mantissa(x, &one, x), &er);
    }
  }
  return er;
}
int round_decision(h_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  h_decimal one;
  set_decimal_one(&one);
  if (mod_int >= 5) {
    errors__(sum_mantissa(x, &one, x), &er);
  }
  return er;
}

int bank_decision(h_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  h_decimal one;
  set_decimal_one(&one);
  if (mod_int > 5) {
    errors__(sum_mantissa(x, &one, x), &er);
  } else if (mod_int == 5) {
    h_decimal mod_buff, ten;
    set_decimal_ten(&ten);
    div_mantissa(x, &ten, NULL, &mod_buff);
    int mod_int_2;
    decimal_to_int_mantissa(&mod_buff, &mod_int_2);
    if (mod_int_2 % 2 != 0) {
      errors__(sum_mantissa(x, &one, x), &er);
    }
  }
  return er;
}

int truncate_decision(h_decimal* x, unsigned int mod_int) {
  (void)mod_int;
  if (x == NULL)
    return ERR_STANDART;

  else {
    h_decimal buffer;
    set_decimal_empty(&buffer);
    copy_decimal(x, &buffer);
    copy_decimal(&buffer, x);
    return 0;
  }
  return 0;
}

int round_decimal_to_bd(big_decimal* x, int scale, big_decimal* result,
                        int (*floor_func)(big_decimal*, unsigned int)) {
  if (x == NULL || result == NULL) return ERR_STANDART;
  int er = 0;

  big_decimal buffer_bd, ten, mod_bd;
  copy_decimal_bd(x, &buffer_bd);
  set_decimal_empty_bd(&mod_bd);
  set_decimal_ten_bd(&ten);

  int exp_buffer = buffer_bd.exp;
  int scale_diff = (int)count_significant_digits_bd(&buffer_bd) - scale;
  if (scale_diff > 0 && scale > 0) {
    for (unsigned int i = 0; i < (unsigned int)scale_diff; ++i) {
      div_mantissa_bd(&buffer_bd, &ten, &buffer_bd, &mod_bd);
      exp_buffer--;
    }
    int mod_int;

    h_decimal mod_dec;
    set_decimal_empty(&mod_dec);
    errors__(bd_to_decimal(&mod_bd, &mod_dec), &er);
    errors__(decimal_to_int_mantissa(&mod_dec, &mod_int), &er);

    if (er == 0) {
      errors__(floor_func(&buffer_bd, (unsigned int)mod_int), &er);
    }
    for (unsigned int i = 0;
         i < (unsigned int)scale_diff && exp_buffer < 0 && er == 0; ++i) {
      errors__(mult_mantissa_bd(&buffer_bd, &ten, &buffer_bd), &er);
      exp_buffer++;
    }
    buffer_bd.exp = exp_buffer;
    if (er == 0) {
      copy_decimal_bd(&buffer_bd, x);
    }
  }

  if (er == 0) {
    copy_decimal_bd(&buffer_bd, result);
  } else {
    errors__(ERR_STANDART, &er);
  }
  return er;
}

unsigned int count_significant_digits_bd(const big_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int counter = 0;
  big_decimal buffer, ten;
  copy_decimal_bd(x, &buffer);
  set_decimal_ten_bd(&ten);
  while (!is_equal_zero_bd(&buffer)) {
    div_mantissa_bd(&buffer, &ten, &buffer, NULL);
    counter++;
  }
  return counter;
}

int floor_decision_bd(big_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  if (mod_int != 0) {
    big_decimal one;
    set_decimal_one_bd(&one);
    if (x->sign == DECIMAL_SIGN_MINUS_VAL) {
      errors__(sum_mantissa_bd(x, &one, x), &er);
    }
  }
  return er;
}
int round_decision_bd(big_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  big_decimal one;
  set_decimal_one_bd(&one);
  if (mod_int >= 5) {
    errors__(sum_mantissa_bd(x, &one, x), &er);
  }
  return er;
}

int bank_decision_bd(big_decimal* x, unsigned int mod_int) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  big_decimal one;
  set_decimal_one_bd(&one);
  if (mod_int > 5) {
    errors__(sum_mantissa_bd(x, &one, x), &er);
  } else if (mod_int == 5) {
    big_decimal mod_buff, ten;
    set_decimal_empty_bd(&mod_buff);
    set_decimal_ten_bd(&ten);
    div_mantissa_bd(x, &ten, NULL, &mod_buff);
    int mod_int_2;

    h_decimal mod_dec;
    set_decimal_empty(&mod_dec);
    bd_to_decimal(&mod_buff, &mod_dec);
    decimal_to_int_mantissa(&mod_dec, &mod_int_2);
    if (mod_int_2 % 2 != 0) {
      errors__(sum_mantissa_bd(x, &one, x), &er);
    }
  }
  return er;
}

int truncate_decision_bd(big_decimal* x, unsigned int mod_int) {
  (void)mod_int;
  if (x == NULL)
    return ERR_STANDART;

  else {
    big_decimal buffer;
    set_decimal_empty_bd(&buffer);
    copy_decimal_bd(x, &buffer);
    copy_decimal_bd(&buffer, x);
    return 0;
  }
  return 0;
}
