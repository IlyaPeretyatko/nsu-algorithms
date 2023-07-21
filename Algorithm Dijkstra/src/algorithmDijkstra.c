#include "algorithmDijkstra.h"
#include "additional.h"
#include "input.h"
#include "output.h"

int main(void) {
  struct graph graph = {NULL, NULL, 0, 0};
  int endIndex = input(&graph);
  if (!endIndex) {
    return 0;
  }
  long long *path = algorithmDijkstra(&graph);
  if (path == NULL) {
    free(graph.parents);
    free(graph.matrix);
    return 0;
  }
  outputDistance(&graph, path);
  outputPath(&graph, path, endIndex);
  destroyGraph(&graph);
  free(path);
  return 0;
}

long long *algorithmDijkstra(struct graph *graph) {
  long long *distance = calloc(graph->countVertex, sizeof(long long));
  if (distance == NULL) {
    destroyGraph(graph);
    return NULL;
  }
  bool *checked = calloc(graph->countVertex, sizeof(bool));
  if (checked == NULL) {
    destroyGraph(graph);
    free(distance);
    return NULL;
  }
  initDijkstra(graph, distance, checked);
  stepsDijkstra(graph, distance, checked);
  free(checked);
  return distance;
}

void stepsDijkstra(struct graph *graph, long long *distance, bool *checked) {
  int count = graph->countVertex;
  int working = graph->startIndex;
  while (count) {
    for (int i = 0; i < graph->countVertex; ++i) {
      if (checked[i]) {
        continue;
      }
      int length = getMatrixValue(working, i + 1, graph);
      if (length == 0) {
        continue;
      }
      if (distance[working - 1] + length < distance[i]) {
        distance[i] = distance[working - 1] + length;
        graph->parents[i] = working;
      }
    }
    long long min = LLONG_MAX;
    for (int i = 0; i < graph->countVertex; ++i) {
      if (checked[i]) {
        continue;
      }
      if (distance[i] <= min) {
        min = distance[i];
        working = i + 1;
      }
    }
    checked[working - 1] = 1;
    count -= 1;
  }
}

void initDijkstra(struct graph *graph, long long *distance, bool *checked) {
  for (int i = 0; i < graph->countVertex; ++i) {
    if (i == graph->startIndex - 1) {
      distance[i] = 0;
      continue;
    }
    distance[i] = LLONG_MAX;
    graph->parents[i] = 0;
  }
  checked[graph->startIndex - 1] = 1;
}
