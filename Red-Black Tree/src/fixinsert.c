#include "fixinsert.h"

void fixInsert(struct tree *tree, struct node* vertex) {
  if (tree->root == vertex) {
    vertex->color = BLACK;
  } else {
    checkFather(tree, vertex);
  }
  tree->count = 0;
}

void checkFather(struct tree *tree, struct node* vertex) {
  struct node* father = tree->parents[tree->count - 1];
  if (getColor(father) == BLACK) {
    return;
  } else {
    checkUncle(tree, vertex);
  }
}

void checkUncle(struct tree *tree, struct node* vertex) {
  struct node* grandfather = tree->parents[tree->count - 2];
  struct node* father = tree->parents[tree->count - 1];
  if (grandfather->left == father) {
    if (getColor(grandfather->right)) {
      father->color = BLACK;
      if (grandfather->right != NULL) {
        grandfather->right->color = BLACK;
      }
      grandfather->color = RED;
      tree->count -= 2;
      fixInsert(tree, grandfather);
    } else {
      alignment(tree, vertex);
    }
  } else {
    if (getColor(grandfather->left)) {
      father->color = BLACK;
      if (grandfather->left != NULL) {
        grandfather->left->color = BLACK;
      }
      grandfather->color = RED;
      tree->count -= 2;
      fixInsert(tree, grandfather);
    } else {
      alignment(tree, vertex);
    }
  }
}
void alignment(struct tree* tree, struct node* vertex) {
  struct node* grandfather = tree->parents[tree->count - 2];
  struct node* father = tree->parents[tree->count - 1];
  if (father == grandfather->left && vertex == father->right) {
    leftRotate(tree, father);
    father = vertex;
    vertex = vertex->left;
  } else if (father == grandfather->right && vertex == father->left) {
    rightRotate(tree, father);
    father = vertex;
    vertex = vertex->right;
  }
  rotate(tree, vertex, father);
}

void rotate(struct tree* tree, struct node* vertex, struct node* father) {
  struct node* grandfather = tree->parents[tree->count - 2];
  father->color = BLACK;
  grandfather->color = RED;
  if (father->left == vertex && grandfather->left == father) {
    rightRotate(tree, grandfather);
  } else {
    leftRotate(tree, grandfather);
  }
}

void rightRotate(struct tree *tree, struct node *node) {
  struct node *son = node->left;
  struct node* grandfather = tree->parents[tree->count - 2];
  if (grandfather == tree->root && grandfather == node) {
    tree->root = node->left;
  } else if (grandfather != tree->root && grandfather == node) {
    if (tree->parents[tree->count - 3]->left == grandfather) {
      tree->parents[tree->count - 3]->left = node->left;
    } else {
      tree->parents[tree->count - 3]->right = node->left;
    }
  } else if (grandfather->right == node) {
    grandfather->right = son;
  }
  node->left = son->right;
  son->right = node;
}

void leftRotate(struct tree *tree, struct node *node) {
  struct node *son = node->right;
  struct node* grandfather = tree->parents[tree->count - 2];
  if (grandfather == tree->root && grandfather == node) {
    tree->root = node->right;
  } else if (grandfather != tree->root && grandfather == node) {
    if (tree->parents[tree->count - 3]->left == grandfather) {
      tree->parents[tree->count - 3]->left = node->right;
    } else {
      tree->parents[tree->count - 3]->right = node->right;
    }
  } else if (grandfather->left == node) {
    grandfather->left = son;
  }
  node->right = son->left;
  son->left = node;
}
