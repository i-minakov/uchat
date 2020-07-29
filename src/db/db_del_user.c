#include "../../inc/header.h"

/* delete user */
static int mx_delete_in_other(char *name) {
    int result = 0;
    t_list *list = mx_get_tables_list();

    for (t_list *node = list; node; node = node->next) {
        if (mx_get_substr_index((char *)node->data, "_blacklist") > 0
            || mx_get_substr_index((char *)node->data, "_friends") > 0
            || mx_get_substr_index((char *)node->data, "_chats") > 0
            || mx_strcmp((char *)node->data, "Users") == 0)
                result += mx_delete_name((char *)node->data, name);
        else if (mx_find_name_in_tables((char *)node->data, name))
            result += mx_drop_table((char *)node->data);
    }
    mx_free_list(&list);
    return result;
}

static int mx_delete_all_adt(struct dirent *entry,
                             char *name, char *user, int flag) {
    char *path = NULL;
    int result = 0;

    path = mx_super_join(name, "/", 0);
    path = mx_super_join(path, entry->d_name, 1);
    if (entry->d_type != DT_DIR && flag == 1)
        result += remove(path);
    else if (entry->d_type == DT_DIR) {
        if (mx_strcmp(entry->d_name, user) == 0)
            result += mx_delete_all(path, user, 1);
        else
            result += mx_delete_all(path, user, flag);
        if (flag == 1 || mx_strcmp(entry->d_name, user) == 0)
            result += remove(path);
    }
    mx_strdel(&path);
    return result;
}

int mx_delete_all(char *name, char *user, int flag) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL)
        if (mx_strcmp(entry->d_name, ".") != 0
            && mx_strcmp(entry->d_name, "..") != 0)
            result += mx_delete_all_adt(entry, name, user,  flag);
    closedir(dir);
    return result;
}

int mx_delete_user(char *name) {
    if (!name || !mx_check_user_name("Users", name))
        return 1;
    int result = 0;
    char *new_command = NULL;

    for (int i = 0; i < 3; i++) {
        if (i == 0)
            new_command = mx_super_join(name, "_chats", 0);
        else if (i == 1)
            new_command = mx_super_join(name, "_friends", 0);
        else if (i == 2)
            new_command = mx_super_join(name, "_blacklist", 0);
        result += mx_drop_table(new_command);
        mx_strdel(&new_command);
    }
    result += mx_delete_name("Users", name);
    if (mx_delete_all("./database", name, 0) != 0
        || mx_delete_in_other(name) != 0)
        return 1;
    return result;
}
