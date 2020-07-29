#include "../../inc/header.h"

static void mx_trim_full_list(t_info **info) {
    if (!info || !*info)
        return;
    mx_strdel(&(*info)->cmd);
    mx_strdel(&(*info)->size);
    for (t_list *i = (*info)->list; i; i = i->next) {
        mx_strdel(&((t_data *)i->data)->name);
        mx_strdel(&((t_data *)i->data)->path);
        mx_del_list(&((t_data *)i->data)->list, 2);
    }
    mx_free_list(&(*info)->list);
    free(*info);
    *info = NULL;
}

static void mx_sort_recv_list(t_info **info) {
    if (mx_strcmp("mx_regular_request", (*info)->cmd) != 0)
        mx_sort_mssg(&(*info)->list, 1);
    else
        mx_sort_mssg(&(*info)->list, 0);
}

static void mx_recv_list_adt(char ch[], t_info **info,
                             t_files *files, t_client *client) {
    if (ch[0] == 'I')
        mx_recv_list_files(ch, info, files, client);
    else if (ch[0] == 'S')
        mx_static_read(ch, &(*info)->size);
    else if (ch[0] == 'H') {
        if (ch[1] == 'E') {
            char *str = NULL;

            mx_push_front(&((t_data *)(*info)->list->data)->list,
                          (void *)str);
        }
        mx_static_read(ch,
                       (char **)&((t_data *)(*info)->list->data)->list->data);
    }
    else if (ch[0] == 'E' && ch[1] == 'E') {
        mx_sort_recv_list(info);
        mx_check_rcv_list(*info, client->gtk);
        mx_trim_full_list(info);
        *info = mx_create_info();
    }
}

void mx_recv_list(char ch[], t_info **info,
                  t_files *files, t_client *client) {
    if (ch[0] == 'C') {
        mx_strdel(&(*info)->cmd);
        mx_static_read(ch, &(*info)->cmd);
    }
    else if (ch[0] == 'N') {
        if (ch[1] == 'E')
            mx_push_front(&(*info)->list, (void *)mx_create_data());
        mx_static_read(ch, &((t_data *)(*info)->list->data)->name);
        ((t_data *)(*info)->list->data)->path =
            mx_super_join("./source/cash_", client->gtk->my_name, 0);
        ((t_data *)(*info)->list->data)->path =
            mx_super_join(((t_data *)(*info)->list->data)->path,
                          "/chats/", 1);
        ((t_data *)(*info)->list->data)->path =
            mx_super_join(((t_data *)(*info)->list->data)->path,
                          ((t_data *)(*info)->list->data)->name, 1);
        ((t_data *)(*info)->list->data)->path =
            mx_super_join(((t_data *)(*info)->list->data)->path, ".jpg", 1);
    }
    mx_recv_list_adt(ch, info, files, client);
}

