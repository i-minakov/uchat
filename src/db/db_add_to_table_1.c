#include "../../inc/header.h"

/* add user to table */
static int mx_two_chats(char *name, char *another_name) {
    char *c = NULL;
    int result = 0;

    c = mx_super_join(c, "CREATE TABLE ", 1);
    c = mx_super_join(c, name, 1);
    c = mx_super_join(c, "_", 1);
    c = mx_super_join(c, another_name, 1);
    c = mx_super_join(c, "(Id INTEGER PRIMARY KEY AUTOINCREMENT, ", 1);
    c = mx_super_join(c, "Message TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "Time TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "Name TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "Reply TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "Forward TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "File TEXT NOT NULL, ", 1);
    c = mx_super_join(c, "Flag INT NOT NULL, ", 1);
    c = mx_super_join(c, "Fk INT NOT NULL, ", 1);
    c = mx_super_join(c, "FOREIGN KEY (Fk) REFERENCES Users(Id));", 1);
    result = mx_exe_command(c);
    mx_strdel(&c);
    return result;
}

int mx_add_sub_folder(char *name, char *another_name, int flag) {
    if (flag != 0)
        return 0;
    int result = 0;
    char *folder_name = NULL;

    folder_name = mx_super_join("./database/", name, 0);
    folder_name = mx_super_join(folder_name, "/", 1);
    folder_name = mx_super_join(folder_name, another_name, 1);
    if (flag == 0)
        result = mkdir(folder_name, 0777);
    else if (flag == 1)
        result = remove(folder_name);
    mx_strdel(&folder_name);
    result += mx_two_chats(name, another_name);
    return result;
}

bool mx_ckeck_user_in_table(char *name, char *another_name, int flag) {
    if (flag < 0 || flag > 2 || mx_strcmp(name, another_name) == 0)
        return true;
    char *table = NULL;

    if (flag == 0)
        table = mx_super_join(name, "_chats", 0);
    else if (flag == 1)
        table = mx_super_join(name, "_friends", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_blacklist", 0);
    if (mx_check_user_name(table, another_name)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}

static bool mx_check_state(char *name, char *another_name, int flag) {
    char *table = NULL;

    if (flag == 1)
        table = mx_super_join(name, "_blacklist", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_friends", 0);
    if (mx_check_user_name(table, another_name)) {
        mx_strdel(&table);
        return true;
    }
    mx_strdel(&table);
    return false;
}

int mx_change_state(char *name, char *another_name, int flag) {
    char *table = NULL;
    
    if (flag == 1)
        table = mx_super_join(name, "_blacklist", 0);
    else if (flag == 2)
        table = mx_super_join(name, "_friends", 0);
    if (mx_check_state(name, another_name, flag)
        && mx_delete_name(table, another_name) == -1) {
        mx_strdel(&table);
        return 1;
    }
    mx_strdel(&table);
    return 0;
}

