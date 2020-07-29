#include "../../inc/header.h"

static void mx_check_user_pass_adt(char **arr, t_node **node) {
    if (mx_check_user_pass(arr[0], arr[1])) {
        mx_send_your_photo(node);
        mx_bites_str((*node)->ssl, "mx_check_user_pass", 'G');
    }
    else {
        mx_bites_str((*node)->ssl, "Wrong pass or user name", 'B');
        mx_strdel(&(*node)->user);
    }
}

static t_list *mx_list_adition(char *command,
                               char **arr, int *hist_flagh) {
    t_list *list = NULL;

    if (mx_strcmp(command, "mx_send_list_back") == 0)
        list = mx_send_list_back(arr[0], mx_atoi(arr[1]));
    else if (mx_strcmp(command, "mx_regular_request") == 0
        || mx_strcmp(command, "mx_mssg_search") == 0) {
        list = mx_send_list_back(arr[0], 0);
        *hist_flagh = 1;
    }
    else if (mx_strcmp(command, "mx_user_search") == 0)
        list = mx_user_search(arr[0], arr[1], arr[2]);
    return list;
}

static int mx_type_adition(char *command, char **arr,
                           t_node **node, char **json) {
    if (mx_strcmp(command, "mx_get_type") == 0)
        return mx_get_type(arr[0], mx_atoi(arr[1]));
    else if (mx_strcmp(command, "mx_get_img_path") == 0) {
        pthread_mutex_lock(&(*node)->files_mutex);
        mx_push_file_way(&(*node)->list, *json);
        *json = NULL;
        pthread_mutex_unlock(&(*node)->files_mutex);
    }
    else if (mx_strcmp(command, "mx_check_user_pass") == 0)
        mx_check_user_pass_adt(arr, node);
    return -1;
}

static void mx_send_back_adt(t_node **node,
                             t_list *list, char **json) {
    if (!list
        && mx_check_json_cmd(*json, "command", "mx_send_list_back"))
        mx_bites_str((*node)->ssl, "mx_send_list_back", 'B');
    else if (!list
             && mx_check_json_cmd(*json, "command", "mx_mssg_search"))
        mx_bites_str((*node)->ssl, "mx_mssg_search", 'B');
}

void mx_send_back(t_node **node, char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);
    int hist_flagh = 0;
    int type = -1;
    t_list *list = NULL;

    list = mx_list_adition(command, arr, &hist_flagh);
    type = mx_type_adition(command, arr, node, json);
    if (list) {
        mx_send_answer_list(node, list, hist_flagh, *json);
        mx_del_list(&list, 0);
        if (hist_flagh == 1)
            hist_flagh = 0;
        (*node)->flag += 1;
    }
    else if (type != -1)
        mx_send_answer_type(node, type, mx_atoi(arr[1]));
    mx_send_back_adt(node, list, json);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}
