#include "../../inc/header.h"

static int mx_add_user_cmd_adt(t_db *data, char *name, int flag) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join(data->command, "INSERT INTO ", 1);
    data->command = mx_super_join(data->command, name, 1);
    if (flag == 0)
        data->command = mx_super_join(data->command, "_chats", 1);
    else if (flag == 1)
        data->command = mx_super_join(data->command, "_friends", 1);
    else if (flag == 2)
        data->command = mx_super_join(data->command, "_blacklist", 1);
    data->command = mx_super_join(data->command, "(Name, Numb) ", 1);
    data->command = mx_super_join(data->command, "VALUES(?, ?);", 1);
    return 0;
}

static int mx_add_user_pre_adt(t_db *data, char *another_name) {
    data->flag = sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK) {
        sqlite3_bind_text(data->res, 1, another_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(data->res, 2, mx_find_user_id(another_name));
    }
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        mx_strdel(&(data->command));
        return 1;
    }
    return 0;
}

int mx_add_user_to_table(char *name, char *another_name, int flag) {
    if (!name
        || !another_name
        || mx_ckeck_user_in_table(name, another_name, flag))
        return 1;
    t_db data;

    if (mx_add_user_cmd_adt(&data, name, flag) == 1)
        return 1;
    if (mx_add_user_pre_adt(&data, another_name) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    mx_strdel(&(data.command));
    if (data.flag != SQLITE_DONE
        || mx_change_state(name, another_name, flag) != 0
        || mx_add_sub_folder(name, another_name, flag) != 0)
        return 1;
    return 0;
}

