#ifndef LAB9_ALGORITHMDIJKSTRA_H
#define LAB9_ALGORITHMDIJKSTRA_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT_VERTEX 5000
#define MAX_COUNT_EDGE N *(N - 1) / 2
#define SIZE_OF_MATRIX(N) ((N) *((N) + 1) / 2)

struct graph {
  int *matrix;
  int *parents;
  int countVertex;
  int startIndex;
};

long long *algorithmDijkstra(struct graph *graph);
void stepsDijkstra(struct graph *graph, long long *distance, bool *checked);
void initDijkstra(struct graph *graph, long long *distance, bool *checked);

#endif // LAB9_ALGORITHMDIJKSTRA_H
