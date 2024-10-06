#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

typedef struct {
    char *route;
    char *distance;
} Path;

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

void print_path(const char *start_island, const char *end_island, const Path *path) {
    mx_printstr("========================================\n");
    mx_printf("Path: %s -> %s\n", start_island, end_island, NULL);
    mx_printf("Route: %s\n", path->route, NULL, NULL);
    mx_printf("Distance: %s\n", path->distance, NULL, NULL);
    mx_printstr("========================================\n");
}

int min_distance(int dist[], bool visited[], int num_islands) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < num_islands; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void sort_paths_by_u(Path paths[], int path_count, int parent[MAX_ISLANDS][MAX_ISLANDS], int to) {
    for (int i = 0; i < path_count - 1; i++) {
        for (int j = 0; j < path_count - i - 1; j++) {
            if (parent[to][j] > parent[to][j + 1]) {
                // Swap the paths
                Path temp = paths[j];
                paths[j] = paths[j + 1];
                paths[j + 1] = temp;
            }
        }
    }
}

void find_and_print(Graph *graph, int from, int to) {
    int num_islands = graph->num_islands;
    int dist[MAX_ISLANDS];
    bool visited[MAX_ISLANDS] = {false};
    int parent[MAX_ISLANDS][MAX_ISLANDS];

    for (int i = 0; i < num_islands; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        for (int j = 0; j < MAX_ISLANDS; j++) {
            parent[i][j] = -1;
        }
    }

    dist[from] = 0;

    for (int count = 0; count < num_islands - 1; count++) {
        int u = min_distance(dist, visited, num_islands);
        visited[u] = true;

        for (int v = 0; v < num_islands; v++) {
            if (!visited[v] && graph->distances[u][v] != INT_MAX && dist[u] != INT_MAX) {
                int new_distance = dist[u] + graph->distances[u][v];
                if (new_distance < dist[v]) {
                    dist[v] = new_distance;
                    for (int i = 0; i < MAX_ISLANDS; i++) {
                        parent[v][i] = -1;
                    }
                    parent[v][0] = u;
                } else if (new_distance == dist[v]) {
                    for (int i = 0; i < MAX_ISLANDS; i++) {
                        if (parent[v][i] == -1) {
                            parent[v][i] = u;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (dist[to] == INT_MAX) {
        mx_printstr("No path found\n");
        return;
    }

    Path paths[MAX_ISLANDS * MAX_ISLANDS];
    int path_count = 0;
    int stack[MAX_ISLANDS];
    build_paths(graph, parent, stack, 0, to, from, paths, &path_count);

    sort_paths_by_u(paths, path_count, parent, to);

    for (int i = 0; i < path_count; i++) {
        print_path(graph->island_names[from], graph->island_names[to], &paths[i]);
        free(paths[i].route);
        free(paths[i].distance);
    }
}

void pathfinder(Graph *graph) {
    for (int i = 0; i < graph->num_islands; ++i) {
        for (int j = i + 1; j < graph->num_islands; ++j) {
            find_and_print(graph, i, j);
        }
    }
}
