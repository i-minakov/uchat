#include "../../inc/header.h"

/* set theme or lan */
int mx_set_type(char *name, char *type, int flag) {
    if (!name || !type || (flag != 0 && flag != 1))
        return 1;
    int result = 0;
    char *command = NULL;

    if (flag == 0)
        command = mx_super_join("UPDATE Users SET Lan = '", type, 0);
    else if (flag == 1)
        command = mx_super_join("UPDATE Users SET Theme = '", type, 0);
    command = mx_super_join(command, "' WHERE Name = '", 1);
    command = mx_super_join(command, name, 1);
    command = mx_super_join(command, "';", 1);
    result += mx_exe_command(command);
    mx_strdel(&command);
    return result;
}

