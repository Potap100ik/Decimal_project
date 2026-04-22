#include "h_decimal_bit_logic.h"

#include <stdlib.h>

#include "h_decimal_compare.h"
#include "h_decimal_internal.h"

int check_bit(unsigned long int x, unsigned int index) {
  int result;
  if (index < ULONG_BITS)
    result = (x & (1ul << index)) == 0 ? 0 : 1;
  else
    result = ERR_STANDART;
  return result;
}

int bit_set_0(unsigned int* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  *x &= ~(1u << index);
  return 0;
}
int bit_set_1(unsigned int* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  *x |= (1u << index);
  return 0;
}

int check_decimal_bit(const h_decimal* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  h_decimal one, buffer;
  set_decimal_empty(&buffer);
  shift_one(&one, index);
  dec_and(x, &one, &buffer);
  return is_equal_zero(&buffer) ? 0 : 1;
}

int shift_one(h_decimal* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  set_decimal_one(x);
  dec_shift_left(x, index, x);
  return 0;
}

int dec_and(const h_decimal* a, const h_decimal* b, h_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  h_decimal result_buff;
  set_decimal_empty(&result_buff);

  for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
    result_buff.bits[i] = a->bits[i] & b->bits[i];
  }
  copy_decimal(&result_buff, result);
  return 0;
}

int dec_or(const h_decimal* a, const h_decimal* b, h_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  h_decimal result_buff;
  set_decimal_empty(&result_buff);
  for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
    result_buff.bits[i] = a->bits[i] | b->bits[i];
  }
  copy_decimal(&result_buff, result);
  return 0;
}
int dec_not(const h_decimal* x, h_decimal* result) {
  if (x == NULL || result == NULL) return ERR_STANDART;
  h_decimal result_buff;
  set_decimal_empty(&result_buff);
  for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
    result_buff.bits[i] = ~x->bits[i];
  }
  copy_decimal(&result_buff, result);
  return 0;
}

int dec_shift_left(const h_decimal* x, unsigned int shift, h_decimal* result) {
  if (x == NULL || result == NULL) return ERR_STANDART;

  int er = 0;
  if (shift >= DECIMAL_BITS) {
    errors__(ERR_STANDART, &er);
  } else {
    h_decimal result_buff;
    copy_decimal(x, &result_buff);
    unsigned int word_shift = shift / (UINT_BITS),
                 byte_shift = shift % (UINT_BITS);
    errors__(word_shift_left(&result_buff, word_shift), &er);
    errors__(bit_shift_left(&result_buff, byte_shift), &er);
    if (er == 0) {
      copy_decimal(&result_buff, result);
    }
  }
  return er;
}

int dec_shift_right(const h_decimal* x, unsigned int shift, h_decimal* result) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (shift >= DECIMAL_BITS) {
    errors__(ERR_STANDART, &er);
  } else if (shift != 0) {
    h_decimal result_buff;
    copy_decimal(x, &result_buff);
    unsigned int word_shift = (unsigned int)(shift / (UINT_BITS)),
                 byte_shift = (unsigned int)(shift % (UINT_BITS));
    errors__(word_shift_right(&result_buff, word_shift), &er);
    errors__(bit_shift_right(&result_buff, byte_shift), &er);
    if (er == 0) {
      copy_decimal(&result_buff, result);
    }
  } else {
    copy_decimal(x, result);
  }
  return er;
}

int word_shift_left(h_decimal* x, unsigned int words) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (words > DECIMAL_DATA_PARTS - 1) {
    errors__(ERR_STANDART, &er);
  } else if (words != 0) {
    for (int i = DECIMAL_DATA_PARTS - 1; i >= (int)words; --i) {
      x->bits[i] = x->bits[i - words];
    }
    for (unsigned int i = 0; i < words; ++i) {
      x->bits[i] = 0;
    }
  }
  return er;
}

