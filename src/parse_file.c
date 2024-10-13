#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

void parse_file(const char *filename, Graph *graph) {
    char *content = NULL;
    int file_size = read_file(filename, &content, graph);
    char *content_ptr = content;

    if (file_size == 0) {
        free(content_ptr);
        free_graph(graph, 0);
        handle_file_error(" is empty", filename);
    }

    char *line = NULL;

    if (get_next_line(&content, &line) && line) {
        if (!is_digit_string(line)) {
            free(content_ptr);
            free_graph(graph, 0);
            handle_error("error: line 1 is not valid\n");
        }

        graph->num_islands = mx_atoi(line);
        if (graph->num_islands <= 0 || graph->num_islands > MAX_ISLANDS) {
            free(content_ptr);
            free_graph(graph, 0);
            handle_error("error: line 1 is not valid\n");
        }
    } else {
        free(content_ptr);
        free_graph(graph, 0);
        handle_error("error: line 1 is not valid\n");
    }

    for (int i = 0; i < graph->num_islands; i++) {
        graph->island_names[i] = NULL;
    }

    int pos = 0;
    int lineN = 2;
    long long total_length = 0;
    bool is_duplicate = false;

    while (get_next_line(&content, &line) && line) {
        if (!is_valid_bridge_line(line)) {
            free(content_ptr);
            free_graph(graph, pos);
            handle_line_error(" is not valid", lineN);
        }

        char island1[50], island2[50];
        long long length = mx_atoll(mx_strchr(line, ',') + 1);

        if (length <= 0 || length > INT_MAX) {
            free(content_ptr);
            free_graph(graph, pos);
            handle_line_error(" is not valid", lineN);
        }

        if (total_length > INT_MAX) {
            free(content_ptr);
            free_graph(graph, pos);
            handle_error("error: sum of bridges lengths is too big\n");
        }

        total_length += length;

        char *dash = mx_strchr(line, '-');
        mx_strncpy(island1, line, dash - line);
        island1[dash - line] = '\0';
        mx_strncpy(island2, dash + 1, mx_strchr(line, ',') - dash - 1);
        island2[mx_strchr(line, ',') - dash - 1] = '\0';
        if (mx_strcmp(island1, "\0") == 0 || mx_strcmp(island2, "\0") == 0) {
            free(content_ptr);
            free_graph(graph, pos);
            handle_line_error(" is not valid", lineN);
        }

        if (mx_strcmp(island1, island2) == 0) {
            free(content_ptr);
            free_graph(graph, pos);
            handle_line_error(" is not valid", lineN);
        }
        lineN++;

        if (add_island(graph, island1, pos)) {
            pos++;
        }
        if (add_island(graph, island2, pos)) {
            pos++;
        }

        int idx1 = find_island_index(graph, island1);
        int idx2 = find_island_index(graph, island2);

        if (graph->distances[idx1][idx2] != INT_MAX) {
            is_duplicate = true;
        }
        // mx_printf("idx1: %d; idx2: %d\n", mx_itoa(idx1), mx_itoa(idx2), NULL);

        graph->distances[idx1][idx2] = length;
        graph->distances[idx2][idx1] = length;
    }

    if (pos != graph->num_islands) {
        free(content_ptr);
        free_graph(graph, pos);
        handle_error("error: invalid number of islands\n");
    } else if (is_duplicate) {
        free(content_ptr);
        free_graph(graph, pos);
        handle_error("error: duplicate bridges\n");
    }
    free(content_ptr);
}
