#include <stdio.h>
#include <stdlib.h>

#define NMAX 100
#define TMAX 1024
#define TABLE_SIZE 256

void table(int* sdvig, unsigned char* pattern, int size_pattern);
int input_pattern(unsigned char* pattern, int* size_pattern, FILE* f);
void search(unsigned char* text, unsigned char* pattern, int size_pattern,
            int delete_count,
            int working_index);
void text_rewrite(unsigned char* text, int* working_index, int* delete_count,
                  int size_pattern, int* sdvig, int* size_text, FILE* f);


int main() {
  FILE* f = fopen("in.txt", "r");
  unsigned char pattern[NMAX];
  int size_pattern = 0;
  int size_text = 0;
  if (input_pattern(pattern, &size_pattern, f)) {
    unsigned char text[TMAX];
    int sdvig[TABLE_SIZE];
    table(sdvig, pattern, size_pattern);
    size_text = fread(text, sizeof(unsigned char), TMAX, f);
    int delete_count = 0;
    int working_index = size_pattern - 1;
    while (working_index < size_text) {
      search(text, pattern, size_pattern, delete_count, working_index);
      if (working_index + sdvig[text[working_index]] >= size_text) {
        text_rewrite(text, &working_index, &delete_count, size_pattern,
                          sdvig, &size_text, f);
      } else {
        working_index += sdvig[text[working_index]];
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


void table(int* sdvig, unsigned char* pattern, int size_pattern) {
  for (int i = 0; i < TABLE_SIZE; ++i) {
    sdvig[i] = size_pattern;
  }
  int j = 1;
  for (int i = 1; i < size_pattern; ++i) {
    if (sdvig[*(pattern + size_pattern - i - 1)] == size_pattern) {
      sdvig[*(pattern + size_pattern - i - 1)] = j;
    }
    j++;
  }
}

void search(unsigned char* text, unsigned char* pattern, int size_pattern,
            int delete_count, int working_index) {
  int index = working_index;
  int index_pattern = size_pattern - 1;
  for (int i = 0; i < size_pattern; ++i) {
    printf("%d ", index + delete_count + 1);
    if (text[index] == pattern[index_pattern]) {
      index--;
      index_pattern--;
    } else {
      break;
    }
  }
}

void text_rewrite(unsigned char* text, int *working_index, int *delete_count, int size_pattern, int *sdvig, int *size_text, FILE *f) {
  int copy_count = size_pattern - sdvig[text[*working_index]];
  for (int i = 0; i < copy_count; ++i) {
    text[i] = text[*working_index + i - copy_count + 1];
  }
  *delete_count += *size_text - copy_count;
  *size_text = copy_count + fread(text + copy_count, sizeof(unsigned char), TMAX - copy_count, f);
  *working_index = size_pattern - 1;
}
