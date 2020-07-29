#include "../../inc/header.h"

/* get current time */
char *mx_get_time(void) {
    time_t rawtime;
    struct tm *timeinfo;
    char *time_str = NULL;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    time_str = asctime(timeinfo);
    if (time_str[mx_strlen(time_str) - 1] == '\n')
        time_str[mx_strlen(time_str) - 1] = '\0';
    return time_str;
}

/* get user id in Users */
static int mx_get_id_adt(t_db *data, char *name) {
    data->command = "SELECT * FROM Users WHERE Name = ?";
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

int mx_get_id(char *name) {
    t_db data;
    int result = -1;

    if (mx_get_id_adt(&data, name) == 1)
        return result;
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

/* from one to another */
int mx_copy(char *old, char *new) {
    FILE *from = fopen(old, "rb");
    FILE *to = fopen(new, "wb");

    if (!to || !from) {
        if (from)
            fclose(from);
        if (to)
            fclose(to);
        return 1;
    }
    char send_buffer[1];
    int nb = fread(send_buffer, 1, 1, from);

    while (nb != 0) {
        fwrite(send_buffer, 1, 1, to);
        nb = fread(send_buffer, 1, 1, from);
    }
    fclose(from);
    fclose(to);
    return 0;
}

/* strnsmp */
bool mx_part_cmp(char *data, char *part_name) {
    for (int i = 0; i < mx_strlen(part_name); i++) {
        if (part_name[i] == '\0')
            break;
        else if (data[i] != part_name[i])
            return false;
    }
    return true;
}
