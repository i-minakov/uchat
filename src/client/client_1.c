#include "../../inc/header.h"

void mx_enter_argv(char ***arr, t_client *client) {
    char **request = client->gtk->command;

    if (request) {
        *arr = mx_copy_arr(request);
        mx_del_strarr(&client->gtk->command);
    }
    mx_check_sigin(client->gtk);
}

/* Cash */
static void mx_create_del_cash(char *name) {
    char *cmd = mx_super_join("./source/cash_", name, 0);

    mkdir(cmd, 0777);
    mx_strdel(&cmd);
    cmd = mx_super_join("./source/cash_", name, 0);
    cmd = mx_super_join(cmd, "/chats", 1);
    mkdir(cmd, 0777);
    mx_strdel(&cmd);
    cmd = mx_super_join("./source/cash_", name, 0);
    cmd = mx_super_join(cmd, "/downloads", 1);
    mkdir(cmd, 0777);
    mx_strdel(&cmd);
}

void mx_for_cash(char *json) {
    char *cmd = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    if (mx_strcmp(cmd, "mx_update") == 0
        && arr
        && mx_strcmp(arr[0], "user") == 0)
        mx_create_del_cash(arr[1]);
    mx_del_strarr(&arr);
    mx_strdel(&cmd);
}
