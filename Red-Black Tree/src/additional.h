#ifndef LAB6_1_ADDITIONAL_H
#define LAB6_1_ADDITIONAL_H

#include "RBTree.h"

int initialTree(struct tree *tree, int N);
void destroyTree(struct tree *tree);
void init(struct tree *tree, int key);
void addParent(struct tree *tree, struct node *node);
int getColor(struct node *node);
int getHeight(struct tree *tree);

#endif // LAB6_1_ADDITIONAL_H
