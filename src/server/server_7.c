#include "../../inc/header.h"

/* recv request */
static char *mx_create_usual_request(t_node *node) {
    char *json = NULL;
    char *command = NULL;
    char **arr = NULL;

    command = mx_strdup("mx_regular_request");
    arr = mx_arrjoin(arr, node->user);
    arr = mx_arrjoin(arr, node->chat);
    arr = mx_arrjoin(arr, node->size);
    arr = mx_arrjoin(arr, node->history);
    json = mx_request(command, arr);
    mx_strdel(&command);
    mx_del_strarr(&arr);
    return json;
}

static void mx_recv_file(t_node *node, char ch[]) {
    if (ch[1] == 'N') {
        node->for_files->file_name = mx_super_join(node->user, ".", 0);
        mx_static_read(ch, &node->for_files->file_name);
        mx_del_if_exist(node->for_files->file_name);
        node->for_files->file = fopen(node->for_files->file_name, "wb");
    }
    else if (ch[1] == 'S')
        mx_static_read(ch, &node->for_files->file_size);
    else if (node->for_files->file && ch[1] == 'B')
        fwrite(&ch[2], 1, 1, node->for_files->file);
    else if (node->for_files->file && ch[1] == 'C') {
        mx_check_file_size(node->for_files->file,
                           &node->for_files->file_size,
                           &node->for_files->file_name);
    }
}

static void mx_recv_request(t_node *node, char **json) {
    char ch[SIZE_SEND];
    int fd = -1;

    while ((fd = SSL_read(node->ssl, ch, SIZE_SEND)) != -1) {
        if (ch[0] == 'T') {
            mx_static_read(ch, json);
            if (ch[1] == 'E')
                break;
        }
        else if (ch[0] == 'F')
            mx_recv_file(node, ch);
        mx_memset(ch, '\0', SIZE_SEND);
    }
    if (fd == -1) {
        mx_strdel(json);
        mx_del_file(node->for_files->file, &node->for_files->file_size,
                    &node->for_files->file_name);
        *json = mx_strdup("mx_error");
    }
}

void mx_choose(t_node *node, char **json) {
    struct pollfd ufds;

    ufds.fd = node->client;
    ufds.events = POLLIN;
    if (poll(&ufds, 1, TIMER) == 0)
        *json = mx_create_usual_request(node);
    else if (ufds.revents & POLLIN)
        mx_recv_request(node, json);
}

