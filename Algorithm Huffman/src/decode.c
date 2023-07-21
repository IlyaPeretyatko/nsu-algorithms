#include <stdio.h>
#include "decode.h"

void decode(FILE *fin, FILE *fout) {
  int lastBits = 0;
  if (!fread(&lastBits, sizeof(int), 1, fin)) {
    return;
  }
  struct stringHuffman *string = createString();
  if (string == NULL) {
    return;
  }
  struct tree_t *huffmanTree = inputTree(string, fin);
  if (huffmanTree == NULL) {
    destroyString(string);
    return;
  }
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    while (1) {
      if (outputTextWithOneSymbol(huffmanTree, string, lastBits, fin, fout)) {
        break;
      }
    }
  } else {
    while (1) {
      if (outputDecodeSymbol(huffmanTree, string, lastBits, fin, fout)) {
        break;
      }
    }
  }
  destroyString(string);
  destroyTree(&huffmanTree);
}

int outputTextWithOneSymbol(struct tree_t *huffmanTree,
                            struct stringHuffman *string, int lastBits,
                            FILE *fin, FILE *fout) {
  static int thisLastByte = 0;
  unsigned char symbol1 = 0;
  unsigned char symbol2 = 0;
  if (string->length == 0) {
    if (feof(fin)) {
      return 1;
    } else {
      if (fread(&symbol1, sizeof(unsigned char), 1, fin)) {
        addSymbol(string, symbol1);
      }
    }
  }
  if (string->length < 2 * BYTE) {
    if (fread(&symbol2, sizeof(unsigned char), 1, fin)) {
      addSymbol(string, symbol2);
    } else {
      thisLastByte = 1;
    }
  }
  if (thisLastByte && string->length == lastBits) {
    return 1;
  }
  getBit(string);
  fwrite(&(huffmanTree->symbol), sizeof(unsigned char), 1, fout);
  return 0;
}

struct tree_t *inputTree(struct stringHuffman *string, FILE *fin) {
  struct stackOfTree *stack = NULL;
  while (1) {
    while (string->length == 0 ||
           (string->code[string->begin] == '1' && string->length < 9)) {
      unsigned char symbol = 0;
      if (!fread(&symbol, sizeof(unsigned char), 1, fin)) {
        break;
      }
      addSymbol(string, symbol);
    }
    if (getBit(string) == '1') {
      unsigned char symbol = getSymbol(string);
      struct tree_t *newTree = (struct tree_t *)malloc(sizeof(struct tree_t));
      if (newTree == NULL) {
        while (stack != NULL) {
          free(stack->tree);
          pop(&stack);
        }
        return NULL;
      }
      newTree->left = NULL;
      newTree->right = NULL;
      newTree->symbol = symbol;
      if (push(&stack, newTree)) {
        while (stack != NULL) {
          free(stack->tree);
          pop(&stack);
        }
        return NULL;
      }
    } else {
      if (stack->next == NULL) {
        return pop(&stack);
      }
      unsigned char symbol = '\0';
      struct tree_t *newTree = (struct tree_t *)malloc(sizeof(struct tree_t));
      if (newTree == NULL) {
        while (stack != NULL) {
          free(stack->tree);
          pop(&stack);
        }
        return NULL;
      }
      newTree->symbol = symbol;
      newTree->right = pop(&stack);
      newTree->left = pop(&stack);
      if (push(&stack, newTree)) {
        while (stack != NULL) {
          free(stack->tree);
          pop(&stack);
        }
        return NULL;
      }
    }
  }
}

int outputDecodeSymbol(struct tree_t *huffmanTree, struct stringHuffman *string,
                       int lastBits, FILE *fin, FILE *fout) {
  static int thisLastByte = 0;
  if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
    fwrite(&(huffmanTree->symbol), sizeof(unsigned char), 1, fout);
    return 0;
  }
  unsigned char symbol1 = 0;
  unsigned char symbol2 = 0;
  if (string->length == 0) {
    if (fread(&symbol1, sizeof(unsigned char), 1, fin)) {
      addSymbol(string, symbol1);
    } else {
      return 1;
    }
  }
  if (string->length < 2 * BYTE) {
    if (fread(&symbol2, sizeof(unsigned char), 1, fin)) {
      addSymbol(string, symbol2);
    } else {
      thisLastByte = 1;
    }
  }
  if (thisLastByte && string->length == lastBits) {
    return 1;
  }
  if (getBit(string) == '1') {
    return outputDecodeSymbol(huffmanTree->right, string, lastBits, fin, fout);
  } else {
    return outputDecodeSymbol(huffmanTree->left, string, lastBits, fin, fout);
  }
}

// static int thisLastBit = 0;
// if (huffmanTree->left == NULL && huffmanTree->right == NULL) {
//   fwrite(&(huffmanTree->symbol), sizeof(unsigned char), 1, fout);
//   return 0;
// }
// unsigned char symbol = 0;
// unsigned char symbolCheckNext = 0;
// if (!fread(&symbolCheckNext, sizeof(unsigned char), 1, fin)) {
//   thisLastBit = 1;
// } else {
//   fseek(fin, -1, SEEK_CUR);
// }
// if (thisLastBit && string->length == lastBits) {
//   return 1;
// }
// if (string->length == 0) {
//   if (fread(&symbol, sizeof(unsigned char), 1, fin)) {
//     addSymbol(string, symbol);
//   } else {
//     return 1;
//   }
//   if (!fread(&symbolCheckNext, sizeof(unsigned char), 1, fin)) {
//     thisLastBit = 1;
//   } else {
//     fseek(fin, -1, SEEK_CUR);
//   }
// }
// if (getBit(string) == '1') {
//   return outputDecodeSymbol(huffmanTree->right, string, lastBits, fin, fout);
// } else {
//   return outputDecodeSymbol(huffmanTree->left, string, lastBits, fin, fout);
// }
