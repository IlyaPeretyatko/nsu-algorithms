#include "output.h"

void outputDistance(struct graph *graph, long long *path) {
  for (int i = 0; i < graph->countVertex; ++i) {
    if (path[i] == LLONG_MAX) {
      printf("oo ");
    } else if (path[i] > INT_MAX) {
      printf("INT_MAX+ ");
    } else {
      printf("%lld ", path[i]);
    }
  }
}

void outputPath(struct graph *graph, long long *path, int endIndex) {
  if (path[endIndex - 1] != LLONG_MAX) {
    printf("\n");
    if (CheckOverflow(endIndex, graph->countVertex, path)) {
      printf("overflow");
    } else {
      if (endIndex != graph->startIndex) {
        printf("%d ", endIndex);
        int i = endIndex - 1;
        while (1) {
          printf("%d ", graph->parents[i]);
          i = graph->parents[i] - 1;
          if (graph->parents[i] == 0) {
            break;
          }
        }
      } else {
        printf("%d", endIndex);
      }
    }
  } else {
    printf("\nno path");
  }
}

bool CheckOverflow(int endIndex, int countVertex, const long long *path) {
  if (path[endIndex - 1] <= INT_MAX) {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < countVertex; ++i) {
    if (i != endIndex - 1 && path[i] != LLONG_MAX && path[i] >= INT_MAX) {
      count++;
      if (count == 2) {
        return 1;
      }
    }
  }
  return 0;
}
