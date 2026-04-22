#ifndef h_DECIMAL_INTERNAL_H
#define h_DECIMAL_INTERNAL_H

#include <limits.h>
#include <stdint.h>

#include "h_decimal.h"

/*
TODO:
- Унификация связи констант и количества разделов в decimal (сейчас: 3)

*/

// --- error constants ---

// индекс раздела со знаком, степенью
#define DECIMAL_EXP_SIGN_INDEX 3

// --- знаки ---

#define DECIMAL_SIGN_PLUS_VAL 0
#define DECIMAL_SIGN_MINUS_VAL 1

#define DECIMAL_SIGN_INDEX 31

// --- степень ---

#define DECIMAL_EXP_MIN_VAL 0
#define DECIMAL_EXP_MAX_VAL 28

#define DECIMAL_EXP_INDEX_START 16
#define DECIMAL_EXP_INDEX_END 23

// --- мантисса и ее размерности

#define BIG_DECIMAL_DATA_PARTS 6

// --- типы данных и их битовый размер ---

#define CHAR_BITS 8
#define UINT_BITS (sizeof(unsigned int) * CHAR_BITS)    // 32
#define ULONG_BITS (sizeof(unsigned long) * CHAR_BITS)  // 64
#define DECIMAL_BITS UINT_BITS * 3                      // 96
#define BIG_DECIMAL_BITS UINT_BITS * 6                  // 192

// --- конвертация в строку LENGTH---
#define DECIMAL_CHAR_SIGN 1
#define DECIMAL_CHAR_SIGNIFICANT_DIGITS 29
#define DECIMAL_CHAR_FLOAT_SEPARATOR 1
#define CHAR_FLOAT_SEPARATOR '.'
#define DECIMAL_CHAR_THOUSANDS_SEPARATORS 9
#define DECIMAL_CHAR_LEN                                                 \
  DECIMAL_CHAR_SIGN + DECIMAL_CHAR_SIGNIFICANT_DIGITS +                  \
      DECIMAL_CHAR_FLOAT_SEPARATOR + DECIMAL_CHAR_THOUSANDS_SEPARATORS + \
      1  // '\0'
#define BIG_DECIMAL_CHAR_LEN 100

// --- конвертация uint в строку ---
#define INT32_CHAR_HEX_SEPARATORS \
  7  // на 32 бита 8 разрядов по 0000 -> 7 запятых
#define INT32_CHAR_BINARY_LEN INT32_CHAR_HEX_SEPARATORS + UINT_BITS + 1  // '\-'

// мантисса из 6 разрядов (в 2 раза больше текущей); Разряд для знака,
// экспоненты отсутствуют
typedef struct big_decimal {
  uint32_t bits[BIG_DECIMAL_DATA_PARTS];
  unsigned int sign;
  int exp;
} big_decimal;

int get_exp(const h_decimal* x);
int get_sign(const h_decimal* x);
int set_sign(h_decimal* x, int sign);
int set_exp(h_decimal* x, int exp);

// --- support functions --- //
// установка значения для мантиссы
int set_decimal_mantissa(h_decimal* x, unsigned int x2, unsigned int x1,
                         unsigned int x0);

// установка значения для всего числа decimal ('-' == 1, '+' == 0 sign)
int set_decimal_value(h_decimal* x, unsigned int x2, unsigned int x1,
                      unsigned int x0, char sign, unsigned int exp);
// клонирование числа
int copy_decimal(const h_decimal* x, h_decimal* target);

int copy_mantissa(const h_decimal* x, h_decimal* target);
// установка значения 0 для всех полей
void set_decimal_empty(h_decimal* x);

// установка значения 1
void set_decimal_one(h_decimal* x);

// установка значения 10
void set_decimal_ten(h_decimal* x);

// индекс самого старшего бита во всем числе
int msb_index(const h_decimal* x);

// подсчет значащих десятичных цифр в числе
unsigned int count_significant_digits(const h_decimal* x);

// уменьшение кода для обработки ошибок
void errors__(int func_return, int* err_container);

void set_decimal_empty_bd(big_decimal* x);
int copy_decimal_bd(const big_decimal* x, big_decimal* target);
int copy_mantissa_bd(const big_decimal* x, big_decimal* target);

int set_decimal_value_bd(big_decimal* x, unsigned int x5, unsigned int x4,
                         unsigned int x3, unsigned int x2, unsigned int x1,
                         unsigned int x0, char sign, unsigned int exp);
int set_decimal_mantissa_bd(big_decimal* x, unsigned int x5, unsigned int x4,
                            unsigned int x3, unsigned int x2, unsigned int x1,
                            unsigned int x0);

void set_decimal_one_bd(big_decimal* x);
void set_decimal_ten_bd(big_decimal* x);

int msb_index_bd(const big_decimal* x);

#endif /* h_DECIMAL_INTERNAL_H */
