#include "RBTree.h"
#include "fixinsert.h"
#include "additional.h"

int main(void) {
  int N;
  if (scanf("%d", &N) == 0) {
    printf("bad input");
    return 0;
  }
  struct tree tree;
  if (!initialTree(&tree, N)) {
    printf("memory error");
    return 0;
  }
  for (int i = 0; i < N; ++i) {
    int number = 0;
    if (scanf("%d", &number) != 0) {
      insert(&tree, number);
    } else {
      printf("bad input");
      destroyTree(&tree);
      return 0;
    }
  }
  printf("%d", getHeight(&tree));
  destroyTree(&tree);
  return 0;
}

void insert(struct tree *tree, int key) {
  if (tree->root == NULL) {
    init(tree, key);
    tree->root = tree->nodes;
    tree->root->color = BLACK;
  } else {
    struct node *point = tree->root;
    int rightOrLeft = 0;
    while (point != NULL) {
      if (key < point->value) {
        addParent(tree, point);
        point = point->left;
        rightOrLeft = 0;
      } else {
        addParent(tree, point);
        point = point->right;
        rightOrLeft = 1;
      }
    }
    init(tree, key);
    if (rightOrLeft) {
      tree->parents[tree->count - 1]->right = &(tree->nodes[tree->index - 1]);
    } else {
      tree->parents[tree->count - 1]->left = &(tree->nodes[tree->index - 1]);
    }
  }
  fixInsert(tree, &(tree->nodes[tree->index - 1]));
}
