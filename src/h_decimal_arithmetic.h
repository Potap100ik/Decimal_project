#ifndef h_DECIMAL_ARITHMETIC_H
#define h_DECIMAL_ARITHMETIC_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

int sum_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result);
int sub_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result);
int mult_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result);
int div_mantissa(const h_decimal* a, const h_decimal* b, h_decimal* result,
                 h_decimal* mod_dec);

int h_add(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_sub(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_mul(h_decimal value_1, h_decimal value_2, h_decimal* result);
int h_div(h_decimal value_1, h_decimal value_2, h_decimal* result);

// сумма мантисс (с переносом разрядов)
int sum_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result);
// вычитание мантисс a - b (с переносом разрядов)
int sub_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result);
// умножение мантисс a*b (с переносом разрядов)
int mult_mantissa_bd(const big_decimal* a, const big_decimal* b,
                     big_decimal* result);

// деление мантисс a/b = result и a%b = mod_dec
int div_mantissa_bd(const big_decimal* a, const big_decimal* b,
                    big_decimal* result, big_decimal* mod_dec);

// деление до перепонения мантиссы decimal (на один двоичный порядок)
int long_div_to_fit_mantissa_exp(const big_decimal* a, const big_decimal* b,
                                 big_decimal* result);
#endif /* h_DECIMAL_ARITHMETIC_H */
