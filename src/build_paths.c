#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

void build_paths(Graph *graph, int parent[MAX_ISLANDS][MAX_ISLANDS], int stack[], int stack_size,
                 int to, int from, Path *paths, int *path_count) {
    stack[stack_size++] = to;

    if (to == from) {
        char route[MAX_ISLANDS * 10] = "";
        char distance_str[100] = "";
        int total_distance = 0;

        for (int i = stack_size - 1; i >= 0; i--) {
            mx_strcat(route, graph->island_names[stack[i]]);
            if (i != 0) {
                mx_strcat(route, " -> ");
            }
        }

        bool equel = false;

        for (int i = stack_size - 1; i > 0; i--) {
            int segment_distance = graph->distances[stack[i]][stack[i - 1]];
            total_distance += segment_distance;

            char *segment_str = mx_itoa(segment_distance);

            if (i < stack_size - 1) {
                equel = true;
                mx_strcat(distance_str, " + ");
                mx_strcat(distance_str, segment_str);
            } else {
                mx_strcpy(distance_str, segment_str);
            }
            free(segment_str);
        }

        if (equel) {
            char *total_distance_str = mx_itoa(total_distance);
            mx_strcat(distance_str, " = ");
            mx_strcat(distance_str, total_distance_str);
            free(total_distance_str);
        }

        paths[*path_count].route = mx_strdup(route);
        paths[*path_count].distance = mx_strdup(distance_str);
        (*path_count)++;

        return;
    }

    for (int i = 0; parent[to][i] != -1; i++) {
        build_paths(graph, parent, stack, stack_size, parent[to][i], from, paths, path_count);
    }
}
