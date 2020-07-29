#include "../../inc/header.h"

/* send history back */
static int mx_history(void *NotUsed, int argc,
                      char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i += 9) {
        t_history *node = (t_history *)malloc(sizeof(t_history));

        node->id = mx_atoi(argv[0]);
        node->message = mx_strdup(argv[1]);
        node->time = mx_strdup(argv[2]);
        node->name = mx_strdup(argv[3]);
        node->mssg_id = mx_strdup(argv[4]);
        node->forward = mx_strdup(argv[5]);
        node->file_name = mx_strdup(argv[6]);
        node->flag = mx_strdup(argv[7]);
        node->r_f_mssg = NULL;
        node->r_f_time = NULL;
        mx_push_front(((t_list **)NotUsed), (void *)node);
    }
    return 0;
}

static int mx_history_back_adt(t_db *data, char *name_from,
                               char *name_to, char *size) {
    if (mx_open_db(data->flag, &data->db, &data->err_msg) == -1)
        return 1;
    data->command = NULL;
    data->command = mx_super_join(data->command, "SELECT * FROM ", 1);
    data->command = mx_super_join(data->command, name_from, 1);
    data->command = mx_super_join(data->command, "_", 1);
    data->command = mx_super_join(data->command, name_to, 1);
    if (size) {
        data->command =
            mx_super_join(data->command, " ORDER BY Id DESC LIMIT ", 1);
        data->command = mx_super_join(data->command, size, 1);
    }
    return 0;
}

t_list *mx_history_back(char *name_from, char *name_to, char *size) {
    if (!name_from || !name_to)
        return NULL;
    t_db data;
    t_list *list = NULL;

    if (mx_history_back_adt(&data, name_from, name_to, size) == 1)
        return NULL;
    data.flag = sqlite3_exec(data.db, data.command,
                             mx_history, &list, &data.err_msg);
    mx_strdel(&(data.command));
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}

