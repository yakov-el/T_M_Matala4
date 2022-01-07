#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

// return index of vertex with a 'number'
int index_of_vertex(Graph *graph, int number){
    Node* nodes = graph->nodes;
    for (int i = 0; i < graph->V; ++i) {
        if (nodes[i].number == number)
            return i;
    }
    return -1;
}

// A utility function to create a new adjacency list node
Edge *add_edge(int dest, int weight) {
    Edge *newNode =
            (Edge *) malloc(sizeof(Edge));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
Graph *create_graph(int num_of_vertexes) {
    Graph *graph =
            (Graph *) malloc(sizeof(Graph));

    graph->V = 0;
    graph->nodes = NULL;

    return graph;
}

// Adds an edge to an directed graph
void addEdge(Graph *graph, int src, int dest, int weight) {
    struct Edge *check = NULL;
    struct Edge *newNode = add_edge(dest, weight);

    if (index_of_vertex(graph, dest) < 0)
        add_vertex(graph, dest);

    int index = index_of_vertex(graph, src);
    if (index < 0) {
        add_vertex(graph, src);
        index = index_of_vertex(graph, src);
    }

    if (graph->nodes[index].head == NULL) {
        newNode->next = graph->nodes[index].head;
        graph->nodes[index].head = newNode;
    } else {

        check = graph->nodes[index].head;
        while (check->next != NULL) {
            check = check->next;
        }
        //graph->nodes[src].head = newNode;
        check->next = newNode;
    }
}

// adds a vertex to the graph
void add_vertex(Graph *graph, int number){
    int index_of = index_of_vertex(graph, number);

    if(index_of == -1) {
        int V = graph->V;
        graph->nodes =
                (Node *) realloc( graph->nodes, (V + 1) * sizeof(Node));
        graph->nodes[V].head = NULL;
        graph->nodes[V].number = number;
        graph->V = V + 1;
    }

}

// removes a vertex to the graph
void remove_vertex(Graph *graph, int src){
    int index = index_of_vertex(graph, src);
    if (index < 0) {
        return;
    }

    // remove all edges that goes out of "src"
    free_memory(&(graph->nodes[index].head));

    graph->nodes[index].head = NULL;

    // remove all edges that goes into "src
    remove_edges_with_dest(graph, src);
}

void remove_edges_with_dest(Graph *graph, int key)
{
    for(int i=0; i<graph->V;i++){
        struct Edge** head_ref = &(graph->nodes[i].head);

        // Store head node
        struct Edge *temp = *head_ref, *prev;

        // If head node itself holds the key to be deleted
        if (temp != NULL && temp->dest == key) {
            *head_ref = temp->next; // Changed head
            free(temp); // free old head
            return;
        }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (temp != NULL && temp->dest != key) {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL)
            return;

        // Unlink the node from linked list
        prev->next = temp->next;

        free(temp);
    }

}



// A utility function to print the adjacency list
// representation of graph
void print_graph(Graph *graph) {

    for (int index = 0; index < (graph)->V; index++) {
        Edge *pEdge = (graph)->nodes[index].head;
        // skip "empty" places
        if(pEdge == NULL)
            continue;
        int v_num = (graph)->nodes[index].number;
        printf("Edges list of vertex %d\n", v_num);
        while (pEdge) {
            printf("%d -> %d (w = %d)\n", v_num, pEdge->dest, pEdge->weight);
            pEdge = pEdge->next;
        }
        printf("\n");
    }
}

// free all used memory by Vertex
void free_memory(Edge** head_ref){
    Edge *current = *head_ref;
    Edge* temp = NULL;

    while (current) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

// free all used memory by Graph
void free_all(Graph* graph) {
    if(graph == NULL)
        return;

    for (int i = 0; i < graph->V; ++i)
        free_memory(&graph->nodes[i].head);

    free(graph->nodes);
    free(graph);
}
