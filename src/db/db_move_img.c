#include "../../inc/header.h"

/* move img */
int mx_change_img(char *name, char *img_name) {
    if (!name || !img_name)
        return 1;
    int result = 0;
    char *command = NULL;
    char *old = NULL;

    command = mx_super_join("./database/", name, 0);
    command = mx_super_join(command, "/", 1);
    command = mx_super_join(command, name, 1);
    command = mx_super_join(command, ".jpg", 1);
    old = mx_super_join("./", img_name, 0);
    remove(command);
    result += rename(old, command);
    mx_strdel(&old);
    mx_strdel(&command);
    return result;
}
