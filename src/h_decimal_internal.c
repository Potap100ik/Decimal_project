#include "h_decimal_internal.h"

#include <stdlib.h>

#include "h_decimal_arithmetic.h"
#include "h_decimal_bit_logic.h"
#include "h_decimal_compare.h"

int get_exp(const h_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  unsigned int mask = 1,
               mask_degree = DECIMAL_EXP_INDEX_END - DECIMAL_EXP_INDEX_START;

  mask = 2 << mask_degree;
  return (x->bits[DECIMAL_EXP_SIGN_INDEX] >> DECIMAL_EXP_INDEX_START) &
         (mask - 1);
}

int get_sign(const h_decimal* x) {
  return check_bit(x->bits[DECIMAL_EXP_SIGN_INDEX], DECIMAL_SIGN_INDEX);
}

int set_exp(h_decimal* x, int exp) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  if (exp > DECIMAL_EXP_MAX_VAL)
    errors__(ERR_OVERFLOW, &er);
  else if (exp < DECIMAL_EXP_MIN_VAL) {
    errors__(ERR_OVERFLOW, &er);
  } else {
    unsigned int mask_degree =
        DECIMAL_EXP_INDEX_END - DECIMAL_EXP_INDEX_START + 1;

    for (unsigned int i = 0; i < mask_degree; ++i) {
      if (check_bit(exp, i) == 0) {
        bit_set_0(&(x->bits[DECIMAL_EXP_SIGN_INDEX]),
                  DECIMAL_EXP_INDEX_START + i);
      } else {
        bit_set_1(&(x->bits[DECIMAL_EXP_SIGN_INDEX]),
                  DECIMAL_EXP_INDEX_START + i);
      }
    }
  }
  return er;
}

/*
плюс:   0
минус:  1
разная логика установки бита для знака
*/
int set_sign(h_decimal* x, int sign) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;

  if (sign == DECIMAL_SIGN_PLUS_VAL || sign == DECIMAL_SIGN_MINUS_VAL) {
    if (sign == 0) {
      bit_set_0(&(x->bits[DECIMAL_EXP_SIGN_INDEX]), DECIMAL_SIGN_INDEX);
    } else if (sign == 1) {
      bit_set_1(&(x->bits[DECIMAL_EXP_SIGN_INDEX]), DECIMAL_SIGN_INDEX);
    } else {
      errors__(ERR_STANDART, &er);
    }
  } else {
    errors__(ERR_STANDART, &er);
  }
  return er;
}

int set_decimal_mantissa(h_decimal* x, unsigned int x2, unsigned int x1,
                         unsigned int x0) {
  if (x == NULL) return ERR_STANDART;
  x->bits[0] = x0;
  x->bits[1] = x1;
  x->bits[2] = x2;
  return 0;
}

int set_decimal_value(h_decimal* x, unsigned int x2, unsigned int x1,
                      unsigned int x0, char sign, unsigned int exp) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  set_decimal_mantissa(x, x2, x1, x0);
  if (sign == '-' || sign == DECIMAL_SIGN_MINUS_VAL) {
    errors__(set_sign(x, DECIMAL_SIGN_MINUS_VAL), &er);
  } else if (sign == '+' || sign == DECIMAL_SIGN_PLUS_VAL) {
    errors__(set_sign(x, DECIMAL_SIGN_PLUS_VAL), &er);
  } else {
    errors__(ERR_STANDART, &er);
  }
  errors__(set_exp(x, exp), &er);
  return er;
}

int copy_decimal(const h_decimal* x, h_decimal* target) {
  if (x == NULL || target == NULL) return ERR_STANDART;
  if (x != target) {
    for (int i = 0; i < DECIMAL_PARTS; ++i) {
      target->bits[i] = x->bits[i];
    }
  }
  return 0;
}

int copy_mantissa(const h_decimal* x, h_decimal* target) {
  if (x == NULL || target == NULL) return ERR_STANDART;
  if (x != target) {
    for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
      target->bits[i] = x->bits[i];
    }
  }
  return 0;
}

void set_decimal_empty(h_decimal* x) {
  for (int i = 0; i < DECIMAL_PARTS; ++i) {
    x->bits[i] = 0;
  }
}

