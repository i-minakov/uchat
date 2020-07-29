#include "../../inc/header.h"

/* send table list */
static int mx_find_last_mssg_adt(t_db *data, char *table) {
    data->command = NULL;
    data->command = mx_super_join("SELECT * FROM ", table, 0);
    data->command =
        mx_super_join(data->command, " ORDER BY Id DESC LIMIT 1;", 1);
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

static void mx_find_last_mssg(char *table, char **message, char **time) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return ;
    if (mx_find_last_mssg_adt(&data, table) == 1)
        return ;
    mx_strdel(&(data.command));
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        *message = mx_strdup((char *)sqlite3_column_text(data.res, 1));
        *time = mx_strdup((char *)sqlite3_column_text(data.res, 2));
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
}

void mx_add_mssg_time(t_list **list, char *name) {
    for (t_list *node = *list; node; node = node->next) {
        char *table_name = NULL;
        char *new_name = ((t_table_list *)node->data)->name;
        char *last_mssg = ((t_table_list *)node->data)->last_mssg;
        char *last_time = ((t_table_list *)node->data)->last_mssg_time;

        table_name = mx_super_join(name, "_", 0);
        table_name = mx_super_join(table_name, new_name, 1);
        mx_find_last_mssg(table_name, &last_mssg, &last_time);
        mx_strdel(&table_name);
    }
}

