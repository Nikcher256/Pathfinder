#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"
bool add_island(Graph *graph, const char *island, int pos) {
    for (int i = 0; i < graph->num_islands; i++) {
        if (graph->island_names[i] != NULL && mx_strcmp(graph->island_names[i], island) == 0) {
            return false;
        }
    }
    graph->island_names[pos] = malloc(mx_strlen(island) + 1);
    mx_strcpy(graph->island_names[pos], island);
    return true;
}
