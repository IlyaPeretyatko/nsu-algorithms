#ifndef LAB6_1_FIXINSERT_H
#define LAB6_1_FIXINSERT_H

#include "RBTree.h"
#include "additional.h"

void fixInsert(struct tree *tree, struct node* vertex);
void checkFather(struct tree *tree, struct node* vertex);
void checkUncle(struct tree *tree, struct node* vertex);
void alignment(struct tree* tree, struct node* vertex);
void rotate(struct tree* tree, struct node* vertex, struct node* father);
void rightRotate(struct tree *tree, struct node *node);
void leftRotate(struct tree *tree, struct node *node);

#endif // LAB6_1_FIXINSERT_H
