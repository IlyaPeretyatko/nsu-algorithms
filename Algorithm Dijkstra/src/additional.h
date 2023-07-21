#ifndef LAB9_ADDITIONAL_H
#define LAB9_ADDITIONAL_H

#include "algorithmDijkstra.h"

int createGraph(struct graph *graph, int N);
void destroyGraph(struct graph *graph);
void pushMatrix(int start, int end, int length, struct graph *graph);
int getMatrixValue(int start, int end, struct graph *graph);

#endif // LAB9_ADDITIONAL_H
