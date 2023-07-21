#ifndef LAB8_0_ALGORITHMKRASKALA_H
#define LAB8_0_ALGORITHMKRASKALA_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COUNT_VERTEX 5000
#define MAX_COUNT_EDGE graph->countVertex * (graph->countVertex + 1) / 2

struct edge {
  int start;
  int end;
  int length;
};

struct graph {
  int countVertex;
  int countEdge;
  int index;
  struct edge *edges;
};

int algorithmKraskala(struct graph *graph);
void initParent(struct graph *graph, int *parent);
int findParent(int vertex, int *parent);
int unite(int firstVertex, int secondVertex, int *parent);

#endif // LAB8_0_ALGORITHMKRASKALA_H
