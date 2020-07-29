#include "../../inc/header.h"

/* create table Users */
int mx_create_table_users(void) {
    int result = 0;
    int dir = 0;
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "CREATE TABLE Users", 1);
    new_command =
        mx_super_join(new_command, "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
    new_command = mx_super_join(new_command, "Name TEXT NOT NULL, ", 1);
    new_command = mx_super_join(new_command, "Lan TEXT NOT NULL, ", 1);
    new_command = mx_super_join(new_command, "Theme INT, ", 1);
    new_command = mx_super_join(new_command, "Pass INT, ", 1);
    new_command = mx_super_join(new_command, "Img TEXT NOT NULL);", 1);
    result += mx_exe_command(new_command);
    mx_strdel(&new_command);
    dir = mkdir("./database", 0700);
    if (!dir)
        result = 1;
    return result;
}
