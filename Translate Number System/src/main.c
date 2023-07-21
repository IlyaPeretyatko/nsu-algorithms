#include <stdio.h>

#define NMAX 13

#include "foo.h"

int main() {
  int b1, b2;
  int dot = 0;
  int size_int = 0;
  int size_float = 0;
  double ten;
  if (input(&b1, &b2)) {
    char number[NMAX];
    input_number(&dot, &size_int, &size_float, number);
    if (check_number(b1, &dot, &size_int, &size_float, number)) {
      ten = to_value_number_in_ten(number, dot, size_int, size_float, b1);
      to_value_number_in_b2(&ten, dot, b2);
    } else {
      printf("bad input");
    }
  } else {
    printf("bad input");
  }
}
