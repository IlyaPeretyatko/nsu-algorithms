#ifndef LAB5_CODE_H
#define LAB5_CODE_H

#include "main.h"

void code(FILE *fin, FILE *fout, int fromTerminal);
int initQueue(int *freqTable, struct list_t **list, int *countDifferentSymbol);
struct tree_t *buildingHuffmanTree(struct list_t **list);
struct codeTable *buildingHuffmanTable(struct tree_t *huffmanTree,
                                       int countSymbol);
int initHuffmanTable(struct tree_t *huffmanTree, struct codeTable *huffmanTable,
                     unsigned char *code, int length);
void outputTree(struct tree_t *huffmanTree, struct stringHuffman *string,
                FILE *fout);
void codeText(struct codeTable *huffmanTable, struct stringHuffman *string,
              FILE *fin, FILE *fout);
void codeTextWithOneSymbol(struct stringHuffman *string, FILE *fin, FILE *fout);
void outputCodingSymbol(struct stringHuffman *string, FILE *fout);
void destroyTree(struct tree_t **tree);
void destroyTable(struct codeTable *huffmanTable);
void getCountNodes(struct tree_t *huffmanTree, int *lastBits);
int calculationLastBits(struct tree_t *huffmanTree,
                        struct codeTable *huffmanTable, const int *freqTable);

#endif // LAB5_CODE_H
