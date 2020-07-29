#include "../../inc/header.h"

void mx_replace(char **old, char *new) {
    mx_strdel(old);
    *old = mx_strdup(new);
}

bool mx_for_file(char *json) {
    char *command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    if ((mx_strcmp(command, "mx_recv_new_mess") == 0 && mx_atoi(arr[3]) == 1)
        || (mx_strcmp(command, "mx_add_new_user") == 0)
        || (mx_strcmp(command, "mx_change_img") == 0)) {
            mx_strdel(&command);
            mx_del_strarr(&arr);
            return true;
        }
    mx_strdel(&command);
    mx_del_strarr(&arr);
    return false;
}

void mx_push_file_way(t_way **list, void *data) {
    t_way *node = (t_way *)malloc(sizeof(t_way));

    node->data = data;
    node->back = NULL;
    node->next = NULL;
    if (!*list) {
        *list = node;
        return ;
    }
    t_way *i = *list;

    for (; i->next; i = i->next);
    i->next = node;
    node->back = i;
}

void mx_free_node(t_way **list) {
    (*list)->data = NULL;
    (*list)->next = NULL;
    (*list)->back = NULL;
    free(*list);
    *list = NULL;
}

void *mx_mom(void *restrict dst,
             const void *restrict src,
             size_t n, size_t i) {
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;

    d += 2;
    s += i;
    for ( ; n--; ) {
        if (*s == 0) {
            *d = *s;
            d++;
            return d;
        }
        *d = *s;
        d++;
        s++;
    }
    return NULL;
}

