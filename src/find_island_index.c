#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

int find_island_index(Graph *graph, const char *island) {
    for (int i = 0; i < graph->num_islands; i++) {
        if (mx_strcmp(graph->island_names[i], island) == 0) {
            return i;
        }
    }
    return -1;
}
