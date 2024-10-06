#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ISLANDS 100
#define BUFFER_SIZE 1024

typedef struct {
    int num_islands;
    char **island_names;
    int distances[MAX_ISLANDS][MAX_ISLANDS];
} Graph;

void handle_error(const char *message);
void handle_line_error(const char *message, int line);
int is_valid_bridge_line(const char *line);
void handle_file_error(const char *message, const char *filename);
void parse_file(const char *filename, Graph *graph);
int read_file(const char *filename, char **content);
int get_next_line(char **content, char **line);
bool add_island(Graph *graph, const char *island, int pos);
int find_island_index(Graph *graph, const char *island);
void pathfinder(Graph *graph);

#endif
