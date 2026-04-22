#ifndef h_DECIMAL_COMPARE_H
#define h_DECIMAL_COMPARE_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

// равенство мантисс
int is_equal_mantissa(const h_decimal* a, const h_decimal* b);
// сравнение мантисс a > b
int is_more_mantissa(const h_decimal* a, const h_decimal* b);
// сравнение мантисс a < b
int is_less_mantissa(const h_decimal* a, const h_decimal* b);

// проверка на равенство всех параметров числа decimal нулю (mantissa, sign,
// exp)
int is_empty(const h_decimal* x);
// мантисса равна нулю
int is_equal_zero(const h_decimal* x);

// сравнение числа decimal a < b (с учетом знака, степени)
int h_is_less(h_decimal a, h_decimal b);
// сравнение числа decimal a <= b (с учетом знака, степени)
int h_is_less_or_equal(h_decimal a, h_decimal b);
// сравнение числа decimal a > b (с учетом знака, степени)
int h_is_greater(h_decimal a, h_decimal b);
// сравнение числа decimal a >= b (с учетом знака, степени)
int h_is_greater_or_equal(h_decimal a, h_decimal b);
// проверка равенства decimal a == b (с учетом знака, степени)
int h_is_equal(h_decimal a, h_decimal b);
// прооверка неравенства decimal a != b (с учетом знака, степени)
int h_is_not_equal(h_decimal a, h_decimal b);

// проверка равенства мантисс big decimal
int is_equal_mantissa_bd(const big_decimal* a, const big_decimal* b);
int is_equal_zero_bd(const big_decimal* x);

int is_equal_mantissa_bd(const big_decimal* a, const big_decimal* b);
int is_less_mantissa_bd(const big_decimal* a, const big_decimal* b);
int is_more_mantissa_bd(const big_decimal* a, const big_decimal* b);

#endif /* h_DECIMAL_COMPARE_H */
