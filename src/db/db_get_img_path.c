#include "../../inc/header.h"

/* down load file */
static int mx_get_img_path_adt(t_db *data, char *name, char *another_name, int id) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join("SELECT * FROM ", name, 0);
    data->command = mx_super_join(data->command, "_", 1);
    data->command = mx_super_join(data->command, another_name, 1);
    data->command = mx_super_join(data->command, " WHERE Id = ?", 1);
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_int(data->res, 1, id);
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        mx_strdel(&data->command);
        return 1;
    }
    mx_strdel(&data->command);
    return 0;
}

char *mx_get_img_path(char *name, char *another_name, int id, char **img_name) {
    t_db data;
    char *path = NULL;

    if (mx_get_img_path_adt(&data, name, another_name, id) == 1)
        return path;
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        path = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        *img_name =
            mx_strdup((char *)sqlite3_column_text(data.res, 6));
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return path;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return path; 
}

