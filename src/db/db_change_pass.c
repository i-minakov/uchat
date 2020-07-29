#include "../../inc/header.h"

/* change pass */
static int mx_change_pass_adt(t_db *data, char *name, char *new_pass) {
    data->command = "UPDATE Users SET Pass = ? WHERE Name = ?";
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK) {
        sqlite3_bind_text(data->res, 1, new_pass,
                          -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data->res, 2, name, -1, SQLITE_TRANSIENT);
    }
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

int mx_change_pass(char *name, char *new_pass) {
    if (!name || !new_pass || !mx_check_user_name("Users", name))
        return 1;
    t_db data;

    if (mx_change_pass_adt(&data, name, new_pass) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}

