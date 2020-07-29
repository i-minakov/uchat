#include "../inc/header.h"

bool mx_check_file_format(char *path) {
    char **slesh = mx_strsplit(path, '/');
    char **dots = mx_strsplit(slesh[mx_arr_size(slesh) - 1], '.');

    if (mx_arr_size(dots) == 1) {
        mx_del_strarr(&dots);
        mx_del_strarr(&slesh);
        return false;
    }
    mx_del_strarr(&dots);
    mx_del_strarr(&slesh);
    return true;
}

void mx_move_to_part_dir(char *name, char *user) {
    if (!name || !user)
        return ;
    char *old = mx_super_join("./", name, 0);
    char *new = mx_super_join("./source/cash_", user, 0);

    new = mx_super_join(new, "/downloads/", 1);
    new = mx_super_join(new, name, 1);
    remove(new);
    rename(old, new);
    mx_strdel(&new);
    mx_strdel(&old);
}
