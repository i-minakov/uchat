#include "../../inc/header.h"

/* add new message */
void mx_del_after(char *name, char * mssg) {
    char **arr = mx_strsplit(mssg, '.');
    char *path = NULL;
    
    path = mx_super_join("./", name, 0);
    path = mx_super_join(path, ".", 1);
    path = mx_super_join(path, arr[mx_arr_size(arr) - 1], 1);
    remove(path);
    mx_strdel(&path);
    mx_del_strarr(&arr);
}

bool mx_check_blacklist(char *name_from, char *name_to) {
    char *table = mx_super_join(name_to, "_blacklist", 0);

    if (mx_check_user_name(table, name_from)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}

int mx_move_file(char *name_from, char *name_to,
                 char *message, char *file_name) {
    int result = 0;
    char *command = NULL;
    char *old = NULL;
    char **format = mx_strsplit(message, '.');

    command = mx_super_join("./database/", name_from, 0);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, mx_get_time(), 1);
    command = mx_super_join(command, ".", 1);
    command = mx_super_join(command, format[mx_arr_size(format) - 1], 1);
    old = mx_super_join("./", file_name, 0);
    if (mx_arr_size(format) == 2) {
        old = mx_super_join(old, ".", 1);
        old = mx_super_join(old, format[mx_arr_size(format) - 1], 1);
    }
    result = mx_copy(old, command);
    mx_strdel(&old);
    mx_strdel(&command);
    mx_del_strarr(&format);
    return result;
}
