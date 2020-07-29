#include "../../inc/header.h"

/* del dir and file */
static int mx_del_files_adt(char *name, struct dirent *entry) {
    int result = 0;
    char *path = NULL;

    path = mx_super_join(name, "/", 0);
    path = mx_super_join(path, entry->d_name, 1);
    if (entry->d_type == DT_DIR) {
        result += mx_del_files(path);
        result += remove(path);
    }
    else
        result += remove(path);
    mx_strdel(&path);
    return result;
}

int mx_del_files(char *name) {
    int result = 0;
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    while ((entry = readdir(dir)) != NULL)
        if (mx_strcmp(entry->d_name, ".") != 0
            && mx_strcmp(entry->d_name, "..") != 0)
            result += mx_del_files_adt(name, entry);
    closedir(dir);
    return result;
}

/* free table list */
void mx_free_table_list(t_table_list *list) {
    if (!list)
        return;
    mx_strdel(&list->name);
    mx_strdel(&list->path_img);
    mx_strdel(&list->last_mssg);
    mx_strdel(&list->last_mssg_time);
}
