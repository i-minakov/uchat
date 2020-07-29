#include "../../inc/header.h"

static int mx_in_other_tables(char *name, char *new_name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_check_user_name((char *)node->data, name)) {
            char *command = NULL;

            command = mx_super_join("UPDATE ", (char *)node->data, 0);
            command = mx_super_join(command, " SET Name = '", 1);
            command = mx_super_join(command, new_name, 1);
            command = mx_super_join(command, "' WHERE Name = '", 1);
            command = mx_super_join(command, name, 1);
            command = mx_super_join(command, "';", 1);
            result += mx_exe_command(command);
            mx_strdel(&command);
        }
    }
    mx_free_list(&list);
    return result;
}

static int mx_change_user_table(char *name, char *new_name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_find_name_in_tables((char *)node->data, name)) {
            char *change = mx_replace_substr((char *)node->data, name, new_name);
            char *new_command = NULL;

            new_command = mx_super_join("ALTER TABLE ", (char *)node->data, 0);
            new_command = mx_super_join(new_command, " RENAME TO ", 1);
            new_command = mx_super_join(new_command, change, 3);
            new_command = mx_super_join(new_command, ";", 1);
            result += mx_exe_command(new_command);
            mx_strdel(&new_command);
        }
    }
    mx_free_list(&list);
    return result;
}

static int mx_change_img_path(char *user, char *new_user) {
    int result = 0;
    char *old = NULL;
    char *new = NULL;

    old = mx_super_join("./database/", user, 0);
    old = mx_super_join(old, "/", 1);
    old = mx_super_join(old, user, 1);
    old = mx_super_join(old, ".jpg", 1);
    new = mx_super_join("./database/", user, 0);
    new = mx_super_join(new, "/", 1);
    new = mx_super_join(new, new_user, 1);
    new = mx_super_join(new, ".jpg", 1);
    result += rename(old, new);
    result += mx_change_path_table(new_user, new);
    mx_strdel(&old);
    mx_strdel(&new);
    return result;
}

static int mx_change_log_adt(t_db *data, char *name, char *new_name) {
    if (mx_change_user_table(name, new_name) != 0)
        return 1;
    data->command = "UPDATE Users SET Name = ? WHERE Name = ?";
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK) {
        sqlite3_bind_text(data->res, 1, new_name,
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

int mx_change_log(char *name, char *new_name) {
    if (!name
        || !new_name
        || isdigit(new_name[0])
        || mx_check_user_name("Users", name))
        return 1;
    t_db data;

    if (mx_change_log_adt(&data, name, new_name) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE
        || mx_change_img_path(name, new_name) != 0
        || mx_change_other_folders("./database", name, new_name) != 0
        || mx_in_other_tables(name, new_name) != 0) {
        return 1;
    }
    return 0;
}

