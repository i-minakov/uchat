#include "../../inc/header.h"

/* drop table */
int mx_drop_table(char *table) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.command = NULL;
    data.command = mx_super_join("DROP TABLE ", table, 0);
    data.command = mx_super_join(data.command, ";", 1);
    if (mx_exe(data.flag, &data.db, &data.command, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        mx_strdel(&(data.command));
        return 1;
    }
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    return 0;
}

/* check name in table */
static int mx_check_user_name_adt(t_db *data, char *table, char *name) {
    data->command = NULL;
    data->command = mx_super_join(data->command, "SELECT * FROM ", 1);
    data->command = mx_super_join(data->command, table, 1);
    data->command = mx_super_join(data->command, " WHERE Name = ?;", 1);
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_text(data->res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        mx_strdel(&(data->command));
        return 1;
    }
    return 0;
}

bool mx_check_user_name(char *table, char *name) {
    if (!table || !name || mx_strcmp(name, "NULL") == 0)
        return false;
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return false;
    if (mx_check_user_name_adt(&data, table, name) == 1)
        return false;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    if (data.flag == SQLITE_ROW)
        return true;
    return false;
}

/* find id user in table Users */
static int mx_find_user_id_adt(t_db *data, char *another_name) {
    data->command = "SELECT * FROM Users WHERE Name = ?";
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_text(data->res, 1, another_name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

int mx_find_user_id(char *another_name) {
    int result = 0;
    t_db data;

    if (mx_find_user_id_adt(&data, another_name) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 0);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return result;
}
