#include <stdio.h>
#include <stdlib.h>

#define NMAX 100
#define TMAX 1024
#define TABLE_SIZE 256

int input_pattern(unsigned char* pattern, int* size_pattern, FILE* f);

void text_rewrite(unsigned char* text, int* working_index, int* delete_count,
                  int size_pattern, int* size_text, FILE* f);
int hash_pattern(unsigned char* pattern, int size_pattern);
void search(unsigned char* text, int h_pattern, int size_pattern,
            int working_index, int delete_count, unsigned char* pattern,
            int* summ, int power_for_shift);
int power(int deg);

int main() {
  FILE* f = fopen("in.txt", "r");
  unsigned char pattern[NMAX];
  int size_pattern = 0;
  if (input_pattern(pattern, &size_pattern, f)) {
    unsigned char text[TMAX];
    int size_text = fread(text, sizeof(unsigned char), TMAX, f);
    int h_pattern = hash_pattern(pattern, size_pattern);
    int power_for_shift = power(size_pattern - 1);
    printf("%d ", h_pattern);
    int delete_count = 0;
    int working_index = size_pattern - 1;
    int summ = 0;
    while (working_index < size_text) {
      search(text, h_pattern, size_pattern, working_index, delete_count,
             pattern, &summ, power_for_shift);
      if (working_index + 1 == size_text) {
        text_rewrite(text, &working_index, &delete_count, size_pattern,
                     &size_text, f);
      } else {
        working_index += 1;
      }
    }

  } else {
    printf("bad input");
  }
  fclose(f);
  return 0;
}

int input_pattern(unsigned char* pattern, int* size_pattern, FILE* f) {
  int correct = 1;
  unsigned char input;
  while (fread(&input, 1, 1, f) == 1 && input != '\n') {
    pattern[*size_pattern] = input;
    *size_pattern += 1;
  }
  if (*size_pattern > 16 || *size_pattern == 0) {
    correct = 0;
  }
  return correct;
}

void text_rewrite(unsigned char* text, int* working_index, int* delete_count,
                  int size_pattern, int* size_text, FILE* f) {
  int copy_count = size_pattern - 1;
  for (int i = 0; i < copy_count; ++i) {
    text[i] = text[*working_index + i - copy_count + 1];
  }

  *delete_count += *size_text - copy_count;
  *size_text =
      copy_count + fread(text + copy_count, sizeof(unsigned char), TMAX - copy_count, f);
  *working_index = size_pattern - 1;
}

int hash_pattern(unsigned char* pattern, int size_pattern) {
  int sum = 0;
  for (int i = 0; i < size_pattern; ++i) {
    sum += (pattern[i] % 3) * power(i);
  }
  return sum;
}

void search(unsigned char* text, int h_pattern, int size_pattern,
            int working_index, int delete_count, unsigned char* pattern,
            int* summ, int power_for_shift) {
  if (working_index == size_pattern - 1) {
    *summ = 0;
    for (int i = 0; i < size_pattern; ++i) {
      *summ += (text[working_index - size_pattern + i + 1] % 3) * power(i);
    }
  } else {
    *summ -= text[working_index - size_pattern] % 3;
    *summ /= 3;
    *summ += (text[working_index] % 3) * power_for_shift;
  }
  if (*summ == h_pattern) {
    for (int i = 0; i < size_pattern; ++i) {
      if (pattern[i] == text[working_index - size_pattern + i + 1]) {
        printf("%d ", working_index - size_pattern + i + 2 + delete_count);
      } else {
        printf("%d ", working_index - size_pattern + i + 2 + delete_count);
        break;
      }
    }
  }
}

int power(int deg) {
  static int result[16];
  result[1] = 0;
  if (result[deg] != 0 && deg > 0) {
    return result[deg];
  } else if (deg == 0) {
    return 1;
  } else {
    result[deg] = 3;
    for (int i = 0; i < deg - 1; ++i) {
      result[deg] *= 3;
    }
    return result[deg];
  }
}

