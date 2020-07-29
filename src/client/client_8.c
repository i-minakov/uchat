#include "../../inc/header.h"

static void mx_command_user_adt(t_client *client, char **json) {
    char **arr = mx_get_arr(*json);

    if (mx_check_json_cmd(*json, "command", "mx_update")
        && mx_strcmp(arr[0], "user") == 0)
        client->user = mx_strdup(arr[1]);
    mx_del_strarr(&arr);
}

static void mx_command_adt(t_client *client, char **json, int *result) {
    if (mx_check_json_cmd(*json, "command", "mx_error"))
        *result = 1;
    else if (mx_check_json_cmd(*json, "command", "mx_add_new_user")
            || mx_check_json_cmd(*json, "command", "mx_check_user_pass")
            || mx_check_json_cmd(*json, "command", "mx_change_pass"))
        mx_hash_pass(json);
    else if (mx_check_json_cmd(*json, "command", "mx_log_out"))
        mx_strdel(&client->user);
    mx_command_user_adt(client, json);
}

static int mx_command(t_client *client, char **json) {
    int result = 0;

    pthread_mutex_lock(client->mutex);
    mx_command_adt(client, json, &result);
    if (mx_for_file(*json)) {
        mx_push_file_way(&client->list, (void *)*json);
        *json = NULL;
    }
    else 
        mx_bites_str(client->ssl, *json, 'T');
    pthread_mutex_unlock(client->mutex);
    return result;
}

static void mx_check_status(t_client *client) {
    if (client->gtk->cmd == LOG_OUT) {
        gtk_widget_destroy(client->gtk->fix1);
        gtk_widget_hide(client->gtk->window);
        free_all(client->gtk);
        client->gtk = malloc_main();
        client->gtk->log_in->start_flag = 1;
        log_screen(client->gtk);
        client->gtk->cmd = BLCK;
    }
    if (client->gtk->cmd == SIG_IN || client->gtk->cmd == SIG_UP)
        mx_chat_screen(&client->gtk);
}

void mx_client_send(t_client *client) {
    char *json = NULL;

    log_screen(client->gtk);
    while (client->exit == 1) {
        gtk_main_iteration();
        mx_get_request(&json, client); 
        mx_check_status(client);
        mx_for_cash(json);
        if (mx_command(client, &json) == 1)
            break;
        mx_strdel(&json);
    }
    client->exit = 0;
    mx_strdel(&json);
}

