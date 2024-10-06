#include "../inc/libmx.h"

static t_list *merge_sorted_lists(t_list *l1, t_list *l2, bool (*cmp)(void *, void *)) {
    t_list dummy;
    t_list *tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2) {
        if (cmp(l1->data, l2->data)) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;

    return dummy.next;
}

static void split_list(t_list *source, t_list **front_ref, t_list **back_ref) {
    t_list *fast;
    t_list *slow;
    if (!source || !source->next) {
        *front_ref = source;
        *back_ref = NULL;
        return;
    }

    slow = source;
    fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL;
}

static t_list *merge_sort(t_list *head, bool (*cmp)(void *, void *)) {
    if (!head || !head->next) {
        return head;
    }

    t_list *front;
    t_list *back;

    split_list(head, &front, &back);

    front = merge_sort(front, cmp);
    back = merge_sort(back, cmp);

    return merge_sorted_lists(front, back, cmp);
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (!lst || !cmp) {
        return NULL;
    }

    return merge_sort(lst, cmp);
}
