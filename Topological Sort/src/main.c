#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GREY 1
#define BLACK 2

int inputCountVertexAndEdges(int *countVertex, int *countEdges);
int inputEdges(char *matrix, int countVertex, int countEdges, int LD);
int TopSort(int countVertex, char *matrix, int *output, int *color, int LD);
int TopSortStep(int countVertex, char *matrix, int *output, int *color, int i,
                int checkCicle, int *outputIndex, int LD);
void output(int *outputNumbers, int countVertex);

int main() {
  int countVertex = 0;
  int countEdges = -1;
  if (inputCountVertexAndEdges(&countVertex, &countEdges) == 0) {
    return 0;
  }
  int LD = (countVertex - countVertex % 8 + 8) / 8;
  char *matrix = (char *)malloc(countVertex * LD *sizeof(char));
  if (matrix != NULL) {
    for (int i = 0; i < LD * countVertex; ++i) {
      matrix[i] = 0;
    }
    if (inputEdges(matrix, countVertex, countEdges, LD) == 0) {
      free(matrix);
      return 0;
    }
  } else {
    printf("memory error");
    return 0;
  }
  int *color = (int *)calloc(countVertex, sizeof(int));
  int *outputNumbers = (int *)calloc(countVertex, sizeof(int));
  if (color == NULL || outputNumbers == NULL) {
    if (color != NULL) {
      free(color);
    }
    if (outputNumbers != NULL) {
      free(outputNumbers);
    }
    printf("memory error");
    free(matrix);
    return 0;
  }
  if (TopSort(countVertex, matrix, outputNumbers, color, LD) != 0) {
    output(outputNumbers, countVertex);
  }
  free(matrix);
  free(color);
  free(outputNumbers);
  return 0;
}

void output(int *outputNumbers, int countVertex) {
  for (int i = countVertex - 1; i >= 0; --i) {
    printf("%d ", outputNumbers[i]);
  }
}



int TopSort(int countVertex, char *matrix, int *output, int *color, int LD) {
  int outputIndex = 0;
  for (int i = 0; i < countVertex; ++i) {
    if (color[i] == WHITE) {
      if (TopSortStep(countVertex, matrix, output, color, i, i, &outputIndex,
                      LD) == 0) {
        return 0;
      }
    }
  }
  return 1;
}

int TopSortStep(int countVertex, char *matrix, int *output, int *color, int i,
                int checkCicle, int *outputIndex, int LD) {
  color[i] = GREY;
  for (int j = countVertex - 1; j >= 0; --j) {
    char maskArea = matrix[i * LD + j / 8];
    if ((maskArea & (1 << (7 - j % 8))) != 0 && j == checkCicle) {
      printf("impossible to sort");
      return 0;
    } else if ((maskArea & (1 << (7 - j % 8))) != 0 && (color[j] == 0)) {
      if (TopSortStep(countVertex, matrix, output, color, j, checkCicle,
                      outputIndex, LD) == 0) {
        return 0;
      }
    }
  }
  color[i] = BLACK;
  output[*outputIndex] = i + 1;
  *outputIndex += 1;
  return 1;
}

int inputEdges(char *matrix, int countVertex, int countEdges, int LD) {
  int i = 0;
  int j = 0;
  int count = 0;
  while (count < countEdges) {
    if (scanf("%d %d", &i, &j) != 2) {
      printf("bad number of lines");
      return 0;
    }
    if (i == j) {
      printf("impossible to sort");
      return 0;
    }
    if (i < 0 || j < 0 || i > countVertex || j > countVertex) {
      printf("bad vertex");
      return 0;
    }
    char maskArea;
    maskArea = matrix[(i - 1) * LD + ((j - 1) / 8)];
    matrix[(i - 1) * LD + ((j - 1) / 8)] =
        maskArea | (1 << (7 - ((j - 1) % 8)));
    count++;
  }
  return 1;
}



int inputCountVertexAndEdges(int *countVertex, int *countEdges) {
  int rv = scanf("%d", countVertex);
  if (rv == 0) {
    printf("bad number of lines");
    return 0;
  } else if (*countVertex < 0 || *countVertex > 2000) {
    printf("bad number of vertices");
    return 0;
  }
  int maxCountEdges = (*countVertex) * (*countVertex + 1) / 2;
  if (scanf("%d", countEdges) == 1 &&
      (*countEdges < 0 || *countEdges > maxCountEdges)) {
    printf("bad number of edges");
    return 0;
  }
  if (*countEdges == -1) {
    printf("bad number of lines");
    return 0;
  }
  return 1;
}
