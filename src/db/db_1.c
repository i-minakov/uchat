#include "../../inc/header.h"

/* open database database.db */
int mx_open_db(int flag, sqlite3 **db, char **err_msg) {
    flag = sqlite3_open("./database.db", db);
    if (flag != SQLITE_OK) {
        sqlite3_free(*err_msg);
        sqlite3_close(*db);
        flag = 1;
    }
    return flag;
}

/* execute statement */
int mx_exe(int flag, sqlite3 **db, char **command, char **err_msg) {
    flag = sqlite3_exec(*db, *command, 0, 0, err_msg);
    if (flag != SQLITE_OK) {
        sqlite3_free(*err_msg);
        sqlite3_close(*db);
        flag = 1;
    }
    return flag;
}

/* execute new command */
int mx_exe_command(char *command) {
    t_db data;

    data.command = command;
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        return 1;
    }
    if (mx_exe(data.flag, &data.db, &data.command, &data.err_msg) == -1) {
        sqlite3_close(data.db);
        return 1;
    }
    sqlite3_close(data.db);
    return 0;
}

/* delete name in table */
static int mx_delete_name_adt(t_db *data, char *table, char *name) {
    data->command = NULL;
    data->command = mx_super_join(data->command, "DELETE FROM ", 1);
    data->command = mx_super_join(data->command, table, 1);
    data->command = mx_super_join(data->command, " WHERE Name = ?;", 1);
    data->flag = sqlite3_prepare_v2(data->db,
                                    data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_text(data->res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        mx_strdel(&(data->command));
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

int mx_delete_name(char *table, char *name) {
    t_db data;

    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    if (mx_delete_name_adt(&data, table, name) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    mx_strdel(&(data.command));
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}
