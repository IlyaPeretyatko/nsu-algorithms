#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct stringHuffman *createString(void) {
  struct stringHuffman *string =
      (struct stringHuffman *)malloc(sizeof(struct stringHuffman));
  if (string == NULL) {
    return NULL;
  }
  string->code =
      (unsigned char *)malloc((CHAR_COUNT + BYTE) * sizeof(unsigned char));
  if (string->code == NULL) {
    free(string);
    return NULL;
  }
  string->max = CHAR_COUNT + BYTE;
  string->begin = 0;
  string->end = 0;
  string->length = 0;
  return string;
}

void addSymbol(struct stringHuffman *string, unsigned char symbol) {
  unsigned char mask = (int)(1 << 7);
  for (int i = 0; i < 8; ++i) {
    if (mask & symbol) {
      addOne(string);
    } else {
      addZero(string);
    }
    symbol <<= 1;
  }
}

void addZero(struct stringHuffman *string) {
  string->code[string->end] = '0';
  string->length += 1;
  string->end = (string->end + 1) % string->max;
}

void addOne(struct stringHuffman *string) {
  string->code[string->end] = '1';
  string->length += 1;
  string->end = (string->end + 1) % string->max;
}

void addSymbolCode(struct stringHuffman *string, struct codeTable *huffmanTable,
                   unsigned char symbol) {
  int index = 0;
  for (int i = 0; i < huffmanTable->max; ++i) {
    if (huffmanTable->table[i].symbol == symbol) {
      index = i;
      break;
    }
  }
  for (int i = 0; i < huffmanTable->table[index].length; ++i) {
    if (huffmanTable->table[index].code[i] == '1') {
      addOne(string);
    } else {
      addZero(string);
    }
  }
}

unsigned char getSymbol(struct stringHuffman *string) {
  unsigned char symbol = 0;
  for (int i = 0; i < 8; ++i) {
    unsigned char bit = getBit(string);
    if (bit == '0') {
      continue;
    }
    symbol |= (1 << (7 - i));
  }
  return symbol;
}

unsigned char getBit(struct stringHuffman *string) {
  unsigned char bit = string->code[string->begin];
  string->length -= 1;
  string->begin = (string->begin + 1) % string->max;
  return bit;
}
