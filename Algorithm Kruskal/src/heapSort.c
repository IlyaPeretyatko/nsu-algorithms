#include "heapSort.h"

void heapSort(struct edge *data, int N) {
  for (int i = N / 2 - 1; i >= 0; --i) {
    heapify(data, i, N);
  }
  while (N > 1) {
    N--;
    swap(data, data + N);
    heapify(data, 0, N);
  }
}

void swap(struct edge *a, struct edge *b) {
  struct edge tmp = *a;
  *a = *b;
  *b = tmp;
}

void heapify(struct edge *data, int i, int N) {
  struct edge curr = data[i];
  int index = i;
  while (1) {
    int left = index + index + 1;
    int right = left + 1;
    if (left < N && data[left].length > curr.length) {
      index = left;
    }
    if (right < N && data[right].length > data[index].length) {
      index = right;
    }
    if (index == i)
      break;
    data[i] = data[index];
    data[index] = curr;
    i = index;
  }
}
