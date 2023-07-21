#ifndef LAB5_STACKANDQUEUE_H
#define LAB5_STACKANDQUEUE_H

#include "main.h"

int pushList(struct tree_t *newTree, int freq, struct list_t **list);
struct tree_t *popList(struct list_t **list);
int push(struct stackOfTree **stack, struct tree_t *newTree);
struct tree_t *pop(struct stackOfTree **stack);
void destroyQueue(struct list_t **list);

#endif // LAB5_STACKANDQUEUE_H
