#include "../../inc/header.h"

static char *mx_other_mssg(char *name_from, char *name_to,
                           char *message, int flag) {
    char *path = NULL;
    char **arr = NULL;

    if (flag == 0 || flag == 2)
        path = mx_strdup(message);
    if (flag == 1) {
        path = mx_super_join("./database/", name_from, 0);
        path = mx_super_join(path, "/", 1);
        path = mx_super_join(path, name_to, 1);
        path = mx_super_join(path, "/", 1);
        path = mx_super_join(path, mx_get_time(), 1);
        path = mx_super_join(path, ".", 1);
        arr = mx_strsplit(message, '.');
        path = mx_super_join(path, arr[mx_arr_size(arr) - 1], 1);
        mx_del_strarr(&arr);
    }
    return path;
}

static int mx_insert_mssg_cmd_adt(t_db *data, t_input *node) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join("INSERT INTO ", node->name_from, 0);
    data->command = mx_super_join(data->command, "_", 1);
    data->command = mx_super_join(data->command, node->name_to, 1);
    data->command = mx_super_join(data->command, NEW_MSSG, 1);
    return 0;
}

static void mx_insert_mssg_bind_adt(t_db *data, t_input *node) {
    char *form =
        mx_other_mssg(node->name_from, node->name_to,
                      node->message, node->flag);

    sqlite3_bind_text(data->res, 1, form, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(data->res, 2,
                      mx_get_time(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(data->res, 3, "NULL", -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(data->res, 4, node->reply, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(data->res, 5,
                      node->forward, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(data->res, 6,
                      node->file_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(data->res, 7, node->flag);
    sqlite3_bind_int(data->res, 8, mx_get_id(node->name_to));
    mx_strdel(&form);
}

static int mx_insert_mssg_pre_adt(t_db *data, t_input *node) {
    if (data->flag == SQLITE_OK)
        mx_insert_mssg_bind_adt(data, node);
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        mx_strdel(&(data->command));
        return 1;
    }
    return 0;
}

int mx_insert_mssg(t_input *node) {
    t_db data;

    if (mx_insert_mssg_cmd_adt(&data, node) == 1)
        return 1;
    data.flag =
        sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (mx_insert_mssg_pre_adt(&data, node) == 1)
        return 1;
    mx_strdel(&(data.command));
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}

