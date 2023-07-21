#ifndef LAB6_1_RBTREE_H
#define LAB6_1_RBTREE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT_TREE 64
#define RED 1
#define BLACK 0

struct node {
  struct node *left;
  struct node *right;
  int value;
  unsigned char color;
};

struct tree {
  struct node *root;
  struct node *nodes;
  struct node **parents;
  int index;
  int count;
};

void insert(struct tree *tree, int key);

#endif // LAB6_1_RBTREE_H
