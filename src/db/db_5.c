#include "../../inc/header.h"

/* check file flag in table */
static int mx_check_file_adt(t_db *data, char *table, char *id) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join("SELECT * FROM ", table, 0);
    data->command = mx_super_join(data->command, " WHERE Id = ?;", 1);
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_int(data->res, 1, mx_atoi(id));
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        mx_strdel(&(data->command));
        return 1;
    }
    mx_strdel(&(data->command));
    return 0;
}

static void mx_set_name_adt(t_db *data, char **name) {
    if (name && *name)
        *name = mx_strdup((char *)sqlite3_column_text(data->res, 1));
}

bool mx_check_file(char *table, char *id, char **name, int flag) {
    t_db data;
    int result = -1;

    if (mx_check_file_adt(&data, table, id) == 1)
        return false;
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 4);
        mx_set_name_adt(&data, name);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        if (result == flag)
            return true;
        else
            return false;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return false;
}

/* free history struct */
void mx_free_history(t_history *list) {
    if (!list)
        return;
    mx_strdel(&list->message);
    mx_strdel(&list->time);
    mx_strdel(&list->name);
    mx_strdel(&list->mssg_id);
    mx_strdel(&list->forward);
    mx_strdel(&list->file_name);
    mx_strdel(&list->flag);
    mx_strdel(&list->r_f_mssg);
    mx_strdel(&list->r_f_time);
}

/* trim list */
void mx_trim_for_size(t_list **list, char *size) {
    if (!size || !list || !*list)
        return ;
    int len = mx_list_size(*list);

    while (len > mx_atoi(size)) {
        mx_pop_front(list);
        len = mx_list_size(*list);
    }
}
