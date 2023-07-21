#ifndef LAB9_OUTPUT_H
#define LAB9_OUTPUT_H

#include "algorithmDijkstra.h"

bool CheckOverflow(int endIndex, int countVertex, const long long *path);
void outputDistance(struct graph *graph, long long *path);
void outputPath(struct graph *graph, long long *path, int endIndex);

#endif // LAB9_OUTPUT_H
