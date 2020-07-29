#include "../../inc/header.h"

/* user search */
static int mx_users(void *NotUsed, int argc, char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        mx_push_front(((t_list **)NotUsed),
                      (void *)mx_strdup(argv[i]));
    return 0;
}

static t_list *mx_get_user_list(void) {
    t_db data;
    t_list *list = NULL;

    data.command = "SELECT Name FROM Users";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.flag = sqlite3_exec(data.db, data.command,
                             mx_users, &list, &data.err_msg);
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}

static void mx_user_search_adt(t_table_list **transfer, t_list *node) {
    (*transfer)->name = mx_strdup((char *)node->data);
    (*transfer)->path_img =
        mx_super_join("./database/", (char *)node->data, 0);
    (*transfer)->path_img =
        mx_super_join((*transfer)->path_img, "/", 1);
    (*transfer)->path_img =
        mx_super_join((*transfer)->path_img, (char *)node->data, 1);
    (*transfer)->path_img =
        mx_super_join((*transfer)->path_img, ".jpg", 1);
    (*transfer)->last_mssg = NULL;
    (*transfer)->last_mssg_time = NULL;
}

t_list *mx_user_search(char *name, char *part_name, char *size) {
    if (!part_name)
        return NULL;
    t_list *list = mx_get_user_list();
    t_list *true_list = NULL;

    for (t_list *node = list; node; node = node->next)
        if (mx_part_cmp((char *)node->data, part_name)
            && mx_strcmp((char *)node->data, name) != 0) {
            t_table_list *transfer =
                (t_table_list *)malloc(sizeof(t_table_list));

            mx_user_search_adt(&transfer, node);
            mx_push_front(&true_list, transfer);
        }
    mx_free_list(&list);
    mx_trim_for_size(&true_list, size);
    return true_list;
}

