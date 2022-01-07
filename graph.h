#ifndef GRAPH_
#define GRAPH_


typedef struct Edge{
    int dest;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Node{
    struct Edge *head;
    int number;
} Node;

typedef struct Graph{
    int V;
    Node *nodes;
} Graph;

int index_of_vertex(Graph *graph, int number);

Edge *add_edge(int dest, int weight);


Graph *create_graph(int num_of_vertexes);

void addEdge(Graph *graph, int src, int dest, int weight);

void add_vertex(Graph *graph, int number);

void remove_vertex(Graph *graph, int src);

void remove_edges_with_dest(Graph *graph, int key);

void print_graph(Graph *graph);

void free_memory(Edge **head_ref);

void free_all(Graph *graph);

#endif