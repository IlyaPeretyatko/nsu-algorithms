#ifndef LAB5_MAIN_H
#define LAB5_MAIN_H

#define CHAR_COUNT 256
#define BYTE 8

struct stringHuffman {
  int begin;
  int end;
  int length;
  int max;
  unsigned char *code;
};

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  unsigned char symbol;
};

struct stackOfTree {
  struct tree_t *tree;
  struct stackOfTree *next;
};

struct list_t {
  struct list_t *next;
  struct tree_t *tree;
  long long freq;
};

struct code_t {
  unsigned char symbol;
  int length;
  unsigned char *code;
};

struct codeTable {
  int count;
  int max;
  struct code_t *table;
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#include "decode.h"
#include "stackAndQueue.h"
#include "string.h"

#endif // LAB5_MAIN_H
