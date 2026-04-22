#ifndef h_DECIMAL_PRINT_H
#define h_DECIMAL_PRINT_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

void print_int32(int x);
void print_int64(long int x);
void print_decimal(const h_decimal* x, int need_plus, const char* msg,
                   const int mode);
void get_str_int32(int x, char* str);
int get_str_decimal(const h_decimal* x, char* str, int need_plus);

void print_decimal_bd(const big_decimal* x, int need_plus, const char* msg);
int get_str_decimal_bd(const big_decimal* x, char* str, int need_plus);

#endif /* h_DECIMAL_PRINT_H */
