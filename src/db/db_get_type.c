#include "../../inc/header.h"

/* get theme or lan */
static int mx_get_type_adt(t_db *data, char *name, int flag) {
    if (flag == 0)
        data->command = "SELECT Lan FROM Users WHERE Name = ?";
    else if (flag == 1)
        data->command = "SELECT Theme FROM Users WHERE Name = ?";
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
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

int mx_get_type(char *name, int flag) {
    t_db data;
    int result = -1;

    if (mx_get_type_adt(&data, name, flag) == 1)
        return -1;
    data.flag = sqlite3_step(data.res);
    if (data.flag == SQLITE_ROW) {
        result = sqlite3_column_int(data.res, 0);
        sqlite3_finalize(data.res);
        sqlite3_close(data.db);
        return result;
    }
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    return -1;
}

