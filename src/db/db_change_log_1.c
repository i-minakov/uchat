#include "../../inc/header.h"

/* change log */
static int mx_change_path_table_adt(t_db *data, char *new_user, char *new_path) {
    data->command = "UPDATE Users SET Img = ? WHERE Name = ?";
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->flag =
        sqlite3_prepare_v2(data->db, data->command, -1, &data->res, 0);
    if (data->flag == SQLITE_OK) {
        sqlite3_bind_text(data->res, 1, new_path,
                          -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(data->res, 2, new_user,
                          -1, SQLITE_TRANSIENT);
    }
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;
}

int mx_change_path_table(char *new_user, char *new_path) {
    t_db data;

    if (mx_change_path_table_adt(&data, new_user, new_path) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (data.flag != SQLITE_DONE)
        return 1;
    return 0;
}

static int mx_change_ofol_adt(struct dirent *entry, char *name, char *user, char *new_user) {
    char *path = NULL;
    int result = 0;

    path = mx_super_join(name, "/", 0);
    path = mx_super_join(path, entry->d_name, 1);
    if (entry->d_type == DT_DIR) {
        result += mx_change_other_folders(path, user, new_user);
        if (mx_strcmp(user, entry->d_name) == 0) {
            char *new = NULL;

            new = mx_super_join(name, "/", 0);
            new = mx_super_join(new, new_user, 1);
            result += rename(path, new);
            mx_strdel(&new);
        }
    }
    mx_strdel(&path);
    return result;
}

int mx_change_other_folders(char *name, char *user, char *new_user) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL)
        if (mx_strcmp(entry->d_name, ".") != 0
            && mx_strcmp(entry->d_name, "..") != 0)
            result += mx_change_ofol_adt(entry, name, user, new_user);
    closedir(dir);
    return result;
}

