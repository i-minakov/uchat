#include "../../inc/header.h"

static void mx_mutex_first_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_error") == 0)
        (*node)->exit = 0;
    else if (mx_strcmp(command, "mx_add_new_user") == 0) {
        if (mx_add_new_user(arr[0], arr[1], arr[2]) == 0) {
            mx_send_your_photo(node);
            mx_bites_str((*node)->ssl, "mx_add_new_user", 'G');
        }
        else {
            mx_bites_str((*node)->ssl, "User already exist", 'B');
            mx_strdel(&(*node)->user);
        }
    }
    else if (mx_strcmp(command, "mx_add_user_to_table") == 0)
        mx_add_user_to_table(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_add_user_to_table", 'G')
            : mx_bites_str((*node)->ssl, "Can't add user", 'B');
    else if (mx_strcmp(command, "mx_delete_user") == 0)
        mx_delete_user(arr[0]) == 0
            ? mx_bites_str((*node)->ssl, "mx_delete_user", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete user", 'B');
}

static void mx_mutex_second_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_recv_new_mess") == 0) {
        t_input data;

        data.name_from = arr[0];
        data.name_to = arr[1];
        data.message = arr[2];
        data.flag = mx_atoi(arr[3]);
        data.reply = arr[4];
        data.forward = arr[5];
        if (mx_atoi(arr[3]) == 1)
            data.file_name = mx_strdup(arr[2]);
        else
            data.file_name = mx_strdup("NULL");
        mx_recv_new_mess(&data) == 0
            ? mx_bites_str((*node)->ssl, "mx_recv_new_mess", 'G')
            : mx_bites_str((*node)->ssl, "Can't send message", 'B');
    }
}

static void mx_mutex_third_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_del_history") == 0)
        mx_del_history(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_history", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete history", 'B');
    else if (mx_strcmp(command, "mx_del_message") == 0)
        mx_del_message(arr[0], arr[1], arr[2]) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_message", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete message", 'B');
    else if (mx_strcmp(command, "mx_edit") == 0)
        mx_edit(arr[0], arr[1], arr[2], arr[3]) == 0
            ? mx_bites_str((*node)->ssl, "mx_edit", 'G')
            : mx_bites_str((*node)->ssl, "Can't edit message", 'B');
    else if (mx_strcmp(command, "mx_change_log") == 0)
        mx_change_log(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_change_log", 'G')
            : mx_bites_str((*node)->ssl, "Can't change user name", 'B');
    else if (mx_strcmp(command, "mx_change_pass") == 0)
        mx_change_pass(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_change_pass", 'G')
            : mx_bites_str((*node)->ssl, "Can't change password", 'B');
}

static void mx_mutex_fourth_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_set_type") == 0)
        mx_set_type(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_set_type", 'G')
            : mx_bites_str((*node)->ssl, "Can't change type", 'B');
    else if (mx_strcmp(command, "mx_change_img") == 0) {
        if (mx_change_img(arr[0], arr[1]) == 0) {
            mx_send_your_photo(node);
            mx_bites_str((*node)->ssl, "mx_change_img", 'G');
        }
        else
            mx_bites_str((*node)->ssl, "Can't change image", 'B');
    }
    else if (mx_strcmp(command, "mx_del_user_from_table") == 0)
        mx_del_user_from_table(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_user_from_table", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete user from table", 'B');
}

void mx_mutex_command(t_node **node, char *json) {
    char *command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    mx_mutex_first_adt(node, command, arr);
    mx_mutex_second_adt(node, command, arr);
    mx_mutex_third_adt(node, command, arr);
    mx_mutex_fourth_adt(node, command, arr);
    if (mx_strcmp(command, "mx_log_out") == 0
        || mx_strcmp(command, "mx_delete_user") == 0) {
        pthread_mutex_lock(&(*node)->files_mutex);
        mx_log_out_fie_del(&(*node)->list);
        pthread_mutex_unlock(&(*node)->files_mutex);
        mx_replace(&(*node)->user, "NULL");
        mx_replace(&(*node)->chat, "NULL");
        mx_replace(&(*node)->size, "20");
        mx_replace(&(*node)->history, "normal");
    }
    mx_strdel(&command);
    mx_del_strarr(&arr);
}

