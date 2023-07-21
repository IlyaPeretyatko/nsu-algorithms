#include "input.h"

int input(struct graph *graph) {
  graph->countVertex = inputCountVertex();
  if (graph->countVertex == -1) {
    return 0;
  }
  graph->countEdge = inputCountEdge(graph);
  if (graph->countEdge == -1) {
    return 0;
  }
  if (graph->countEdge < graph->countVertex - 1) {
    printf("no spanning tree");
    return 0;
  }
  graph->edges = malloc(graph->countEdge * sizeof(struct edge));
  if (graph->edges == NULL) {
    return 0;
  }
  if (graph->countEdge != 0) {
    int rvInputEdges = inputEdges(graph);
    if (rvInputEdges == -1) {
      free(graph->edges);
      return 0;
    }
  }
  return 1;
}

int inputEdges(struct graph *graph) {
  int start, end;
  long long length;
  int count = 0;
  int countInitVertex = 0;
  bool* checked = calloc(graph->countVertex, sizeof(bool));
  if (checked == NULL) {
    return -1;
  }
  while (scanf("%d %d %lld", &start, &end, &length) == 3) {
    if (start < 0 || end < 0 || start > graph->countVertex ||
        end > graph->countVertex) {
      printf("bad vertex");
      free(checked);
      return -1;
    }
    if (start == end) {
      printf("no spanning tree");
      free(checked);
      return -1;
    }
    if (length < 0 || length > INT_MAX) {
      printf("bad length");
      free(checked);
      return -1;
    }
    if (checked[start - 1] == 0) {
      checked[start - 1] = 1;
      countInitVertex++;
    }
    if (checked[end - 1] == 0) {
      checked[end - 1] = 1;
      countInitVertex++;
    }
    graph->edges[graph->index].start = start;
    graph->edges[graph->index].end = end;
    graph->edges[graph->index].length = (int)length;
    graph->index += 1;
    count++;
    if (count == graph->countEdge) {
      break;
    }
  }
  free(checked);
  if (count != graph->countEdge) {
    printf("bad number of lines");
    return -1;
  }
  if (countInitVertex != graph->countVertex) {
    printf("no spanning tree");
    return -1;
  }
  return count;
}

int inputCountEdge(struct graph* graph) {
  int countEdge;
  if (scanf("%d", &countEdge)) {
    if (countEdge < 0 || countEdge > MAX_COUNT_EDGE) {
      printf("bad number of edges");
      return -1;
    }
  } else {
    printf("bad number of lines");
    return -1;
  }
  return countEdge;
}

int inputCountVertex(void) {
  int countVertex;
  if (scanf("%d", &countVertex)) {
    if (countVertex < 0 || countVertex > MAX_COUNT_VERTEX) {
      printf("bad number of vertices");
      return -1;
    }
    if (countVertex == 0) {
      printf("no spanning tree");
      return -1;
    }
  } else {
    printf("bad number of lines");
    return -1;
  }
  return countVertex;
}
