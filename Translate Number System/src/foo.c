#include <math.h>
#include <stdio.h>

#define IMAX 100

int input(int* b1, int* b2) {
  int correct = 1;
  char check;
  if (!(scanf("%d %d%c", b1, b2, &check) == 3 && check == '\n')) {
    correct = 0;
  }
  if (correct) {
    if (*b1 > 16 || *b1 < 2) {
      correct = 0;
    }
    if (*b2 > 16 || *b2 < 2) {
      correct = 0;
    }
  }
  return correct;
}

void input_number(int* dot, int* size_int, int* size_float, char* number) {
  char input;
  while (*size_int + *size_float < 12) {
    if (scanf("%c", &input) == 1) {
      if (input == '\n') {
        break;
      } else if (*dot == 0) {
        number[*size_int] = input;
        *size_int += 1;
        if (input == '.') {
          *dot = 1;
          *size_int -= 1;
        }
      } else {
        number[*size_int + 1 + *size_float] = input;
        *size_float += 1;
      }
    }
  }
}

int range(int j, int b1, char* number) {
  int correct = 0;
  if ((number[j] < '0' || number[j] >= b1 + '0') && b1 <= 10) {
    correct = 1;
  } else if (b1 <= 16 && b1 > 10 &&
             (number[j] < '0' || (number[j] > '9' && number[j] < 'A') ||
              (number[j] > b1 + 'A' - 11 && number[j] < 'a') ||
              number[j] > b1 + 'a' - 11)) {
    correct = 1;
  }
  return correct;
}

int check_number(int b1, int* dot, int* size_int, int* size_float,
                 char* number) {
  int correct = 1;
  if ((*size_int == 0 && *dot == 1) || (*size_float == 0 && *dot == 1)) {
    correct = 0;
  } else {
    for (int i = 0; i < *size_int; ++i) {
      if (range(i, b1, number)) {
        correct = 0;
      }
    }
  }
  if (correct) {
    for (int i = 0; i < *size_float; ++i) {
      if (range(*size_int + i + 1, b1, number)) {
        correct = 0;
      }
    }
  }
  return correct;
}

double to_value_number_in_ten(char* number, int dot, int size_int, int size_float, int b1) {
  double ten = 0;
  int symb;
  for (int i = size_int - 1, j = 0; i != -1; --i, ++j) {
    if (number[j] >= 'a' && number[j] <= 'f') {
      symb = number[j] - 'a' + 10;
    } else if (number[j] >= 'A' && number[j] <= 'F') {
      symb = number[j] - 'A' + 10;
    } else {
      symb = number[j] - '0';
    }
    ten += symb * pow(b1, i);
  }
  if (dot) {
    for (int i = -1, j = size_int + 1; i != -size_float - 1; --i, ++j) {
      if (number[j] >= 'a' && number[j] <= 'f') {
        symb = number[j] - 'a' + 10;
      } else if (number[j] >= 'A' && number[j] <= 'F') {
        symb = number[j] - 'A' + 10;
      } else {
        symb = number[j] - '0';
      }
      ten += symb * pow(b1, i);
    }
  }
  return ten;
}

void output_int(double* ten, long long* output, int b2, int* flag_integer) {
  long long ten_copy = (long long)*ten;
  int size_answer = 0;
  int answer[IMAX];
  if (*ten == 0) {
    printf("0");
  }
  while (ten_copy != 0) {
    *output = ten_copy % b2;
    ten_copy /= b2;
    if (*output >= 10 && *output < 16) {
      answer[size_answer] = (int)*output + 87;
      size_answer++;
    } else {
      answer[size_answer] = (int)*output;
      size_answer++;
    }
    *flag_integer = 1;
  }
  for (int i = 0; i < size_answer; ++i) {
    if (answer[size_answer - 1 - i] >= 10) {
      printf("%c", answer[size_answer - 1 - i]);
    } else {
      printf("%d", answer[size_answer - 1 - i]);
    }
  }
}

void output_float(int dot, int flag_integer, double* ten, long long* output,
                  int b2) {
  if (dot) {
    if (!flag_integer) {
      printf("0");
    }
    printf(".");
    double output_2 = *ten - (long long)*ten;
    int i = 0;
    double integer;
    while (i < 12) {
      output_2 *= b2;
      *output = (int)output_2;
      if (*output >= 10 && *output < 16) {
        printf("%c", (int)*output + 87);
      } else {
        printf("%lld", *output);
      }
      output_2 = modf(output_2, &integer);
      i++;
    }
  }
}

void to_value_number_in_b2(double* ten, int dot, int b2) {
  long long output;
  int flag_integer = 0;
  output_int(ten, &output, b2, &flag_integer);
  output_float(dot, flag_integer, ten, &output, b2);
}
