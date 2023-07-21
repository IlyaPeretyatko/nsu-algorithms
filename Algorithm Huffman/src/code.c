#include <stdio.h>
#include <stdlib.h>
#include "code.h"

void code(FILE *fin, FILE *fout, int fromTerminal) {
  int countDifferentSymbol = 0;
  int *freqTable = (int *)calloc(CHAR_COUNT, sizeof(int));
  if (freqTable == NULL) {
    return;
  }
  unsigned char symbol = 0;
  while (!feof(fin)) {
    if (fread(&symbol, sizeof(unsigned char), 1, fin)) {
      freqTable[(int)symbol]++;
    }
  }
  if (fromTerminal) {
    fseek(fin, 0, SEEK_SET);
  } else {
    fseek(fin, sizeof(unsigned char), SEEK_SET);
  }
  struct list_t *list = NULL;
  if (initQueue(freqTable, &list, &countDifferentSymbol)) {
    free(freqTable);
    return;
  }
  if (countDifferentSymbol == 0) {
    free(freqTable);
    return;
  }
  struct tree_t *huffmanTree = buildingHuffmanTree(&list);
  if (huffmanTree == NULL) {
    destroyQueue(&list);
    free(freqTable);
    return;
  }
  struct codeTable *huffmanTable =
      buildingHuffmanTable(huffmanTree, countDifferentSymbol);
  if (huffmanTable == NULL) {
    destroyTree(&huffmanTree);
    free(list);
    free(freqTable);
    return;
  }
  int lastBits = calculationLastBits(huffmanTree, huffmanTable, freqTable);
  fwrite(&lastBits, sizeof(int), 1, fout);
  struct stringHuffman *string = createString();
  if (string == NULL) {
    destroyTable(huffmanTable);
    destroyTree(&huffmanTree);
    free(list);
    free(freqTable);
    return;
  }
  outputTree(huffmanTree, string, fout);
  addZero(string);
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    codeTextWithOneSymbol(string, fin, fout);
  } else {
    codeText(huffmanTable, string, fin, fout);
  }
  destroyTree(&huffmanTree);
  free(list);
  free(freqTable);
  destroyString(string);
  destroyTable(huffmanTable);
}

void codeTextWithOneSymbol(struct stringHuffman *string, FILE *fin,
                           FILE *fout) {
  unsigned char symbol = 0;
  while (fread(&symbol, sizeof(unsigned char), 1, fin)) {
    addZero(string);
    while (string->length >= 8) {
      outputCodingSymbol(string, fout);
    }
  }
  if (string->length != 0) {
    while (string->length != 8) {
      addZero(string);
    }
    outputCodingSymbol(string, fout);
  }
}

int calculationLastBits(struct tree_t *huffmanTree,
                        struct codeTable *huffmanTable, const int *freqTable) {
  int lastBits = 0;
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    getCountNodes(huffmanTree, &lastBits);
    lastBits += 1;
    for (int i = 0; i < CHAR_COUNT; ++i) {
      if (freqTable[i] != 0) {
        lastBits += freqTable[i];
        lastBits = (BYTE - lastBits % BYTE) % BYTE;
        break;
      }
    }
  } else {
    getCountNodes(huffmanTree, &lastBits);
    lastBits += 1;
    for (int i = 0; i < huffmanTable->max; ++i) {
      lastBits += huffmanTable->table[i].length *
                  freqTable[huffmanTable->table[i].symbol];
      lastBits %= BYTE;
    }
    lastBits = (BYTE - lastBits % BYTE) % BYTE;
  }
  return lastBits;
}

void getCountNodes(struct tree_t *huffmanTree, int *lastBits) {
  if (huffmanTree == NULL) {
    return;
  }
  getCountNodes(huffmanTree->left, lastBits);
  getCountNodes(huffmanTree->right, lastBits);
  *lastBits += 1;
}

int initQueue(int *freqTable, struct list_t **list, int *countDifferentSymbol) {
  for (int i = 0; i < CHAR_COUNT; ++i) {
    if (freqTable[i] != 0) {
      *countDifferentSymbol += 1;
      struct tree_t *newTree = (struct tree_t *)malloc(sizeof(struct tree_t));
      if (newTree == NULL) {
        free(freqTable);
        destroyQueue(list);
        return 1;
      }
      newTree->left = NULL;
      newTree->right = NULL;
      newTree->symbol = (unsigned char)i;
      if (pushList(newTree, freqTable[i], list)) {
        destroyQueue(list);
        free(freqTable);
        return 1;
      }
    }
  }
  return 0;
}

