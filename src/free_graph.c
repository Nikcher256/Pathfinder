#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

void free_graph(Graph *graph, int islands) {
    for (int i = 0; i < islands; i++) {
        free(graph->island_names[i]);
    }
    free(graph->island_names);
}
