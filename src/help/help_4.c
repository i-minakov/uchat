#include "../../inc/header.h"

void mx_del_list(t_list **list, int flag) {
    if (!list || !*list)
        return;
    t_list *i = *list;

    for (; i; i = i->next) {
        if (flag == 0)
            mx_free_table_list((t_table_list *)i->data);
        else if (flag == 1)
            mx_free_history((t_history *)i->data);
        else if (flag == 2)
            mx_strdel((char **)&i->data);
    }
    mx_free_list(list);
}

void mx_static_read(char ch[], char **str) {
    if (!str)
        return ;
    for (int i = 2; ch[i]; i++)
        *str = mx_add_char(*str, ch[i]);
}

void mx_del_if_exist(char *name) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("./");
    while ((entry = readdir(dir)) != NULL)
        if (mx_strcmp(entry->d_name, ".") != 0
            && mx_strcmp(entry->d_name, "..") != 0
            && mx_strcmp(entry->d_name, name) == 0)
            remove(name);
    closedir(dir);
}

void mx_del_file(FILE *file, char **size, char **name) {
    if (file && name && size && *size && *name) {
        fclose(file);
        remove(*name);
        mx_strdel(size);
        mx_strdel(name);
    }
}

void mx_check_file_size(FILE *file, char **size, char **name) {
    if (file && name && size && *size && *name) {
        int len = 0;

        fclose(file);
        file = fopen(*name, "rb");
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fseek(file, 0, SEEK_SET);
        if (len != mx_atoi(*size))
            remove(*name);
        fclose(file);
        file = NULL;
        mx_strdel(size);
        mx_strdel(name);
    }
}

