#include "../../inc/header.h"

/* reply forward */
static int mx_reply_forward_adt(t_db *data, char *name_from,
                                char *name_to, char *id) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join("SELECT * FROM ", name_from, 0);
    data->command = mx_super_join(data->command, "_", 1);
    data->command = mx_super_join(data->command, name_to, 1);
    data->command = mx_super_join(data->command, " WHERE Id = ", 1);
    data->command = mx_super_join(data->command, id, 1);
    data->command = mx_super_join(data->command, ";", 1);
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag != SQLITE_OK) {
        mx_strdel(&(data->command));
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

void mx_reply_forward(char *name_from, char *name_to,
                      char *id, t_list **list) {
    if (!name_to || !name_from || !id || !*list)
        return ;
    t_db data;

    if (mx_reply_forward_adt(&data, name_from, name_to, id) == 1)
        return ;
    data.flag = sqlite3_step(data.res);
    mx_strdel(&(data.command));
    if (data.flag == SQLITE_ROW) {
        ((t_history *)(*list)->data)->r_f_mssg =
            mx_strdup((char *)sqlite3_column_text(data.res, 1));
        ((t_history *)(*list)->data)->r_f_time =
            mx_strdup((char *)sqlite3_column_text(data.res, 2));
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
}

