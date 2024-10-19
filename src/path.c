#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

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

int get_island_priority(const char *island_name, char *island_names[], int num_islands) {
    for (int i = 0; i < num_islands; i++) {
        if (mx_strcmp(island_name, island_names[i]) == 0) {
            return i;  // Return the index as priority
        }
    }
    return INT_MAX;  // Return max value if not found
}

// Sort paths based on the priority of the first island in the path
void sort_paths_by_priority(Path paths[], int path_count, char *island_names[], int num_islands) {
    for (int i = 0; i < path_count - 1; i++) {
        for (int j = 0; j < path_count - i - 1; j++) {
            // Create copies of the route strings for tokenization
            char *route_copy1 = mx_strdup(paths[j].route);
            char *route_copy2 = mx_strdup(paths[j + 1].route);

            // Tokenize the route copies
            char *tokens1[100];  // Array to hold the islands
            char *tokens2[100];  // Array to hold the islands
            int count1 = 0, count2 = 0;
            // mx_printf("%s\n%s\n", paths[j].route, paths[j + 1].route, NULL);
            // Split the first route into islands
            char *token1 = mx_strtok(route_copy1, " -> ");
            while (token1 != NULL) {
                tokens1[count1++] = token1;
                token1 = mx_strtok(NULL, " -> ");
            }

            // Split the second route into islands
            char *token2 = mx_strtok(route_copy2, " -> ");
            while (token2 != NULL) {
                tokens2[count2++] = token2;
                token2 = mx_strtok(NULL, " -> ");
            }

            // Compare islands in the path except the first and last
            for (int k = 1; k < count1 && k < count2; k++) {  // Skip first and last
                // Get priorities
                int priority1 = get_island_priority(tokens1[k], island_names, num_islands);
                int priority2 = get_island_priority(tokens2[k], island_names, num_islands);

                // mx_printf("Compare %s and %s with priority: ", tokens1[k], tokens2[k], NULL);
                // mx_printf("%d and %d\n", mx_itoa(priority1), mx_itoa(priority2), NULL);

                if (priority1 > priority2) {  // Sort in ascending order
                    // Swap the paths
                    // mx_printstr("swap\n");
                    Path temp = paths[j];
                    paths[j] = paths[j + 1];
                    paths[j + 1] = temp;
                    break;  // Break to re-evaluate paths
                } else if (priority1 < priority2) {
                    break;
                }
            }

            // Free the allocated memory for the copied routes
            free(route_copy1);
            free(route_copy2);
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

    sort_paths_by_priority(paths, path_count, graph->island_names, graph->num_islands);

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
