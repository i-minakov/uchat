#include "../../inc/header.h"

char *mx_super_join(char *src1, char *src2, int fl) {
    char *s = mx_strjoin(src1, src2);

    if (fl == 1)
        mx_strdel(&src1);
    else if (fl == 2)
        mx_strdel(&src2);
    else if (fl == 3) {
        mx_strdel(&src1);
        mx_strdel(&src2);
    }
    return s;
}

int mx_arr_size(char **arr) {
    int count = 0;

    if (arr)
        for (int i = 0; arr[i]; i++)
            count++;
    return count;
}

char *mx_add_char(char *str, char c) {
    char *join = mx_strnew(1);

    join[0] = c;
    str = mx_super_join(str, join, 3);
    return str;
}

char **mx_copy_arr(char **s) {
    int len = mx_arr_size(s);
    char **new = (char **)malloc(sizeof(char *) * (len + 1));

    for (int i = 0; s[i]; i++)
        new[i] = mx_strdup(s[i]);
    new[len] = NULL;
    return new;
}

void mx_push_back_t_way(t_way **list, void *data) {
    t_way *node = (t_way *)malloc(sizeof(t_way));

    node->data = data;
    node->back = NULL;
    node->next = NULL;
    if (!*list) {
        *list = node;
        return ;
    }
    for (; (*list)->next; (*list) = (*list)->next);
    (*list)->next = node;
    node->back = (*list);
    *list = node;
}

