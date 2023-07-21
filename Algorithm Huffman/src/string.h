#ifndef LAB5_STRING_H
#define LAB5_STRING_H

#include "main.h"

struct stringHuffman *createString(void);
void addSymbol(struct stringHuffman *string, unsigned char symbol);
void addZero(struct stringHuffman *string);
void addOne(struct stringHuffman *string);
void addSymbolCode(struct stringHuffman *string, struct codeTable *huffmanTable,
                   unsigned char symbol);
unsigned char getBit(struct stringHuffman *string);
unsigned char getSymbol(struct stringHuffman *string);
void destroyString(struct stringHuffman *string);

#endif // LAB5_STRING_H
