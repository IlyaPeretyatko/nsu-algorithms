#include <stdio.h>
#include <stdlib.h>
#include "stackAndQueue.h"

int push(struct stackOfTree **stack, struct tree_t *newTree) {
  struct stackOfTree *list =
      (struct stackOfTree *)malloc(sizeof(struct stackOfTree));
  if (list == NULL) {
    return 1;
  }
  list->next = *stack;
  *stack = list;
  list->tree = newTree;
  return 0;
}

struct tree_t *pop(struct stackOfTree **stack) {
  struct tree_t *tree = (*stack)->tree;
  struct stackOfTree *list = *stack;
  *stack = (*stack)->next;
  free(list);
  return tree;
}

struct tree_t *popList(struct list_t **list) {
  struct tree_t *returnList = (*list)->tree;
  struct list_t *temp = *list;
  *list = (*list)->next;
  free(temp);
  return returnList;
}

int pushList(struct tree_t *newTree, int freq, struct list_t **list) {
  if (*list == NULL || freq <= (*list)->freq) {
    struct list_t *newList = (struct list_t *)malloc(sizeof(struct list_t));
    if (newList == NULL) {
      return 1;
    }
    newList->freq = freq;
    newList->tree = newTree;
    newList->next = *list;
    *list = newList;
    return 0;
  } else {
    return pushList(newTree, freq, &((*list)->next));
  }
}

void destroyQueue(struct list_t **list) {
  if (*list == NULL) {
    return;
  } else {
    struct list_t *next = (*list)->next;
    destroyTree(&((*list)->tree));
    free(*list);
    destroyQueue(&next);
  }
}
