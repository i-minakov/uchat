#include "../../inc/header.h"

/* delete from friends/blacklist */
int mx_del_user_from_table(char *name, char *another_name, int flag) {
    if (!name || !another_name)
        return 1;
    int result = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "DELETE FROM ", 1);
    new_command = mx_super_join(new_command, name, 1);
    if (flag == 0)
        new_command = mx_super_join(new_command, "_chats", 1);
    else if (flag == 1)
        new_command = mx_super_join(new_command, "_friends", 1);
    else if (flag == 2)
        new_command = mx_super_join(new_command, "_blacklist", 1);
    new_command = mx_super_join(new_command, " WHERE Name = '", 1);
    new_command = mx_super_join(new_command, another_name, 1);
    new_command = mx_super_join(new_command, "';", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    return result;        
}
