#include "additional.h"

int createGraph(struct graph *graph, int N) {
  graph->matrix = calloc(SIZE_OF_MATRIX(N), sizeof(int));
  if (graph->matrix == NULL) {
    printf("memory error");
    return 0;
  }
  graph->parents = calloc(graph->countVertex, sizeof(int));
  if (graph->parents == NULL) {
    destroyGraph(graph);
    return 0;
  }
  return 1;
}

void destroyGraph(struct graph *graph) {
  if (graph->matrix != NULL) {
    free(graph->matrix);
  }
  if (graph->parents != NULL) {
    free(graph->parents);
  }
}

void pushMatrix(int start, int end, int length, struct graph *graph) {
  int max = (start > end) ? start : end;
  int min = (start < end) ? start : end;
  int index = max * (max - 1) / 2 + min - 1;
  graph->matrix[index] = length;
}

int getMatrixValue(int start, int end, struct graph *graph) {
  int max = (start > end) ? start : end;
  int min = (start < end) ? start : end;
  int index = max * (max - 1) / 2 + min - 1;
  return graph->matrix[index];
}
