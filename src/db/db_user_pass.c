#include "../../inc/header.h"

/* check user pass */
static int mx_check_user_pass_adt(t_db *data, char *name) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = "SELECT * FROM Users WHERE Name = ?";
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK)
        sqlite3_bind_text(data->res, 1, name, -1, SQLITE_TRANSIENT);
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

bool mx_check_user_pass(char *name, char *pass) {
    if (!name || !pass || !mx_check_user_name("Users", name))
        return false;
    t_db data;

    if (mx_check_user_pass_adt(&data, name) == 1)
        return false;
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW)
        if (mx_strcmp(pass,
                      (char *)sqlite3_column_text(data.res, 4)) == 0) {
            sqlite3_finalize(data.res);
            sqlite3_close(data.db);
            return true;
        }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return false;
}

