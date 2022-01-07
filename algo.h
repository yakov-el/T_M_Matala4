#ifndef ALGO_
#define ALGO_

#include "graph.h"
#include <limits.h>

#define MAX_WEIGHT 999      // MAX for weight

int find_edge_weight(Graph graph, int src, int dest);
int max_num(Graph graph);
void dijkstra(Graph graph, int src, int* dists);
int find_ssp(Graph graph, int src, int dest);


int find_tsp(const Graph graph, int* vertexes, int count);
int least(int c, Graph graph, int* cost, int * completed);
void min_cost(int city, Graph graph, int* cost, int* completed);

#endif