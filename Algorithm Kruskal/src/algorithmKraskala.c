#include "algorithmKraskala.h"
#include "heapSort.h"
#include "input.h"

int main(void) {
  struct graph graph = {-1, -1, 0, NULL};
  if (!input(&graph)) {
    return 0;
  }
  heapSort(graph.edges, graph.countEdge);
  if (!algorithmKraskala(&graph)) {
    free(graph.edges);
    return 0;
  }
  for (int i = 0; i < graph.countEdge; ++i) {
    if (graph.edges[i].length != 0) {
      printf("%d %d\n", graph.edges[i].start, graph.edges[i].end);
    }
  }
  free(graph.edges);
  return 0;
}

int algorithmKraskala(struct graph *graph) {
  int *parent = malloc(graph->countVertex * sizeof(int));
  if (parent == NULL) {
    free(graph->edges);
    return 0;
  }
  initParent(graph, parent);
  for (int i = 0; i < graph->countEdge; ++i) {
    int first = graph->edges[i].start;
    int second = graph->edges[i].end;
    if (!unite(first, second, parent)) {
      graph->edges[i].length = 0;
    }
  }
  free(parent);
  return 1;
}

int unite(int firstVertex, int secondVertex, int *parent) {
  int firstParent = findParent(firstVertex, parent);
  int secondParent = findParent(secondVertex, parent);
  if (firstParent != secondParent) {
    parent[secondParent - 1] = firstParent;
    return 1;
  } else {
    return 0;
  }
}

int findParent(int vertex, int *parent) {
  if (vertex == parent[vertex - 1]) {
    return vertex;
  }
  return parent[vertex - 1] = findParent(parent[vertex - 1], parent);
}

void initParent(struct graph *graph, int *parent) {
  for (int i = 0; i < graph->countVertex; ++i) {
    parent[i] = i + 1;
  }
}
