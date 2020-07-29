#include "../../inc/header.h"

static t_table_list *mx_create_table_list(char *name) {
    t_table_list *node = (t_table_list *)malloc(sizeof(t_table_list));
    char *path = NULL;

    node->name = mx_strdup(name);
    path = mx_super_join("./database/", name, 0);
    path = mx_super_join(path, "/", 1);
    path = mx_super_join(path, name, 1);
    path = mx_super_join(path, ".jpg", 1);
    node->path_img = mx_strdup(path);
    node->last_mssg = NULL;
    node->last_mssg_time = NULL;
    mx_strdel(&path);
    return node;
}

static int mx_list_back(void *NotUsed, int argc,
                        char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        mx_push_front(((t_list **)NotUsed),
                     (void *)mx_create_table_list(argv[0]));
    return 0;
}

static int mx_send_list_back_adt(t_db *data, t_list **list,
                                 char *name, int flag) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command =
        mx_super_join(data->command, "SELECT Name FROM ", 1);
    data->command = mx_super_join(data->command, name, 1);
    if (flag == 0)
        data->command = mx_super_join(data->command, "_chats;", 1);
    else if (flag == 1)
        data->command = mx_super_join(data->command, "_friends;", 1);
    else if (flag == 2)
        data->command = mx_super_join(data->command, "_blacklist;", 1);
    data->flag = sqlite3_exec(data->db, data->command,
                             mx_list_back, list, &data->err_msg);
    mx_strdel(&(data->command));
    return 0;
}

t_list *mx_send_list_back(char *name, int flag) {
    if (!name || (flag != 0 && flag != 1))
        return NULL;
    t_db data;
    t_list *list = NULL;

    if (mx_send_list_back_adt(&data, &list, name, flag) == 1)
        return NULL;
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    if (flag == 1)
        mx_add_mssg_time(&list, name);
    return list;
}

