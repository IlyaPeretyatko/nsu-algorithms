#include <stdio.h>
#include <stdlib.h>

void heapSort(int *data, int N);
void swap(int *a, int *b);
void heapify(int *data, int i, int N);

int main() {
  int N;
  if (scanf("%d", &N) == 0 || N < 0 || N > 2000000) {
    printf("bad input");
    return 0;
  }
  int *data = (int *)malloc(N * sizeof(int));
  if (data == NULL) {
    printf("memory error");
    return 0;
  }
  for (int i = 0; i < N; ++i) {
    if (scanf("%d", &data[i]) == 0) {
      printf("bad input");
      free(data);
      return 0;
    }
  }

  heapSort(data, N);

  for (int i = 0; i < N; ++i) {
    printf("%d ", data[i]);
  }
  free(data);
  return 0; 
}

void heapSort(int *data, int N) {
  for (int i = N / 2 - 1; i >= 0; --i) {
    heapify(data, i, N);
  }
  while (N > 1) {
    N--;
    swap(data, data + N);
    heapify(data, 0, N);
  }
}

void swap(int *a, int *b) { 
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void heapify(int *data, int i, int N) { 
  int curr = data[i];
  int index = i;
    while (1) {
      int left = index + index + 1;
      int right = left + 1;
      if (left < N && data[left] > curr) {
        index = left;
      }
      if (right < N && data[right] > data[index]) {
        index = right;
      }
      if (index == i) break;
      data[i] = data[index];
      data[index] = curr;
      i = index;
    }
}
