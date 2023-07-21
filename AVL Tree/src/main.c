#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  struct node* left;
  struct node* right;
  int value;
  unsigned char height;
}vertex;

unsigned char getHeight (vertex *p);
void fixHeight(vertex *p);
int checkBalance(vertex *p);
vertex* rotateRight(vertex* root);
vertex* rotateLeft(vertex* root);
vertex* balance(vertex* p);
vertex* insert(vertex* p, vertex *new);


int main(void) {
  int N;
  if (scanf("%d", &N) == 0) {
    printf("bad input");
    return 0;
  }
  vertex *nodes = malloc(N * sizeof(vertex));
  if (nodes == NULL) {
    printf("memory error");
    return 0;
  }
  vertex *tree = NULL;
  for (int i = 0; i < N; ++i) {
    int number = 0;
    if (scanf("%d", &number) != 0) {
      nodes[i].left = NULL;
      nodes[i].right = NULL;
      nodes[i].value = number;
      nodes[i].height = 1;
      tree = insert(tree, &nodes[i]);
    } else {
      printf("bad input");
      free(nodes);
      return 0;
    }
  }
  if (N != 0) {
    printf("%d", tree -> height);
  } else {
    printf("%d", 0);
  }
  free(nodes);
  return 0;
}

vertex* insert(vertex* p, vertex* new) {
  if(p == NULL) {
    return new;
  }
  if(new -> value < p -> value) {
    p->left = insert(p->left, new);
  } else {
    p->right = insert(p->right, new);
  }
  return balance(p);
}


unsigned char getHeight (vertex *p) {
  if (p != NULL) {
    return p -> height;
  }
  return 0;
}

void fixHeight(vertex *p) {
  unsigned char heightLeft = getHeight(p -> left);
  unsigned char heightRight= getHeight(p -> right);
  unsigned char max;
  if (heightLeft >= heightRight) {
    max = heightLeft;
  } else {
    max = heightRight;
  }
  p -> height = max + 1;
}

int checkBalance(vertex *p) {
  return getHeight(p -> right) - getHeight(p -> left);
}

vertex* rotateRight(vertex* root) {
  vertex* newRoot = root -> left;
  root -> left = newRoot -> right;
  newRoot -> right = root;
  fixHeight(root);
  fixHeight(newRoot);
  return newRoot;
}

vertex* rotateLeft(vertex* root) {
  vertex* newRoot = root->right;
  root -> right = newRoot -> left;
  newRoot -> left = root;
  fixHeight(root);
  fixHeight(newRoot);
  return newRoot;
}


vertex *balance(vertex* p) {
  fixHeight(p);
  if (checkBalance(p) == 2) {
    if (checkBalance(p -> right) < 0) {
      p -> right = rotateRight(p->right);
    }
    return rotateLeft(p);
  }
  if (checkBalance(p) == -2 ) {
    if (checkBalance(p -> left) > 0) {
      p -> left = rotateLeft(p -> left);
    }
    return rotateRight(p);
  }
  return p;
}




