#ifndef LAB9_INPUT_H
#define LAB9_INPUT_H

#include "additional.h"
#include "algorithmDijkstra.h"

int input(struct graph *graph);
int inputEdges(struct graph *graph, int countEdges);
int inputCountEdges(int N);
int inputStartEnd(struct graph *graph);
int inputCountVertex(struct graph *graph);

#endif // LAB9_INPUT_H
