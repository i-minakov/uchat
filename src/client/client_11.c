#include "../../inc/header.h"

/* send file */
static void mx_change_file_pass(char ***arr, char *command) {
    char **argv = *arr;
    char **pars = mx_strsplit(argv[2], '/');

    mx_strdel(&argv[2]);
    if (mx_strcmp(command, "mx_add_new_user") == 0)
        argv[2] = mx_super_join(argv[0], ".jpg", 0);
    else
        argv[2] = mx_super_join(argv[2], pars[mx_arr_size(pars) - 1], 1);
    mx_del_strarr(&pars);
}

void mx_send_command(char *json, t_client *client) {
    char *new_json = NULL;
    char *command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    mx_change_file_pass(&arr, command);
    new_json = mx_request(command, arr);
    mx_bites_str(client->ssl, new_json, 'T');
    mx_strdel(&command);
    mx_del_strarr(&arr);
    mx_strdel(&new_json);
}

static int mx_send_f_s(char *format, FILE *file, t_client *client) {
    char *len = NULL;
    char **split_dot = mx_strsplit(format, '.');

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_file_format(split_dot, client->ssl, 'F', 'N');
    mx_file_size_close(client->ssl, len, 'F', 'S');
    mx_strdel(&len);
    mx_del_strarr(&split_dot);
    return 0;
}

static void mx_command_for_send(char *json, t_client *client) {
    FILE *file = NULL;
    char **arr = mx_get_arr(json);
    char *command = mx_get_value(json, "command");

    file = fopen(arr[2], "rb");
    if (file) {
        if (mx_send_f_s(arr[2], file, client) != 1) {
            mx_file_bites(file, client->ssl, 'F', 'B');
            mx_file_size_close(client->ssl, "close", 'F', 'C');
        }
        fclose(file);
    }
    mx_send_command(json, client);
    mx_del_strarr(&arr);
    mx_strdel(&command);
}

void *mx_files(void *client_pointer) {
    t_client *client = (t_client *)client_pointer;

    while (client->exit == 1) {
        if (client->list != NULL) {
            pthread_mutex_lock(client->mutex);
            mx_command_for_send((char *)client->list->data, client);
            mx_strdel((char **)&client->list->data);
            mx_unset_file_node(&client->list);
            pthread_mutex_unlock(client->mutex);
        }
    }
    return NULL;
}

