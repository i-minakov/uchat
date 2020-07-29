#include "../../inc/header.h"

/* not mutex */
void mx_send_your_photo(t_node **node) {
    char *img = mx_super_join("./source/cash/", (*node)->user, 0);

    img = mx_super_join(img, ".jpg", 1);
    mx_bites_str((*node)->ssl, "mx_your_photo", 'C');
    mx_strdel(&img);
    img = mx_super_join("./database/", (*node)->user, 0);
    img = mx_super_join(img, "/", 1);
    img = mx_super_join(img, (*node)->user, 1);
    img = mx_super_join(img, ".jpg", 1);
    mx_send_user_file(img, node);
    mx_strdel(&img);
}

static void mx_update(t_node **node, char **arr) {
    if (mx_strcmp(arr[0], "user") == 0) {
        mx_replace(&(*node)->user, arr[1]);
        (*node)->flag = 0;
    }
    else if (mx_strcmp(arr[0], "chat") == 0) {
        mx_replace(&(*node)->chat, arr[1]);
        mx_replace(&(*node)->size, "20");
    }
    else if (mx_strcmp(arr[0], "size") == 0)
        mx_replace(&(*node)->size, arr[1]);
    else if (mx_strcmp(arr[0], "history") == 0)
        mx_replace(&(*node)->history, arr[1]);
}

void mx_not_mutex(t_node **node, char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);

    if (mx_strcmp(command, "mx_update") == 0)
        mx_update(node, arr);
    else
        mx_send_back(node, json);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}

