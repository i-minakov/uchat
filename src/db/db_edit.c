#include "../../inc/header.h"

/* edit message */
static char *mx_edit_cmd_adt(char *name_from, char *name_to, char *new_mssg, char *id) {
    char *command = NULL;

    command = mx_super_join("UPDATE ", name_from, 0);
    command = mx_super_join(command, "_", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, " SET Message = '", 1);
    command = mx_super_join(command, new_mssg, 1);
    command = mx_super_join(command, "', Time = ", 1);
    command = mx_super_join(command, "'edit ", 1);
    command = mx_super_join(command, mx_get_time(), 1);
    command = mx_super_join(command, "' WHERE Id = ", 1);
    command = mx_super_join(command, id, 1);
    command = mx_super_join(command, ";", 1);
    return command;
}

static int mx_edit_adt(char *name_from, char *name_to, char *new_mssg, char *id) {
    char *command = NULL;
    int result = 0;
    char *str_switch = NULL;

    for (int i = 0; i < 2; i++) {
        command = mx_edit_cmd_adt(name_from, name_to, new_mssg, id);
        result += mx_exe_command(command);
        mx_strdel(&command);
        str_switch = name_from;
        name_from = name_to;
        name_to = str_switch;
    }
    return result;
}

int mx_edit(char *name_from, char *name_to, char *new_mssg, char *id) {
    if (!name_from || !name_to || !new_mssg || !id)
        return 1;
    char *table = NULL;
    int result = 0;

    table = mx_super_join(name_from, "_", 0);
    table = mx_super_join(table, name_to, 1);
    if (mx_check_file(table, id, NULL, 1)
        || mx_check_file(table, id, NULL, 2)) {
        mx_strdel(&table);
        return 1;
    }
    mx_strdel(&table);
    result += mx_edit_adt(name_from, name_to, new_mssg, id);
    return result;
}