int bit_shift_left(h_decimal* x, unsigned int shift) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (shift >= UINT_BITS)
    errors__(ERR_STANDART, &er);
  else if (shift != 0) {
    unsigned int carry_last = 0;
    unsigned int carry_shift = UINT_BITS - shift;

    for (int i = 0; i < DECIMAL_DATA_PARTS; ++i) {
      unsigned int carry_main = x->bits[i] >> carry_shift;
      x->bits[i] = x->bits[i] << shift;
      x->bits[i] |= carry_last;
      carry_last = carry_main;
    }
  }
  return er;
}
int word_shift_right(h_decimal* x, unsigned int words) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (words > DECIMAL_DATA_PARTS - 1) {
    errors__(ERR_STANDART, &er);
  } else if (words != 0) {
    for (int i = 0; i < (int)(DECIMAL_DATA_PARTS - words); ++i) {
      x->bits[i] = x->bits[i + words];
    }
    for (int i = DECIMAL_DATA_PARTS - 1;
         i > (int)(DECIMAL_DATA_PARTS - words - 1); --i) {
      x->bits[i] = 0;
    }
  }
  return er;
}
int bit_shift_right(h_decimal* x, unsigned int shift) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if ((int)(UINT_BITS - shift) < 0) {
    errors__(ERR_STANDART, &er);
  } else if (shift != 0) {
    unsigned int carry_last = 0;
    unsigned int carry_shift = UINT_BITS - shift;

    for (int i = DECIMAL_DATA_PARTS - 1; i >= 0; --i) {
      unsigned int carry_main = x->bits[i] << carry_shift;
      x->bits[i] = x->bits[i] >> shift;
      x->bits[i] |= carry_last;
      carry_last = carry_main;
    }
  }
  return er;
}

int check_decimal_bit_bd(const big_decimal* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  big_decimal one, buffer;
  set_decimal_empty_bd(&buffer);
  shift_one_bd(&one, index);
  dec_and_bd(x, &one, &buffer);
  return is_equal_zero_bd(&buffer) ? 0 : 1;
}

int shift_one_bd(big_decimal* x, unsigned int index) {
  if (x == NULL) return ERR_STANDART;
  set_decimal_one_bd(x);
  dec_shift_left_bd(x, index, x);
  return 0;
}

int dec_shift_left_bd(const big_decimal* x, unsigned int shift,
                      big_decimal* result) {
  if (x == NULL || result == NULL) return ERR_STANDART;

  int er = 0;
  if (shift >= BIG_DECIMAL_BITS) {
    errors__(ERR_STANDART, &er);
  } else {
    big_decimal result_buff;
    copy_decimal_bd(x, &result_buff);
    unsigned int word_shift = shift / (UINT_BITS),
                 byte_shift = shift % (UINT_BITS);
    errors__(word_shift_left_bd(&result_buff, word_shift), &er);
    errors__(bit_shift_left_bd(&result_buff, byte_shift), &er);
    if (er == 0) {
      copy_decimal_bd(&result_buff, result);
    }
  }
  return er;
}

int word_shift_left_bd(big_decimal* x, unsigned int words) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (words > BIG_DECIMAL_DATA_PARTS - 1) {
    errors__(ERR_STANDART, &er);
  } else if (words != 0) {
    for (int i = BIG_DECIMAL_DATA_PARTS - 1; i >= (int)words; --i) {
      x->bits[i] = x->bits[i - words];
    }
    for (unsigned int i = 0; i < words; ++i) {
      x->bits[i] = 0;
    }
  }
  return er;
}

int bit_shift_left_bd(big_decimal* x, unsigned int shift) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if (shift >= UINT_BITS)
    errors__(ERR_STANDART, &er);
  else if (shift != 0) {
    unsigned int carry_last = 0;
    unsigned int carry_shift = UINT_BITS - shift;

    for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
      unsigned int carry_main = x->bits[i] >> carry_shift;
      x->bits[i] = x->bits[i] << shift;
      x->bits[i] |= carry_last;
      carry_last = carry_main;
    }
  }
  return er;
}

int dec_and_bd(const big_decimal* a, const big_decimal* b,
               big_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  big_decimal result_buff;
  set_decimal_one_bd(&result_buff);

  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
    result_buff.bits[i] = a->bits[i] & b->bits[i];
  }
  copy_decimal_bd(&result_buff, result);
  return 0;
}

int dec_or_bd(const big_decimal* a, const big_decimal* b, big_decimal* result) {
  if (a == NULL || b == NULL || result == NULL) return ERR_STANDART;
  big_decimal result_buff;
  set_decimal_empty_bd(&result_buff);
  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i) {
    result_buff.bits[i] = a->bits[i] | b->bits[i];
  }
  copy_decimal_bd(&result_buff, result);
  return 0;
}

int bit_shift_right_bd(big_decimal* x, unsigned int shift) {
  if (x == NULL) return ERR_STANDART;

  int er = 0;
  if ((int)(UINT_BITS - shift) < 0) {
    errors__(ERR_STANDART, &er);
  } else if (shift != 0) {
    unsigned int carry_last = 0;
    unsigned int carry_shift = UINT_BITS - shift;

    for (int i = BIG_DECIMAL_DATA_PARTS - 1; i >= 0; --i) {
      unsigned int carry_main = x->bits[i] << carry_shift;
      x->bits[i] = x->bits[i] >> shift;
      x->bits[i] |= carry_last;
      carry_last = carry_main;
    }
  }
  return er;
}
