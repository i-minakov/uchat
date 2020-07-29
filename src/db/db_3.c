#include "../../inc/header.h"

/* create user folder */
int mx_folder(char *name) {
    int result = 0;
    char *folder_name = NULL;

    folder_name = mx_super_join("./database/", name, 0);
    result = mkdir(folder_name, 0777);
    free(folder_name);
    folder_name = NULL;
    return result;
}

/* get list of all tables */
static int mx_tables(void *NotUsed, int argc,
                     char **argv, char **azColName) {
    char **s = NULL;

    s = azColName;
    for (int i = 0; i < argc; i++)
        if (argv[i] && mx_strcmp(argv[i], "Users") != 0 
            && mx_strcmp(argv[i], "sqlite_sequence") != 0)
            mx_push_front(((t_list **)NotUsed), (void *)mx_strdup(argv[i]));
    return 0;
}

t_list *mx_get_tables_list(void) {
    t_db data;
    t_list *list = NULL;

    data.command = "SELECT name FROM sqlite_master WHERE type='table'";
    if (mx_open_db(data.flag, &data.db, &data.err_msg) == -1)
        return NULL;
    data.flag =
        sqlite3_exec(data.db, data.command, mx_tables, &list, &data.err_msg);
    if (data.flag != SQLITE_OK) {
        sqlite3_free(data.err_msg);
        sqlite3_close(data.db);
        return NULL;
    } 
    sqlite3_close(data.db);
    return list;
}

/* free list */
void mx_free_list(t_list **list) {
    while (*list) {
        t_list *node = *list;

        *list = (*list)->next;
        if (node->data) {
            free(node->data);
            node->data = NULL;
        }
        node->next = NULL;
        free(node);
        node = NULL;
    }
}

/* find name in chats tables */
bool mx_find_name_in_tables(char *table, char *name) {
    char **two_names = mx_strsplit(table, '_');

    for (int i = 0; two_names[i]; i++)
        if (mx_strcmp(two_names[i], name) == 0) {
            mx_del_strarr(&two_names);
            return true;
        }
    mx_del_strarr(&two_names);
    return false;
}
