#include "../../inc/header.h"

static void mx_send_size_list(t_node **node, t_list *list) {
    t_list *i = list;
    int j = 0;
    char *str = NULL;

    for (; i; i = i->next)
        j++;
    str = mx_itoa(j);
    mx_bites_str((*node)->ssl, str, 'S');
    mx_strdel(&str);
}

static int mx_send_user_f_s(char *img_path,
                            FILE *file, t_node **node) {
    char *len = NULL;
    char **slesh = mx_strsplit(img_path, '/');

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_file_format(slesh, (*node)->ssl, 'I', 'N');
    mx_file_size_close((*node)->ssl, len, 'I', 'S');
    mx_strdel(&len);
    mx_del_strarr(&slesh);
    return 0;
}

void mx_send_user_file(char *img_path, t_node **node) {
    FILE *file = NULL;

    file = fopen(img_path, "rb");
    if (file) {
        if (mx_send_user_f_s(img_path, file, node) != 1) {
            mx_file_bites(file, (*node)->ssl, 'I', 'B');
            mx_file_size_close((*node)->ssl, "close", 'I', 'C');
        }
        fclose(file);
    }
}

void mx_send_answer_list(t_node **node, t_list *list,
                         int hist_flag, char *json) {
    t_list *i = list;
    t_table_list *data = NULL;
    char *cmd = mx_get_value(json, "command");

    mx_bites_str((*node)->ssl, cmd, 'C');
    mx_send_size_list(node, list);
    for (; i; i = i->next) {
        data = (t_table_list *)i->data;
        mx_bites_str((*node)->ssl, data->name, 'N');
        if ((*node)->flag == 0 && mx_strcmp(cmd, "mx_regular_request") == 0)
            mx_send_user_file(data->path_img, node);
        else if ((*node)->flag >= (FLAG * mx_list_size(list)))
            (*node)->flag = 0;
        if (hist_flag == 1)
            mx_send_history_list(node, data->name, json);
        data = NULL;
    }
    mx_bites_str((*node)->ssl, "end", 'E');
    mx_strdel(&cmd);
}

