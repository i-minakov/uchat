#include "../../inc/header.h"

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
    if (SSL_write(ssl, ch, SIZE_SEND) == -1)
        return ;
}

void mx_file_bites(FILE *file, SSL *ssl, char ch1, char ch2) {
    char send[SIZE_SEND];
    char ch;

    while (fread(&ch, 1, 1, file) != 0) {
        mx_memset(send, '\0', SIZE_SEND);
        send[0] = ch1;
        send[1] = ch2;
        send[2] = ch;
        if (SSL_write(ssl, send, SIZE_SEND) == -1)
            return ;
        mx_memset(send, '\0', SIZE_SEND);
    }
}

void mx_file_size_close(SSL *ssl, char *str, char ch1, char ch2) {
    char send[SIZE_SEND];

    mx_memset(send, '\0', SIZE_SEND);
    send[0] = ch1;
    send[1] = ch2;
    mx_mom(send, str, mx_strlen(str), 0);
    if (SSL_write(ssl, send, SIZE_SEND) == -1)
        return ;
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
        if (SSL_write(ssl, ch, SIZE_SEND) == -1)
            return ;
    }
}

