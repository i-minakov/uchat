#include "../../inc/header.h"

/* handel for files */
static int mx_send_size_name(t_node *node, FILE *file, char *img_name) {
    char *len = NULL;

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_bites_str(node->ssl, img_name, 'F');
    mx_file_size_close(node->ssl, len, 'F', 'L');
    mx_strdel(&len);
    return 0;
}

static void mx_server_files_send(char *json, t_node *node) {
    char **arr = mx_get_arr(json);
    char *img_name = NULL;
    char *img_path = mx_get_img_path(arr[0], arr[1],
                                     mx_atoi(arr[2]), &img_name);
    FILE *file = fopen(img_path, "rb");

    if (file) {
        if (mx_send_size_name(node, file, img_name) != 1) {
            mx_file_bites(file, node->ssl, 'F', 'B');
            mx_file_size_close(node->ssl, "close", 'F', 'C');
        }
        fclose(file);
    }
    mx_strdel(&img_name);
    mx_strdel(&img_path);
    mx_del_strarr(&arr);
}

void *mx_server_files(void *data) {
    t_way *list = *((t_way **)data);
    t_node *node = (t_node *)list->data;

    while (node->exit == 1) {
        if (node->list) {
            pthread_mutex_lock(&node->files_mutex);
            mx_server_files_send((char *)node->list->data, node);
            mx_strdel((char **)&node->list->data);
            mx_unset_file_node(&node->list);
            pthread_mutex_unlock(&node->files_mutex);
        }
    }
    mx_del_client(&list, &node, data, 0);
    return NULL;
}