void set_decimal_one(h_decimal* x) {
  set_decimal_empty(x);
  set_decimal_mantissa(x, 0, 0, 1);
}

void set_decimal_ten(h_decimal* x) {
  set_decimal_empty(x);
  set_decimal_mantissa(x, 0, 0, 10);
}

int msb_index(const h_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int index = -1;
  if (is_equal_zero(x) != 1) {
    index = 0;
    h_decimal buff;
    int flag_null = copy_decimal(x, &buff);
    for (unsigned int i = 0; i < DECIMAL_BITS && flag_null == 0; ++i) {
      bit_shift_right(&buff, 1);
      if ((flag_null = is_equal_zero(&buff)) != 1) {
        ++index;
      }
    }
  }
  return index;
}

unsigned int count_significant_digits(const h_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int counter = 0;
  h_decimal buffer, ten;
  copy_decimal(x, &buffer);
  set_decimal_ten(&ten);
  while (!is_equal_zero(&buffer)) {
    div_mantissa(&buffer, &ten, &buffer, NULL);
    counter++;
  }
  return counter;
}

void errors__(int func_return, int* err_container) {
  if (err_container != NULL)
    *err_container = *err_container == 0 ? func_return : *err_container;
}

void set_decimal_empty_bd(big_decimal* x) {
  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
    x->bits[i] = 0;
  }
  x->sign = 0;
  x->exp = 0;
}

int copy_decimal_bd(const big_decimal* x, big_decimal* target) {
  if (x == NULL || target == NULL) return ERR_STANDART;
  if (x != target) {
    for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
      target->bits[i] = x->bits[i];
    }
  }
  target->sign = x->sign;
  target->exp = x->exp;
  return 0;
}

int set_decimal_mantissa_bd(big_decimal* x, unsigned int x5, unsigned int x4,
                            unsigned int x3, unsigned int x2, unsigned int x1,
                            unsigned int x0) {
  if (x == NULL) return ERR_STANDART;
  x->bits[0] = x0;
  x->bits[1] = x1;
  x->bits[2] = x2;
  x->bits[3] = x3;
  x->bits[4] = x4;
  x->bits[5] = x5;
  return 0;
}
int set_decimal_value_bd(big_decimal* x, unsigned int x5, unsigned int x4,
                         unsigned int x3, unsigned int x2, unsigned int x1,
                         unsigned int x0, char sign, unsigned int exp) {
  if (x == NULL) return ERR_STANDART;
  int er = 0;
  set_decimal_mantissa_bd(x, x5, x4, x3, x2, x1, x0);
  if (sign == '-' || sign == DECIMAL_SIGN_MINUS_VAL) {
    x->sign = DECIMAL_SIGN_MINUS_VAL;
  } else if (sign == '+' || sign == DECIMAL_SIGN_PLUS_VAL) {
    x->sign = DECIMAL_SIGN_PLUS_VAL;
  } else {
    errors__(ERR_STANDART, &er);
  }
  x->exp = exp;
  return er;
}

void set_decimal_one_bd(big_decimal* x) {
  set_decimal_empty_bd(x);
  set_decimal_mantissa_bd(x, 0, 0, 0, 0, 0, 1);
}

int msb_index_bd(const big_decimal* x) {
  if (x == NULL) return ERR_STANDART;
  int index = -1;
  if (is_equal_zero_bd(x) != 1) {
    index = 0;
    big_decimal buff;
    int flag_null = copy_decimal_bd(x, &buff);
    for (unsigned int i = 0; i < BIG_DECIMAL_BITS && flag_null == 0; ++i) {
      bit_shift_right_bd(&buff, 1);
      if ((flag_null = is_equal_zero_bd(&buff)) != 1) {
        ++index;
      }
    }
  }
  return index;
}

void set_decimal_ten_bd(big_decimal* x) {
  set_decimal_empty_bd(x);
  set_decimal_mantissa_bd(x, 0, 0, 0, 0, 0, 10);
}

int copy_mantissa_bd(const big_decimal* x, big_decimal* target) {
  if (x == NULL || target == NULL) return ERR_STANDART;
  if (x != target) {
    for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
      target->bits[i] = x->bits[i];
    }
  }
  return 0;
}
