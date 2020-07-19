#include "../inc/header.h"

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

// static int mx_arrsize_malloc(char **arr) {
//     int count = 2;

//     if (!arr)
//         return count;
//     for (int i = 0; arr[i]; i++)
//         count++;
//     return count;
// }
// char **mx_arrjoin(char **arr, char *str) {
//     char **new_arr = (char **)malloc(sizeof(char *) * mx_arrsize_malloc(arr));

//     for (int i = 0; i < mx_arrsize_malloc(arr); i++) {
//         if (i == mx_arrsize_malloc(arr) - 2)
//             new_arr[i] = mx_strdup(str);
//         else if (i == mx_arrsize_malloc(arr) - 1)
//             new_arr[i] = NULL;
//         else
//             new_arr[i] = mx_strdup(arr[i]);
//     }
//     if (arr)
//         mx_del_strarr(&arr);
//     return new_arr;
// }

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

void *mx_mom(void *restrict dst, const void *restrict src, size_t n, size_t i) {
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

void mx_unset_file_node(t_way **list) {
    t_way *next = NULL;
    t_way *back = NULL;

    if ((*list)->next)
        next = (*list)->next;
    if ((*list)->back)
        back = (*list)->back;
    if (next && back)
        next->back = back;
    else if (next)
        next->back = NULL;
    if (back && next)
        back->next = next;
    else if (back)
        back->next = NULL;
    mx_free_node(list);
    if (next)
        *list = next;
    else if (back)
        *list = back;
    else
        *list = NULL;
}

void mx_file_format(char **arr, SSL *ssl, char ch1, char ch2) {
    char ch[SIZE_SEND];

    mx_memset(ch, '\0', SIZE_SEND);
    ch[0] = ch1;
    ch[1] = ch2;
    mx_mom(ch, arr[mx_arr_size(arr) - 1], SIZE_SEND_LESS, 0);
    SSL_write(ssl, ch, SIZE_SEND);
}

void mx_file_bites(FILE *file, SSL *ssl, char ch1, char ch2) {
    char send[SIZE_SEND];
    char ch;

    while (fread(&ch, 1, 1, file) != 0) {
        mx_memset(send, '\0', SIZE_SEND);
        send[0] = ch1;
        send[1] = ch2;
        send[2] = ch;
        SSL_write(ssl, send, SIZE_SEND);
        mx_memset(send, '\0', SIZE_SEND);
    }
}

void mx_file_size_close(SSL *ssl, char *str, char ch1, char ch2) {
    char send[SIZE_SEND];

    mx_memset(send, '\0', SIZE_SEND);
    send[0] = ch1;
    send[1] = ch2;
    mx_mom(send, str, mx_strlen(str), 0);
    SSL_write(ssl, send, SIZE_SEND);
}

void mx_bites_str(SSL *ssl, char *json, char ch1) {
    char ch[SIZE_SEND];

    for (int i = 0; i < mx_strlen(json); i += SIZE_SEND_LESS) {
        mx_memset(ch, '\0', SIZE_SEND);
        mx_mom(ch, json, SIZE_SEND_LESS, i);
        ch[0] = ch1;
        if (mx_strlen(json) > i + SIZE_SEND_LESS)
            ch[1] = 'S';
        else
            ch[1] = 'E';
        SSL_write(ssl, ch, SIZE_SEND);
    }
}

void mx_del_list(t_list **list, int flag) {
    if (!list || !*list)
        return;
    t_list *i = *list;

    for (; i; i = i->next) {
        if (flag == 0)
            mx_free_table_list((t_table_list *)i->data);
        else if (flag == 1)
            mx_free_history((t_history *)i->data);
        else if (flag == 2)
            mx_strdel((char **)&i->data);
    }
    mx_free_list(list);
}

void mx_static_read(char ch[], char **str) {
    for (int i = 2; ch[i]; i++)
        *str = mx_add_char(*str, ch[i]);
}

void mx_del_if_exist(char *name) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("./");
    while ((entry = readdir(dir)) != NULL)
        if (mx_strcmp(entry->d_name, ".") != 0
            && mx_strcmp(entry->d_name, "..") != 0
            && mx_strcmp(entry->d_name, name) == 0)
            remove(name);
    closedir(dir);
}

void mx_del_file(FILE *file, char **size, char **name) {
    if (file && name && size && *size && *name) {
        fclose(file);
        remove(*name);
        mx_strdel(size);
        mx_strdel(name);
    }
}

void mx_check_file_size(FILE *file, char **size, char **name) {
    if (file && name && size && *size && *name) {
        int len = 0;

        fclose(file);
        file = fopen(*name, "rb");
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fseek(file, 0, SEEK_SET);
        if (len != mx_atoi(*size))
            remove(*name);
        fclose(file);
        file = NULL;
        mx_strdel(size);
        mx_strdel(name);
    }
}
