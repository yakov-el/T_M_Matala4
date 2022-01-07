#ifndef MAIN_
#define MAIN_

#include "algo.h"
#include "utils.h"

#define MAX_COMMAND_LEN 200

struct Graph;

Graph *handle_create_graph_input(char *input);

void handle_create_vertex_input(char *input, Graph *graph);

void handle_delete_vertex_input(char *input, Graph *graph);

void handle_delete_ssp_input(char *input, Graph graph);

void handle_tsp_input (char *input, Graph graph);
#endif