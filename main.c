#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

// handles creating a graph input command
Graph *handle_create_graph_input(char *input) {
    char string[1000];    // helper
    strcpy(string, input);

    char *token = trim(strtok(string, "n"));
    int num_of_vertexes = (int) (token[0]) - '0';

    Graph *graph = create_graph(num_of_vertexes);
    token = strtok(NULL, "n");
    while (token != NULL) {
        remove_spaces(token);       // removes spaces

        int vertex_num = (int) (token[0]) - 48;

        add_vertex(graph, vertex_num);

        for (int i = 1; i < strlen(token); i += 2) {
            int dest = (int) (token[i]) - 48;
            int weight = (int) (token[i + 1]) - 48;
            addEdge(graph, vertex_num, dest, weight);
        }

        token = strtok(NULL, "n");
    }
    return graph;
}

// handles creating a vertex input command
void handle_create_vertex_input(char *input, Graph *graph) {
    char string[1000];    // helper
    strcpy(string, input);

    char *token = strtok(string, " ");
    int vertex_num = (int) (token[0]) - 48;
    token = strtok(NULL, " ");

    remove_vertex(graph, vertex_num);
    add_vertex(graph, vertex_num);

    int count = 0;
    int dest;
    int weight;
    while (token != NULL) {
        if (count % 2 == 0) {
            dest = (int) (token[0]) - 48;
        } else {
            weight = (int) (token[0]) - 48;
            addEdge(graph, vertex_num, dest, weight);
        }
        count++;
        token = strtok(NULL, " ");
    }
}

// handles deleting a vertex input command
void handle_delete_vertex_input(char *input, Graph *graph) {
    remove_spaces(input);
    int vertex = atol(&input[0]);
    remove_vertex(graph, vertex);
}

// handles the shortest path input command
void handle_delete_ssp_input(char *input, Graph graph){
    char string[1000];    // helper
    strcpy(string, input);

    char *token = strtok(string, " ");
    int count = 0;
    int src;
    int dest;
    while (token != NULL) {
        if (count % 2 == 0) {
            src = (int) (token[0]) - 48;
        } else {
            dest = (int) (token[0]) - 48;
        }
        count++;
        token = strtok(NULL, " ");
    }

    int ssp_distance = find_ssp(graph, src, dest);
    printf("Dijsktra shortest path: %d \n", ssp_distance);
}

// handles calculating tsp  input command
void handle_tsp_input (char *input, Graph graph){
    char string[1000] = {' '};    // helper
    strcpy(string, input);

    char *token = trim(strtok(string, " "));
    int vertexes_count = (int) (token[0]) - '0';
    token = strtok(NULL, " ");
    int vertexes[vertexes_count];

    int count = 0;
    while (token != NULL) {
        int vertex = (int) (token[0]) - '0';
        vertexes[count] = vertex;
        token = strtok(NULL, " ");
        count++;
    }

    int dist = find_tsp(graph, vertexes, count);
    printf("TSP shortest path: %d \n", dist);
}

int main() {
    Graph* graph = NULL;
    char command[MAX_COMMAND_LEN];      // string that keeps the current command

    fgets(command, MAX_COMMAND_LEN, stdin);

    char sub_commands[20][MAX_COMMAND_LEN];
    int count = 0;
    int lastCommandIndex;

    char temp[MAX_COMMAND_LEN];

    // divide long commend into sub-commend "blocks"
    for(int k=0; command[k] != '\0';){
        if(isalpha(command[k])){
            lastCommandIndex = k;
            do{
                k++;
                if(command[k] == '\0')
                    break;
                if(command[k] >= 'A' && command[k] <= 'Z')
                    break;
            }while (1);

            strncpy(temp, &command[lastCommandIndex], (k - lastCommandIndex) - 1);
            temp[(k - lastCommandIndex) - 1] = '\0';
            strcpy(sub_commands[count] , temp);

            count++;
        }
        else k++;
    }

    // executing each command
    for (int i = 0; i < count; ++i) {
        char* curr_command = sub_commands[i];

        char letter = curr_command[0];

        switch (letter) {
            // add new graph
            case 'A':
                free_all(graph);
                graph = handle_create_graph_input(&curr_command[1]);
                break;

                // add new vertex
            case 'B':
                handle_create_vertex_input(&curr_command[1], graph);
                break;

                // delete a vertex
            case 'D':
                handle_delete_vertex_input(&curr_command[1], graph);
                break;

                // shortest path
            case 'S':
                handle_delete_ssp_input(&curr_command[1], *graph);
                break;

                // TSP
            case 'T':
                handle_tsp_input(&curr_command[1], *graph);
                break;

                // for debug usage
            case 'P':
                print_graph(graph);
                break;

            default:
                break;
        }
    }

    free_all(graph);
    return 0;
}