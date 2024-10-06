#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
    if (head == NULL || *head == NULL) {
        return;
    }

    t_list *current = *head;

    if (current->next == NULL) {
        free(current);
        *head = NULL;
        return;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }

    t_list *last_node = current->next;
    current->next = NULL;
    free(last_node);
}
