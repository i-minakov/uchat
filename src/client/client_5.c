#include "../../inc/header.h"

/* recv callbacks */
t_data *mx_create_data(void) {
    t_data *node = (t_data *)malloc(sizeof(t_data));
    char *str = NULL;

    node->path = NULL;
    node->name = NULL;
    node->list = NULL;
    mx_push_front(&node->list, str);
    return node;
}

t_info *mx_create_info(void) {
    t_info *node = (t_info *)malloc(sizeof(t_info));

    node->cmd = NULL;
    node->size = NULL;
    node->list = NULL;
    return node;
}

char *mx_right_path(t_info **info, t_files *files, t_client *client, char *name) {
    char *path = NULL;
    char **arr = mx_strsplit(name, '.');

    if (mx_strcmp((*info)->cmd, "mx_regular_request") == 0) {
        path = mx_super_join("./source/cash_", client->user, 0);
        path = mx_super_join(path, "/chats/", 1);
        path = mx_super_join(path, files->file_name, 1);
    }
    else if (mx_strcmp((*info)->cmd, "mx_your_photo") == 0) {
        path = mx_super_join("./source/cash_", arr[0], 0);
        path = mx_super_join(path, "/", 1);
        path = mx_super_join(path, files->file_name, 1);
    }
    mx_del_strarr(&arr);
    return path;
}

void mx_recv_list_files(char ch[], t_info **info, t_files *files, t_client *client) {
    if (ch[1] == 'S')
        mx_static_read(ch, &files->file_size);
    else if (ch[1] == 'N') {
        char *s = NULL;

        mx_static_read(ch, &files->file_name);
        s = files->file_name;
        files->file_name = mx_right_path(info, files, client, s);
        mx_strdel(&s);
        mx_del_if_exist(files->file_name);
        files->file = fopen(files->file_name, "wb");
    }
    else if (ch[1] == 'B') {
        if ((int)fwrite(&ch[2], 1, 1, files->file) == -1)
            return ;
    }
    else if (ch[1] == 'C')
        mx_check_file_size(files->file, &files->file_size,
                           &files->file_name);
}

