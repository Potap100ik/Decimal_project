#ifndef h_DECIMAL_SCALE_H
#define h_DECIMAL_SCALE_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

int align_scales(big_decimal* a, big_decimal* b);

int scale_up_to_bd(big_decimal* x, int exp_new);

int reduce_scale(const h_decimal* x, h_decimal* result,
                 int (*floor_func)(h_decimal*, unsigned int));
// преобразование с сохранением максимальной точности
int reduce_scale_to_decimal_bd(const big_decimal* x, h_decimal* result,
                               int (*floor_func)(h_decimal*, unsigned int));

#endif /* h_DECIMAL_SCALE_H */
