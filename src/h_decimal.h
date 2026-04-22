#ifndef h_DECIMAL_H
#define h_DECIMAL_H

#include <limits.h>
#include <stdint.h>

// --- error constants ---

#define ERR_PLUS_INF 1
#define ERR_MINUS_INF 2
#define ERR_ZERO_DIV 3
#define ERR_CONVERT 1

// --- не должны совпадать с вышеуказанными

#define ERR_STANDART -1
#define ERR_OVERFLOW -2

// количество разрядов в decimal
#define DECIMAL_DATA_PARTS 3

// количество разрядов для знака, степени
#define DECIMAL_EXP_SIGN_PARTS 1
#define DECIMAL_PARTS DECIMAL_DATA_PARTS + DECIMAL_EXP_SIGN_PARTS

typedef struct h_decimal {
  uint32_t bits[DECIMAL_PARTS];
} h_decimal;

int h_add(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_sub(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_mul(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_div(h_decimal value_1, h_decimal value_2, h_decimal* result);

int h_is_less(h_decimal, h_decimal);
int h_is_less_or_equal(h_decimal, h_decimal);
int h_is_greater(h_decimal, h_decimal);
int h_is_greater_or_equal(h_decimal, h_decimal);
int h_is_equal(h_decimal, h_decimal);
int h_is_not_equal(h_decimal, h_decimal);

int h_from_int_to_decimal(int src, h_decimal* dst);
int h_from_float_to_decimal(float src, h_decimal* dst);
int h_from_decimal_to_int(h_decimal src, int* dst);
int h_from_decimal_to_float(h_decimal src, float* dst);

int h_floor(h_decimal value, h_decimal* result);
int h_round(h_decimal value, h_decimal* result);
int h_truncate(h_decimal value, h_decimal* result);
int h_negate(h_decimal value, h_decimal* result);

#endif /* h_DECIMAL_H */
