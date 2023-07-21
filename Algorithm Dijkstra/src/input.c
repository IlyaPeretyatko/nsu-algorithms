#include "input.h"

int input(struct graph *graph) {
  int N = inputCountVertex(graph);
  if (N == -1) {
    return 0;
  }
  int endIndex = inputStartEnd(graph);
  if (!endIndex) {
    return 0;
  }
  int countEdges = inputCountEdges(N);
  if (countEdges == -1) {
    return 0;
  }
  if (!createGraph(graph, N)) {
    return 0;
  }
  int count = inputEdges(graph, countEdges);
  if (count != countEdges) {
    printf("bad number of lines");
    destroyGraph(graph);
    return 0;
  }
  return endIndex;
}

int inputCountVertex(struct graph *graph) {
  int N;
  if (scanf("%d", &N)) {
    if (N < 0 || N > MAX_COUNT_VERTEX) {
      printf("bad number of vertices");
      return -1;
    }
    graph->countVertex = N;
  } else {
    printf("bad number of lines");
    return -1;
  }
  return N;
}

int inputStartEnd(struct graph *graph) {
  int startIndex, endIndex;
  if (scanf("%d %d", &startIndex, &endIndex) == 2) {
    if (startIndex <= 0 || endIndex <= 0 || startIndex > graph->countVertex ||
        endIndex > graph->countVertex) {
      printf("bad vertex");
      return 0;
    }
    graph->startIndex = startIndex;
  } else {
    printf("bad number of lines");
    return 0;
  }
  return endIndex;
}

int inputCountEdges(int N) {
  int countEdges;
  if (scanf("%d", &countEdges)) {
    if (countEdges < 0 || countEdges > MAX_COUNT_EDGE) {
      printf("bad number of edges");
      return -1;
    }
  } else {
    printf("bad number of lines");
    return -1;
  }
  return countEdges;
}

int inputEdges(struct graph *graph, int countEdges) {
  int start, end;
  long long length;
  int count = 0;
  while (scanf("%d %d %lld", &start, &end, &length) == 3) {
    if (start < 0 || end < 0 || start > graph->countVertex ||
        end > graph->countVertex) {
      printf("bad vertex");
      return 0;
    }
    if (length < 0 || length > INT_MAX) {
      printf("bad length");
      return 0;
    }
    pushMatrix(start, end, (int)length, graph);
    count++;
    if (count == countEdges) {
      break;
    }
  }
  return count;
}
