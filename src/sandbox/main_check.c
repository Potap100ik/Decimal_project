#include "../h_decimal.h"
#include "../h_decimal_print.h"
#include "stdio.h"

void print_res(long long int * resI, long double *resF, h_decimal * resD, const char * msg){

  printf("\nmsg: [\033[32m%s\033[0m]\n", msg);
  print_decimal(resD, 0, "", 0);
  printf("resI  = \t[%lld]\n", *resI);
  printf("resF  = \t[%Lf]\n", *resF);
}


int main(void) {
  /*
  example:
  trying to return 1st value of every type: int, float, decimal
  (2^32) * (2^32) / 7 / (2^32) * 7
  */

  h_decimal dec1, resD;
  int int1 = 2147483647;
  float fl1 = int1;

  // long containers
  long long int resI = 0;
  long double resF = 0.0;

  h_from_int_to_decimal(int1, &dec1);

  print_decimal(&dec1, 0, "dec1 before mul", 0);
  printf("int1 = \t\t[%d]\n", int1);
  printf("fl1  = \t\t[%lf]\n", fl1);


  h_mul(dec1, dec1, &resD);
  resI = (long long int)int1 * int1;
  resF    = fl1 * fl1;
  print_res(&resI, &resF, &resD, "mul 2^32");

  h_decimal dec_s;
  int seven = 7;
  h_from_int_to_decimal(seven, &dec_s);


  h_div(resD, dec_s, &resD);
  resI /= seven;
  resF /= seven;
  print_res(&resI, &resF, &resD, "div by 7");


  h_div(resD, dec1, &resD);
  resI /= int1;
  resF /= fl1;
  print_res(&resI, &resF, &resD, "div by 2^32");

  h_mul(resD, dec_s, &resD);
  resI *= seven;
  resF *= seven;
  print_res(&resI, &resF, &resD, "mul 7");

  h_sub(resD, dec1, &resD);
  resI -= int1;
  resF -= fl1;
  print_res(&resI, &resF, &resD, "difference with 1st values");




  return 0;
}
