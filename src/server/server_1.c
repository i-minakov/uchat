#include "../../inc/header.h"

/* callbacks */
static void mx_rep_for_mssg(char ***arr, t_list *node, int flag) {
    *arr = mx_arrjoin(*arr, (((t_history *)node->data)->r_f_mssg
                        ? ((t_history *)node->data)->r_f_mssg : "NULL"));
    *arr = mx_arrjoin(*arr, (((t_history *)node->data)->r_f_time
                        ? ((t_history *)node->data)->r_f_time : "NULL"));
    if (flag == 1)
        *arr = mx_arrjoin(*arr, (((t_history *)node->data)->forward
                            ? ((t_history *)node->data)->forward : "NULL"));
}

static void mx_send_history_line_adt(t_list *node, char *from, char *to, char ***arr) {
    if (mx_strcmp(((t_history *)node->data)->mssg_id, "NULL") != 0
        && mx_strcmp(((t_history *)node->data)->forward, "NULL") == 0) {
        mx_reply_forward(from, to, ((t_history *)node->data)->mssg_id, &node);
        mx_rep_for_mssg(arr, node, 0);
    }
    else if (mx_strcmp(((t_history *)node->data)->forward, "NULL") != 0) {
        mx_reply_forward(from, ((t_history *)node->data)->forward,
                            ((t_history *)node->data)->mssg_id, &node);
        mx_rep_for_mssg(arr, node, 1);
    }
}

static void mx_send_history_line(t_list **list, char *from, char *to, SSL *ssl) {
    char *command = NULL;
    char **arr = NULL;
    char *json;

    for (t_list *node = *list; node; node = node->next) {
        command = mx_itoa(((t_history *)node->data)->id);
        if (mx_strcmp(((t_history *)node->data)->flag, "1") == 0)
            arr = mx_arrjoin(arr, ((t_history *)node->data)->file_name);
        else
            arr = mx_arrjoin(arr, ((t_history *)node->data)->message);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->time);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->name);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->flag);
        mx_send_history_line_adt(node, from, to, &arr);
        json = mx_request(command, arr);
        mx_bites_str(ssl, json, 'H');
        mx_strdel(&json);
        mx_strdel(&command);
        mx_del_strarr(&arr);
    }
}

void mx_send_history_list(t_node **node, char *name, char *json) {
    t_list *list = NULL;
    char *size = NULL;
    char **arr = NULL;

    if (mx_strcmp(name, (*node)->chat) == 0)
        size = mx_strdup((*node)->size);
    else
        size = mx_strdup("1");
    if (mx_strcmp((*node)->history, "normal") != 0
        && mx_strcmp(name, (*node)->chat) == 0) {
        arr = mx_get_arr(json);
        list = mx_mssg_search((*node)->user, (*node)->chat, arr[2], size);
        mx_replace(&(*node)->history, "normal");
        mx_del_strarr(&arr);
    }
    else
        list = mx_history_back((*node)->user, name, size);
    mx_send_history_line(&list, (*node)->user, (*node)->chat, (*node)->ssl);
    mx_strdel(&size);
    mx_del_list(&list, 1);
}

void mx_send_answer_type(t_node **node, int type, int flag) {
    char *type_str = NULL;
    char send[SIZE_SEND];

    mx_memset(send, '\0', SIZE_SEND);
    send[0] = 'T';
    type_str = mx_itoa(type);
    if (flag == 0)
        send[1] = 'L';
    if (flag == 1)
        send[1] = 'T';
    mx_mom(send, type_str, mx_strlen(type_str), 0);
    if (SSL_write((*node)->ssl, send, SIZE_SEND) == -1)
        return ;
    mx_strdel(&type_str);
}

