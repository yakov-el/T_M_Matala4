#include "algo.h"
#include <stdbool.h>
#include <stdlib.h>

// return the weight of edge from 'src' to 'dest'
int find_edge_weight(Graph graph, int src, int dest) {
    int index = index_of_vertex(&graph, src);
    if (index < 0)
        return MAX_WEIGHT;

    Edge *p_crawl = (graph).nodes[index].head;

    while (p_crawl) {
        if (p_crawl->dest == dest) {
            return p_crawl->weight;
        }
        p_crawl = p_crawl->next;
    }
    return MAX_WEIGHT;        // BIG enough
}

int max_num(Graph graph){
    int max = -1;
    for (int i = 0; i < graph.V; ++i) {
        if(graph.nodes[i].number > max)
            max = graph.nodes[i].number;
    }
    return max;
}


// function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int min_distance(const int *dist, const bool *sptSet, int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(Graph graph, int src, int* dists)
{
    int V = max_num(graph)+1;//?+1??

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dists[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dists[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // picks the minimum distance vertex from the set of vertices not
        int u = min_distance(dists, sptSet, V);

        // mark the picked vertex as processed
        sptSet[u] = true;

        int w;
        // Update dists value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {


            w = find_edge_weight(graph, u, v);

            if (!sptSet[v] && w && dists[u] != MAX_WEIGHT
                && dists[u] + w  < dists[v]) {
                dists[v] = dists[u] +w ;
            }
        }
    }

    for (int j = 0; j < V; ++j) {
        if(dists[j] >= MAX_WEIGHT || dists[j] < -1)
            dists[j] = -1;
    }
}

// find the weight of the shortest path (by Dijkstra) from 'src' to 'dest'
int find_ssp(const Graph graph, int src, int dest)
{
    int x = max_num(graph);
    int dists[x];
    dijkstra(graph, src, dists);
    int distance = dists[dest];
    return distance == MAX_WEIGHT ? -1 : distance;
}

// type for callback that is called for every permutation
typedef void (*heap_callback)(int* vertexes, int count);

void heap_swap(int* pointer_a, int* pointer_b) {

    int integer_a = *pointer_a;
    int integer_b = *pointer_b;
    *pointer_a = integer_b;
    *pointer_b = integer_a;

}

// generates the next permutation using Heap's algorithm
void heap_permutations(int* vertexes, int count, int size, heap_callback callback) {

    if (size == 1)
        callback(vertexes, count);

    for (int i = 0; i < size; i++) {
        heap_permutations(vertexes, count, size - 1, callback);

        if ((size & 1) == 0) // odd
            heap_swap(&vertexes[0], &vertexes[size -1]);
        else // even
            heap_swap(&vertexes[i], &vertexes[size -1]);

    }

}

Graph callback_graph;
bool callback_success;
int callback_distance;

// callback for testing all permutations of the path in the TSP
void callback_tsp(int* vertexes, int count) {

    int shortest_travel = 0;
    bool useless_path = false;

    for (int i = 1; i < count; i++) {
        int src = vertexes[i - 1];
        int dest = vertexes[i];
        int ssp = find_ssp(callback_graph, src, dest);
        if (ssp < 0) { // this permutation is useless
            useless_path = true;
            break;
        }
        shortest_travel += ssp;
    }

    if (!useless_path && shortest_travel < callback_distance) {
        callback_distance = shortest_travel;
        callback_success = true;
    }

}

// find the weight of the shortest path (by tsp) from 'src' to 'dest'
int find_tsp(const Graph graph, int* vertexes, int count)
{
    callback_distance = INT_MAX;
    callback_graph = graph;
    callback_success = false;
    heap_permutations(vertexes, count, count, callback_tsp);
    if (!callback_success) // not a single permutation was useful
        return (-1);

    return callback_distance;
}


int least(int c, Graph graph, int* cost, int * completed) {
    int i, nc = MAX_WEIGHT;
    int n = max_num(graph)+1;

    int min = 10000, kmin = INT_MIN;

    for (i = 0; i < n; i++) {
        int ci = find_edge_weight(graph, c, i);
        int ic = find_edge_weight(graph, i, c);

        if ((ci != 0) && (completed[i] == 0)) {
            if (ci + ic < min) {
//                min = ic + ci;
//                kmin = ci;
//                nc = i;
            }
        }
    }

    if (min < MAX_WEIGHT)
        *cost += kmin;

    return nc;
}


void min_cost(int city, Graph graph, int* cost, int* completed) {

    completed[city] = 1;
    int ncity = least(city, graph, cost, completed);

    if (ncity == MAX_WEIGHT) {
        ncity = 0;
        int weight = find_edge_weight(graph, city, ncity)+2;
        if(weight < MAX_WEIGHT)
            *cost += weight;

        return;
    }

    min_cost(ncity, graph, cost, completed);
}
