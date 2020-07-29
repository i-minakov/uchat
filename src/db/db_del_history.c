#include "../../inc/header.h"

/* delete history */
static int mx_del_other_hist(char *name_from, char *name_to) {
    int result = 0;
    char *cmd = NULL;

    result += mx_del_user_from_table(name_from, name_to, 0);
    cmd = mx_super_join(name_from, "_", 0);
    cmd = mx_super_join(cmd, name_to, 1);
    result += mx_drop_table(cmd);
    mx_strdel(&cmd);
    cmd = mx_super_join("./database/", name_from, 0);
    cmd = mx_super_join(cmd, "/", 1);
    cmd = mx_super_join(cmd, name_to, 1);
    result += remove(cmd);
    mx_strdel(&cmd);
    return result;
}

int mx_del_history(char *name_from, char *name_to) {
    if (!name_from || !name_to)
        return 1;
    int result = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name_from, 1);
    new_command = mx_super_join(new_command, "_", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    new_command = mx_super_join(new_command, ";", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    new_command = mx_super_join("./database/", name_from, 0);
    new_command = mx_super_join(new_command, "/", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    result += mx_del_files(new_command);
    mx_strdel(&new_command);
    result += mx_del_other_hist(name_from, name_to);
    result += mx_del_user_from_table(name_from, name_to, 0);
    return result;
}

