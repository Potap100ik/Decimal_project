#ifndef h_DECIMAL_CONVERT_H
#define h_DECIMAL_CONVERT_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

int h_from_int_to_decimal(int src, h_decimal* dst);
int h_from_float_to_decimal(float src, h_decimal* dst);
int h_from_decimal_to_int(h_decimal src, int* dst);
int h_from_decimal_to_float(h_decimal src, float* dst);

int decimal_to_int_mantissa(const h_decimal* x, int* result);

// перенос decimal в big decimal (data, exp, sign)
int decimal_to_bd(const h_decimal* x, big_decimal* result);

// конвертация big decimal в decimal (data, exp, sign)
int bd_to_decimal(const big_decimal* x, h_decimal* result);

#endif /* h_DECIMAL_CONVERT_H */