struct tree_t *buildingHuffmanTree(struct list_t **list) {
  if ((*list)->next == NULL) {
    return (*list)->tree;
  }
  int frequenceFirst = (*list)->freq;
  struct tree_t *treeFirst = popList(list);
  int frequenceSecond = (*list)->freq;
  struct tree_t *treeSecond = popList(list);
  struct tree_t *newTree = (struct tree_t *)malloc(sizeof(struct tree_t));
  if (newTree == NULL) {
    free(treeFirst);
    free(treeSecond);
    return NULL;
  }
  newTree->symbol = '\0';
  newTree->left = treeFirst;
  newTree->right = treeSecond;
  if (pushList(newTree, frequenceFirst + frequenceSecond, list)) {
    free(treeFirst);
    free(treeSecond);
    free(newTree);
    return NULL;
  }
  return buildingHuffmanTree(list);
}

struct codeTable *buildingHuffmanTable(struct tree_t *huffmanTree,
                                       int countSymbol) {
  struct codeTable *huffmanTable =
      (struct codeTable *)malloc(sizeof(struct codeTable));
  if (huffmanTable == NULL) {
    return NULL;
  }
  huffmanTable->max = countSymbol;
  huffmanTable->count = 0;
  huffmanTable->table =
      (struct code_t *)malloc(countSymbol * sizeof(struct code_t));
  if (huffmanTable->table == NULL) {
    free(huffmanTable);
    return NULL;
  }
  unsigned char code[CHAR_COUNT] = {0};
  if (initHuffmanTable(huffmanTree, huffmanTable, code, 0)) {
    destroyTable(huffmanTable);
    return NULL;
  }
  return huffmanTable;
}

int initHuffmanTable(struct tree_t *huffmanTree, struct codeTable *huffmanTable,
                     unsigned char *code, int length) {
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    huffmanTable->table[huffmanTable->count].symbol = huffmanTree->symbol;
    huffmanTable->table[huffmanTable->count].length = length;
    huffmanTable->table[huffmanTable->count].code =
        (unsigned char *)malloc(length * sizeof(unsigned char));
    if (huffmanTable->table[huffmanTable->count].code == NULL) {
      return 1;
    }
    for (int i = 0; i < length; ++i) {
      huffmanTable->table[huffmanTable->count].code[i] = code[i];
    }
    huffmanTable->count += 1;
  } else {
    code[length] = '0';
    if (initHuffmanTable(huffmanTree->left, huffmanTable, code, length + 1)) {
      return 1;
    }
    code[length] = '1';
    if (initHuffmanTable(huffmanTree->right, huffmanTable, code, length + 1)) {
      return 1;
    }
  }
  return 0;
}

void outputTree(struct tree_t *huffmanTree, struct stringHuffman *string,
                FILE *fout) {
  if (huffmanTree == NULL) {
    return;
  }
  outputTree(huffmanTree->left, string, fout);
  outputTree(huffmanTree->right, string, fout);
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    addOne(string);
    addSymbol(string, huffmanTree->symbol);
  } else {
    addZero(string);
  }
  while (string->length >= 8) {
    outputCodingSymbol(string, fout);
  }
}

void outputCodingSymbol(struct stringHuffman *string, FILE *fout) {
  unsigned char symbol = 0;
  for (int i = 0; i < 8; ++i) {
    symbol <<= 1;
    unsigned char bit = string->code[string->begin];
    string->begin = (string->begin + 1) % string->max;
    string->length -= 1;
    if (bit == '1') {
      symbol |= 1;
    } else {
      symbol |= 0;
    }
  }
  fwrite(&symbol, 1, 1, fout);
}

void codeText(struct codeTable *huffmanTable, struct stringHuffman *string,
              FILE *fin, FILE *fout) {
  unsigned char symbol = 0;
  while (fread(&symbol, sizeof(unsigned char), 1, fin)) {
    addSymbolCode(string, huffmanTable, symbol);
    while (string->length >= 8) {
      outputCodingSymbol(string, fout);
    }
  }
  if (string->length != 0) {
    while (string->length != 8) {
      addZero(string);
    }
    outputCodingSymbol(string, fout);
  }
}

void destroyTree(struct tree_t **tree) {
  if (*tree == NULL) {
    return;
  }
  destroyTree(&((*tree)->left));
  destroyTree(&((*tree)->right));
  free(*tree);
}

void destroyString(struct stringHuffman *string) {
  free(string->code);
  free(string);
}

void destroyTable(struct codeTable *huffmanTable) {
  for (int i = 0; i < huffmanTable->max; ++i) {
    if (huffmanTable->table[i].code != NULL) {
      free(huffmanTable->table[i].code);
    }
  }
  if (huffmanTable->table != NULL) {
    free(huffmanTable->table);
  }
  if (huffmanTable != NULL) {
    free(huffmanTable);
  }
}
