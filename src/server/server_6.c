#include "../../inc/header.h"

/* mutex or not */
void mx_log_out_fie_del(t_way **list) {
    if (!list || !*list)
        return ;
    t_way *i = *list;
    int j = 0;

    for (; i->next; i = i->next);
    for (; i->back; i = i->back)
        j++;
    for (; j > 0; j--)
        mx_unset_file_node(&i);
    i = NULL;
}

static bool mx_check_command(char *json) {
    if (mx_check_json_cmd(json, "command", "mx_error")
        || mx_check_json_cmd(json, "command", "mx_add_new_user")
        || mx_check_json_cmd(json, "command", "mx_add_user_to_table")
        || mx_check_json_cmd(json, "command", "mx_delete_user")
        || mx_check_json_cmd(json, "command", "mx_recv_new_mess")
        || mx_check_json_cmd(json, "command", "mx_del_history")
        || mx_check_json_cmd(json, "command", "mx_del_message")
        || mx_check_json_cmd(json, "command", "mx_edit")
        || mx_check_json_cmd(json, "command", "mx_log_out")
        || mx_check_json_cmd(json, "command", "mx_change_log")
        || mx_check_json_cmd(json, "command", "mx_change_pass")
        || mx_check_json_cmd(json, "command", "mx_del_user_from_table")
        || mx_check_json_cmd(json, "command", "mx_set_type"))
        return true;
    return false;
}

void mx_exe_request(t_node **node, char **json) {
    if (mx_check_command(*json)) {
        pthread_mutex_lock((*node)->mutex);
        mx_mutex_command(node, *json);
        pthread_mutex_unlock((*node)->mutex);
    }
    else
        mx_not_mutex(node, json);
}

