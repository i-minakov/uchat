#include "../../inc/header.h"

/* delete node */
static void mx_free_struct(t_node **node, int flag) {
    if (!node || !*node)
        return;
    mx_strdel(&(*node)->json);
    mx_strdel(&(*node)->user);
    mx_strdel(&(*node)->chat);
    mx_strdel(&(*node)->size);
    mx_strdel(&(*node)->history);
    mx_strdel(&(*node)->for_files->file_size);
    mx_strdel(&(*node)->for_files->file_name);
    if ((*node)->ssl && flag != 1)
        SSL_free((*node)->ssl);
    if ((*node)->ctx && flag != 1)
        SSL_CTX_free((*node)->ctx);
    if ((*node)->client != -1)
        close((*node)->client);
    if ((*node)->for_files->file)
        fclose((*node)->for_files->file);
    free((*node)->for_files);
    free(*node);
    *node = NULL;
}

static void mx_unset_node_adt(t_way **list, t_way **next, t_way **back) {
    if ((*list)->next)
        (*next) = (*list)->next;
    if ((*list)->back)
        (*back) = (*list)->back;
    if (*next && *back)
        (*next)->back = *back;
    else if (*next)
        (*next)->back = NULL;
    if (*back && *next)
        (*back)->next = *next;
    else if (*back)
        (*back)->next = NULL;
}

static void mx_unset_node(t_way **list, void *data) {
    t_way *next = NULL;
    t_way *back = NULL;

    mx_unset_node_adt(list, &next, &back);
    mx_free_node(list);
    if (next)
        *((t_way **)data) = next;
    else if (back)
        *((t_way **)data) = back;
    else
        *((t_way **)data) = NULL;
}

void mx_del_client(t_way **list, t_node **node, void *data, int flag) {
    mx_free_struct(node, flag);
    mx_unset_node(list, data);
    free(*list);
    *list = NULL;
}

void *mx_server_handel(void *data) {
    t_way *list = *((t_way **)data);
    t_node *node = (t_node *)list->data;
    char *json = NULL;

    while (node->exit == 1) {
        mx_choose(node, &json);
        mx_exe_request(&node, &json);
        mx_strdel(&json);
    }
    mx_strdel(&json);
    return NULL;
}

