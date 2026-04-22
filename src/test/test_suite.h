#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <check.h>

// #define BUFFER_SIZE 256

Suite* suite_h_arithmetic();
Suite* suite_h_bit_logic();
Suite* suite_h_compare();
Suite* suite_h_convert();
Suite* suite_h_internal();
Suite* suite_h_rounding();
Suite* suite_h_scale();

#endif /* TEST_SUITE_H */
