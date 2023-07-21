#ifndef LAB8_0_HEAPSORT_H
#define LAB8_0_HEAPSORT_H

#include "algorithmKraskala.h"

void heapSort(struct edge *data, int N);
void swap(struct edge *a, struct edge *b);
void heapify(struct edge *data, int i, int N);

#endif // LAB8_0_HEAPSORT_H
