#include "additional.h"

int getColor(struct node *node) {
  if (node == NULL) {
    return 0;
  }
  if (node->color == RED) {
    return 1;
  }
  return 0;
}

void addParent(struct tree *tree, struct node *node) {
  if (tree->count < MAX_HEIGHT_TREE) {
    tree->parents[tree->count] = node;
    tree->count += 1;
  }
}

void init(struct tree *tree, int key) {
  tree->nodes[tree->index].left = NULL;
  tree->nodes[tree->index].right = NULL;
  tree->nodes[tree->index].value = key;
  tree->nodes[tree->index].color = RED;
  tree->index += 1;
}

int initialTree(struct tree *tree, int N) {
  tree->index = 0;
  tree->count = 0;
  tree->root = NULL;
  tree->nodes = malloc(N * sizeof(struct node));
  if (tree->nodes == NULL) {
    return 0;
  }
  tree->parents = malloc(MAX_HEIGHT_TREE * sizeof(struct node *));
  if (tree->parents == NULL) {
    free(tree->nodes);
    return 0;
  }
  return 1;
}

void destroyTree(struct tree *tree) {
  free(tree->nodes);
  free(tree->parents);
}

int getHeight(struct tree *tree) {
  int count = 0;
  struct node *point = tree->root;
  while (point != NULL) {
    if (point->color == BLACK) {
      count++;
    }
    point = point->right;
  }
  if (count != 0) {
    count++;
  }
  return count;
}
