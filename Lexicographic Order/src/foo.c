#include <stdio.h>

void input(char *data, int *size_data) {
  char input;
  while (scanf("%c", &input) == 1 && input != '\n') {
    data[*size_data] = input;
    *size_data += 1;
  }
}

int check_input(char *data, int size_data) {
  int check[10];
  for (int i = 0; i < 10; ++i) {
    check[i] = 0;
  }
  int correct = 1;
  for (int i = 0; i < size_data; ++i) {
    if (data[i] < '0' || data[i] > '9') {
      correct = 0;
      break;
    } else {
      check[data[i] - '0'] += 1;
    }
    if (check[data[i] - '0'] > 1) {
      correct = 0;
      break;
    }
  }
  return correct;
}

void reverse(char *data, int j, int size_data) {
  for (int i = j; i < (j + size_data) / 2; ++i) {
    char temp;
    temp = data[i];
    data[i] = data[size_data + j - i - 1];
    data[size_data + j - i - 1] = temp;
  }
}

void swap(char *data, int max_index, int j_index) {
  char temp = data[max_index];
  data[max_index] = data[j_index];
  data[j_index] = temp;
}

void output(char *data, int size_data) {
  for (int i = 0; i < size_data; ++i) {
    printf("%c", data[i]);
  }
  printf("\n");
}

void permutation(char *data, int size_data, int *input_count) {
  int flag_have = 1;
  while (*input_count != 0 && flag_have) {
    int max_index = -1;
    char max;
    for (int i = 0; i < size_data - 1; ++i) {
      if (data[i] < data[i + 1]) {
        max_index = i;
        max = data[i];
      }
    }
    if (max_index != -1) {
      int j_index = -1;
      for (int i = 0; i < size_data; ++i) {
        if (i != max_index && i > j_index && data[i] > max) {
          j_index = i;
        }
      }
      swap(data, max_index, j_index);
      reverse(data, max_index + 1, size_data);
      output(data, size_data);
      *input_count -= 1;
    } else {
      flag_have = 0;
    }
  }
}

