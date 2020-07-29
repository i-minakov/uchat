#include "../inc/header.h"

/* search user util */
t_search *mx_create_node_search(char *name, char *path) {
    t_search *new = (t_search *)malloc(sizeof(t_search));

    new->name = mx_strdup(name);
    new->path = mx_strdup(path);
    new->next = NULL;
    return new;
}

void pushfront_search_contact(t_search **head, t_main *m, char *name, char *path) {
    t_search *tmp = mx_create_node_search(name, path);

    if (!head || !*head) {
        *head = tmp;
        (*head)->m = m;
        return;
    }
    tmp->next = *head;
    *head = tmp;
    (*head)->m = m;
}
