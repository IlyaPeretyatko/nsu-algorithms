#ifndef LAB5_DECODE_H
#define LAB5_DECODE_H

#include "main.h"

void decode(FILE *fin, FILE *fout);
struct tree_t *inputTree(struct stringHuffman *string, FILE *fin);
int outputDecodeSymbol(struct tree_t *huffmanTree, struct stringHuffman *string,
                       int lastBits, FILE *fin, FILE *fout);
int outputTextWithOneSymbol(struct tree_t *huffmanTree,
                            struct stringHuffman *string, int lastBits,
                            FILE *fin, FILE *fout);

#endif // LAB5_DECODE_H
