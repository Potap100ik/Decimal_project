#include "h_decimal_print.h"

#include <stdio.h>
#include <stdlib.h>

#include "h_decimal_arithmetic.h"
#include "h_decimal_bit_logic.h"
#include "h_decimal_compare.h"
#include "h_decimal_internal.h"

void get_str_int32(int x, char* str) {
  unsigned int len_binary = UINT_BITS;
  char* binary = calloc(len_binary, sizeof(char));  // 1 bit needs 1 char byte
  for (unsigned int i = 0; i < len_binary; i++) {   // 32 iterations
    int is_set = check_bit(x, len_binary - (i + 1));
    binary[i] = is_set != 0 ? '1' : '0';
  }

  for (unsigned int i = 0, j = 0;
       i < INT32_CHAR_BINARY_LEN - 1 && j < len_binary; ++i, ++j) {
    str[i] = binary[j];
    if ((j + 1) % 4 == 0 && j != (len_binary - 1)) {
      str[++i] = ',';
    }
  }
  str[INT32_CHAR_BINARY_LEN - 1] = '\0';
  free(binary);
}

void print_int32(int x) {
  char str[INT32_CHAR_BINARY_LEN];
  get_str_int32(x, str);
  printf("str: [%s]\n", str);
}

void print_int64(long int x) {
  char str[INT32_CHAR_BINARY_LEN];
  get_str_int32((int)(x >> UINT_BITS), str);
  printf("str: [%s]", str);
  get_str_int32((int)x, str);
  printf("[%s]\n", str);
}

void print_decimal(const h_decimal* x, int need_plus, const char* msg,
                   const int mode) {
  char str[DECIMAL_PARTS][INT32_CHAR_BINARY_LEN];
  char str_decimal[DECIMAL_CHAR_LEN];

  get_str_decimal(x, str_decimal, need_plus);
  for (int i = 0; i < DECIMAL_PARTS; ++i) get_str_int32(x->bits[i], str[i]);
  if (mode > 0)
    printf("/////////////////////// [\033[32m%s\033[0m]\n",
           msg != NULL ? msg : "");
  if (mode >= 0)
    printf("decimal: \t\033[33m[\033[0m%s\033[33m] <--\033[0m\n", str_decimal);
  if (mode > 1) {
    printf("decimal: [%s][%s][%s]\n", str[2], str[1], str[0]);
    printf("exp:     [%s]\n", str[3]);
    printf("exp:     [%d]\n", get_exp(x));
    printf("sign:    [%s]\n", get_sign(x) == DECIMAL_SIGN_MINUS_VAL
                                  ? "\033[44m-\033[0m"
                                  : "\033[41m+\033[0m");
  }
}

int get_str_decimal(const h_decimal* x, char* str, int need_plus) {
  h_decimal buffer, mod_buf, ten;
  set_decimal_ten(&ten);
  set_decimal_empty(&mod_buf);
  copy_decimal(x, &buffer);
  int len_decimal = DECIMAL_CHAR_LEN;
  char* digit = calloc(len_decimal, sizeof(char));

  int index = 0;
  int exp_index = get_exp(x);
  while ((is_equal_zero(&buffer) == 0 || exp_index >= 0) &&
         index < len_decimal) {
    div_mantissa(&buffer, &ten, &buffer, &mod_buf);
    digit[index] = (char)(mod_buf.bits[0] + '0');
    index++;
    exp_index--;
    if (exp_index == 0) {
      digit[index++] = CHAR_FLOAT_SEPARATOR;
    }
  }
  digit[index] = get_sign(x) == DECIMAL_SIGN_PLUS_VAL ? '+' : '-';
  if (get_sign(x) == DECIMAL_SIGN_PLUS_VAL) {
    if (need_plus != 0) {
      digit[index] = '+';
    } else {
      index--;
    }
  } else {
    digit[index] = '-';
  }
  int j = 0;
  for (; index >= 0 && j < DECIMAL_CHAR_LEN - 1; --index, ++j) {
    str[j] = digit[index];
  }
  str[j] = '\0';

  free(digit);
  return 0;
}

void print_decimal_bd(const big_decimal* x, int need_plus, const char* msg) {
  char str[BIG_DECIMAL_DATA_PARTS][INT32_CHAR_BINARY_LEN];
  char str_decimal[BIG_DECIMAL_CHAR_LEN];

  // need_plus++;
  get_str_decimal_bd(x, str_decimal, need_plus);
  for (int i = 0; i < BIG_DECIMAL_DATA_PARTS; ++i)
    get_str_int32(x->bits[i], str[i]);
  printf("/////////////////////// [\033[32m%s\033[0m]\n",
         msg != NULL ? msg : "");
  printf("decimal: [%s][%s][%s]\n", str[5], str[4], str[3]);
  printf("decimal: [%s][%s][%s]\n", str[2], str[1], str[0]);
  printf("decimal: \033[33m[\033[0m%s\033[33m] <--\033[0m\n", str_decimal);
  printf("exp:     [%d]\n", x->exp);
  printf("sign:    [%s]\n", x->sign == DECIMAL_SIGN_MINUS_VAL
                                ? "\033[44m-\033[0m"
                                : "\033[41m+\033[0m");

  printf("сравнение конвертации в другие типы (по возможности <stdlib.h>)\n");
  // if (x->exp == 0) {
  //   long l = strtol(str_decimal, NULL, 10);
  //   printf("decimal: [%s]\n", str_decimal);
  //   printf("long:    [%ld]\n", l);
  // } else {
  //   double d = strtod(str_decimal, NULL);
  //   printf("decimal: [%s]\n", str_decimal);
  //   printf("double:  [%.*f]\n", x->exp, d);
  // }
}

int get_str_decimal_bd(const big_decimal* x, char* str, int need_plus) {
  big_decimal buffer, mod_buf, ten;
  set_decimal_ten_bd(&ten);
  set_decimal_empty_bd(&mod_buf);
  copy_decimal_bd(x, &buffer);
  int len_decimal = BIG_DECIMAL_CHAR_LEN;
  char* digit = calloc(len_decimal, sizeof(char));

  int index = 0;
  int exp_index = x->exp;
  int sign = x->sign;
  while ((is_equal_zero_bd(&buffer) == 0 || exp_index >= 0) &&
         index < len_decimal) {
    div_mantissa_bd(&buffer, &ten, &buffer, &mod_buf);
    digit[index] = (char)(mod_buf.bits[0] + '0');
    index++;
    exp_index--;
    if (exp_index == 0) {
      digit[index++] = CHAR_FLOAT_SEPARATOR;
    }
  }

  digit[index] = sign == DECIMAL_SIGN_PLUS_VAL ? '+' : '-';
  if (sign == DECIMAL_SIGN_PLUS_VAL) {
    if (need_plus != 0) {
      digit[index] = '+';
    } else {
      index--;
    }
  } else {
    digit[index] = '-';
  }
  int j = 0;
  for (; index >= 0 && j < BIG_DECIMAL_CHAR_LEN - 1; --index, ++j) {
    str[j] = digit[index];
  }
  str[j] = '\0';

  free(digit);
  return 0;
}