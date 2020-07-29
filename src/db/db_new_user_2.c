#include "../../inc/header.h"

static int mx_add_new_user_adt(t_db *data, char *name, char *pass) {
    char *img = NULL;

    if (data->flag == SQLITE_OK) {
        sqlite3_bind_text(data->res, 1, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(data->res, 2, 0);
        sqlite3_bind_int(data->res, 3, 0);
        sqlite3_bind_text(data->res, 4, pass, -1, SQLITE_TRANSIENT);
        img = mx_super_join("./database/", name, 0);
        img = mx_super_join(img, "/", 1);
        img = mx_super_join(img, name, 1);
        img = mx_super_join(img, ".jpg", 1);
        sqlite3_bind_text(data->res, 5, img, -1, SQLITE_TRANSIENT);
        mx_strdel(&img);
    }
    else {
        sqlite3_finalize(data->res);
        sqlite3_close(data->db);
        return 1;
    }
    return 0;    
}

static int mx_add_new_user_last_adt(t_db *data,
                                    char *name, char *img_name) {
    if (data->flag != SQLITE_DONE
        || mx_user_tables(name) != 0
        || mx_folder(name) != 0
        || mx_change_img(name, img_name) != 0)
        return 1;
    return 0;
}

int mx_add_new_user(char *name, char *pass, char *img_name) {
    if (!name || !pass || mx_check_user_name("Users", name))
        return mx_rm_if_error(name);
    t_db data;

    data.command = NEW_USER;
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return 1;
    data.flag =
        sqlite3_prepare_v2(data.db, data.command, -1, &data.res, 0);
    if (mx_add_new_user_adt(&data, name, pass) == 1)
        return 1;
    data.flag = sqlite3_step(data.res);
    sqlite3_finalize(data.res);
    sqlite3_close(data.db);
    if (mx_add_new_user_last_adt(&data, name, img_name) == 1)
        return mx_rm_if_error(name);
    return 0;
}

