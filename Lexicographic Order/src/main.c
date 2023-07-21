#include <stdio.h>

#include "foo.h"

#define NMAX 100

int main() {
  int size_data = 0;
  char data[NMAX];
  input(data, &size_data);
  int input_count;
  char check;
  if (!(scanf("%d%c", &input_count, &check) == 2 && check == '\n')) {
    printf("bad input");
    return 0;
  }
  if (!check_input(data, size_data)) {
    printf("bad input");
    return 0;
  }
  permutation(data, size_data, &input_count);
  return 0;
}

