#include <stdio.h>
#include <stdlib.h>

struct item {
  int price;
  int weight;
};

int maximum(int i, int j, struct item *items, int **matrix);
struct item *input(int *countBag, int *weightBag);
void initMatrix(struct item *items, int **matrix, int countBag, int weightBag);
void output(struct item *items, int **matrix, int countBag, int weightBag);
void findItems(struct item *items, int **matrix, int k, int s, int weightBag);
void destroyMatrix(int **matrix, int countBag);

int main(void) {
  int countBag = 0;
  int weightBag = 0;
  struct item *items = input(&countBag, &weightBag);
  if (items == NULL) {
    return 0;
  }
  int **matrix = malloc((countBag + 1) * sizeof(int *));
  if (matrix == NULL) {
    free(items);
    return 0;
  }
  for (int i = 0; i < countBag + 1; ++i) {
    matrix[i] = malloc((weightBag + 1) * sizeof(int));
    if (matrix[i] == NULL) {
      destroyMatrix(matrix, countBag);
      free(items);
      return 0;
    }
  }
  initMatrix(items, matrix, countBag, weightBag);
  output(items, matrix, countBag, weightBag);
  destroyMatrix(matrix, countBag);
  free(items);
  return 0;
}

void destroyMatrix(int **matrix, int countBag) {
  if (matrix != NULL) {
    for (int i = 0; i < countBag + 1; ++i) {
      if (matrix[i] != NULL) {
        free(matrix[i]);
      } else {
        break;
      }
    }
    free(matrix);
  }
}

void output(struct item *items, int **matrix, int countBag, int weightBag) {
  printf("%d\n", matrix[countBag][weightBag]);
  int j = weightBag;
  int maxPrice = matrix[countBag][weightBag];
  while (matrix[countBag][j] == maxPrice) {
    j--;
  }
  j++;
  findItems(items, matrix, countBag, j, weightBag);
}

void findItems(struct item *items, int **matrix, int k, int s, int weightBag) {
  if (matrix[k][s] == 0) {
    return;
  }
  if (matrix[k][s] == matrix[k - 1][s]) {
    findItems(items, matrix, k - 1, s, weightBag);
  } else {
    findItems(items, matrix, k - 1, s - items[k - 1].weight, weightBag);
    printf("%d %d\n", items[k - 1].weight, items[k - 1].price);
  }
}

void initMatrix(struct item *items, int **matrix, int countBag, int weightBag) {
  for (int i = 0; i < countBag + 1; ++i) {
    for (int j = 0; j < weightBag + 1; ++j) {
      if (i == 0 || j == 0) {
        matrix[i][j] = 0;
      } else {
        matrix[i][j] = maximum(i, j, items, matrix);
      }
    }
  }
}

struct item *input(int *countBag, int *weightBag) {
  if (scanf("%d %d", countBag, weightBag) != 2) {
    printf("bad input");
    return NULL;
  }
  struct item *items = malloc(*countBag * sizeof(struct item));
  if (items == NULL) {
    return NULL;
  }
  for (int i = 0; i < *countBag; ++i) {
    if (scanf("%d %d", &items[i].weight, &items[i].price) != 2) {
      printf("bad input");
      free(items);
      return NULL;
    }
  }
  return items;
}

int maximum(int i, int j, struct item *items, int **matrix) {
  int b = 0;
  if (j - items[i - 1].weight < 0) {
    b = 0;
  } else {
    b = matrix[i - 1][j - items[i - 1].weight] + items[i - 1].price;
  }
  int a = matrix[i - 1][j];
  return (a >= b) ? a : b;
}
