#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/libmx.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        char *message = "usage: ./pathfinder [filename]\n";
        write(2, message, mx_strlen(message));
        exit(EXIT_FAILURE);
    }

    Graph graph;
    graph.num_islands = 0;
    graph.island_names = malloc(sizeof(char *) * MAX_ISLANDS);

    for (int i = 0; i < MAX_ISLANDS; i++) {
        for (int j = 0; j < MAX_ISLANDS; j++) {
            graph.distances[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    parse_file(argv[1], &graph);

    pathfinder(&graph);

    for (int i = 0; i < graph.num_islands; i++) {
        free(graph.island_names[i]);
    }
    free(graph.island_names);

    return 0;
}
