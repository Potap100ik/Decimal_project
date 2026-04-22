#ifndef h_DECIMAL_BIT_LOGIC_H
#define h_DECIMAL_BIT_LOGIC_H

#include "h_decimal.h"
#include "h_decimal_internal.h"

// проверка конктерного бита внутри long int
int check_bit(unsigned long int x, unsigned int index);

// установка 0 по индексу в unsigned int
int bit_set_0(unsigned int* x, unsigned int index);
// установка 1 по индексу в unsigned int
int bit_set_1(unsigned int* x, unsigned int index);

// проверка конкретного бита внутри decimal
int check_decimal_bit(const h_decimal* x, unsigned int index);

// сдвиг единицы внутри decimal на индекс (аналог 2^i)
int shift_one(h_decimal* buffer, unsigned int index);

// побитовый & для decimal
int dec_and(const h_decimal* a, const h_decimal* b, h_decimal* result);
// побитовый | для decimal
int dec_or(const h_decimal* a, const h_decimal* b, h_decimal* result);
// побитовый ~ для decimal
int dec_not(const h_decimal* x, h_decimal* result);
// сдвиг влево всего decimal на индекс (аналог <<)
int dec_shift_left(const h_decimal* x, unsigned int shift, h_decimal* buffer);
// сдвиг вправо всего decimal на индекс (аналог >>)
int dec_shift_right(const h_decimal* x, unsigned int shift, h_decimal* buffer);

// вспомогательные функции для реализации сдвига влево/вправо в decimal

// сдвиг на несколько разрядов - перенос значений разрядов и зануление
int word_shift_left(h_decimal* x, unsigned int words);

// сдвиг внутри разрядов
int bit_shift_left(h_decimal* x, unsigned int shift);

// сдвиг на несколько разрядов - перенос значений разрядов и очищение
// (зануление)
int word_shift_right(h_decimal* x, unsigned int words);
// сдвиг внутри разрядов
int bit_shift_right(h_decimal* x, unsigned int shift);

int check_decimal_bit_bd(const big_decimal* x, unsigned int index);
int shift_one_bd(big_decimal* x, unsigned int index);
int dec_shift_left_bd(const big_decimal* x, unsigned int shift,
                      big_decimal* result);
int word_shift_left_bd(big_decimal* x, unsigned int words);
int bit_shift_left_bd(big_decimal* x, unsigned int shift);

int dec_and_bd(const big_decimal* a, const big_decimal* b, big_decimal* result);

int dec_or_bd(const big_decimal* a, const big_decimal* b, big_decimal* result);

int bit_shift_right_bd(big_decimal* x, unsigned int shift);

#endif /* h_DECIMAL_BIT_LOGIC_H */
