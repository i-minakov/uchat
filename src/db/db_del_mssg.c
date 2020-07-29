#include "../../inc/header.h"

/* delete message */
static int mx_del_message_adt(char *name_from,
                              char *name_to, char *id) {
    int result = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name_from, 1);
    new_command = mx_super_join(new_command, "_", 1);
    new_command = mx_super_join(new_command, name_to, 1);
    new_command = mx_super_join(new_command, " WHERE Id = ", 1);
    new_command = mx_super_join(new_command, id, 1);
    new_command = mx_super_join(new_command, ";", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    return result;
}

int mx_del_message(char *name_from, char *name_to, char *id) {
    if (!name_to || !name_from || !id)
        return 1;
    int result = 0;
    char *name = NULL;
    char *new_command = NULL;

    new_command = mx_super_join(name_from, "_", 0);
    new_command = mx_super_join(new_command, name_to, 1);
    if (mx_check_file(new_command, id, &name, 1)) {
        result += remove(name);
        mx_strdel(&name);
    }
    mx_strdel(&new_command);
    result += mx_del_message_adt(name_from, name_to, id);
    return result;
}

