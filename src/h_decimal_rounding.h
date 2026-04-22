#ifndef h_DECIMAL_ROUNDING_H
#define h_DECIMAL_ROUNDING_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

int h_floor(h_decimal value, h_decimal* result);
int h_round(h_decimal value, h_decimal* result);
int h_truncate(h_decimal value, h_decimal* result);
int h_negate(h_decimal value, h_decimal* result);

int round_decimal_to(h_decimal* x, int scale, h_decimal* result,
                     int (*floor_func)(h_decimal*, unsigned int));

int normalize(const h_decimal* x, h_decimal* result);
int floor_decision(h_decimal* x, unsigned int mod_int);
int round_decision(h_decimal* x, unsigned int mod_int);
int bank_decision(h_decimal* x, unsigned int mod_int);
int truncate_decision(h_decimal* x, unsigned int mod_int);

int round_decimal_to_bd(big_decimal* x, int scale, big_decimal* result,
                        int (*floor_func)(big_decimal*, unsigned int));
unsigned int count_significant_digits_bd(const big_decimal* x);

int round_decision_bd(big_decimal* x, unsigned int mod_int);
int bank_decision_bd(big_decimal* x, unsigned int mod_int);
int truncate_decision_bd(big_decimal* x, unsigned int mod_int);
int floor_decision_bd(big_decimal* x, unsigned int mod_int);

#endif /* h_DECIMAL_ROUNDING_H */
