#include "../../inc/header.h"

/* new user */
int mx_rm_if_error(char *name) {
    char *img_path = NULL;

    img_path = mx_super_join("./", name, 0);
    img_path = mx_super_join(img_path, ".jpg", 1);
    remove(img_path);
    mx_strdel(&img_path);
    return 1;
}

static char *mx_user_tables_adt(char *name, int i) {
    char *new_command = NULL;

    new_command = mx_super_join(new_command, "CREATE TABLE ", 1);
    new_command = mx_super_join(new_command, name, 1);
    if (i == 0)
        new_command = mx_super_join(new_command, "_chats", 1);
    else if (i == 1)
        new_command = mx_super_join(new_command, "_friends", 1);
    else if (i == 2)
        new_command = mx_super_join(new_command, "_blacklist", 1);
    new_command =
        mx_super_join(new_command,
                      "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
    new_command =
        mx_super_join(new_command, "Name TEXT NOT NULL, ", 1);
    new_command = mx_super_join(new_command, "Numb INT NOT NULL, ", 1);
    new_command =
        mx_super_join(new_command,
                      "FOREIGN KEY (Numb) REFERENCES Users(Id));", 1);
    return new_command;
}

int mx_user_tables(char *name) {
    int result = 0;
    char *new_command = NULL;

    for (int i = 0; i < 3; i++) {
        new_command = mx_user_tables_adt(name, i);
        result += mx_exe_command(new_command);
        mx_strdel(&new_command);
    }
    return result;
}

