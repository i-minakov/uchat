#include "../../inc/header.h"

/* send request */
void mx_get_request(char **json, t_client *client) {
    char *command = NULL;
    char **arr = NULL;

    mx_enter_argv(&arr, client);
    if (arr && arr[0])
        command = mx_strdup(arr[0]);
    *json = mx_request(command, &arr[1]);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}

void mx_hash_pass(char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);
    char *hash = mx_strdup(arr[1]);

    mx_strdel(&arr[1]);
    arr[1] = mx_hash(arr[0], hash);
    mx_strdel(json);
    *json = mx_request(command, arr);
    mx_strdel(&hash);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}
