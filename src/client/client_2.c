#include "../../inc/header.h"

/* read recv */
static bool mx_client_read_adt(char ch[]) {
    if (ch[0] == 'S'
        || ch[0] == 'N'
        || ch[0] == 'I'
        || ch[0] == 'H'
        || ch[0] == 'C'
        || ch[0] == 'E')
        return true;
    return false;
}

static void mx_set_files_adt(t_files *file) {
    file->file = NULL;
    file->file_name = NULL;
    file->file_size = NULL;
}

static void mx_client_adt(char ch[], t_client *client,
                          t_info **info, t_files *file) {
    if (ch[0] == 'T' || ch[0] == 'G' || ch[0] == 'B')
        mx_recv_lan_theme(ch, client);
    else if (mx_client_read_adt(ch))
        mx_recv_list(ch, info, file, client);
    else if (ch[0] == 'F')
        mx_client_recv_file(ch, client);
}

void *mx_client_read(void *client_pointer) {
    t_client *client = (t_client *)client_pointer;
    t_info *info = mx_create_info();
    t_files file;
    char ch[SIZE_SEND];

    mx_set_files_adt(&file);
    while (SSL_read(client->ssl, ch, SIZE_SEND) != -1) {
        if (((t_client *)client_pointer)->exit == 0)
            break;            
        mx_client_adt(ch, client, &info, &file);
        mx_memset(ch, '\0', SIZE_SEND);
    }
    mx_del_file(client->for_files->file, &client->for_files->file_size,
                &client->for_files->file_name);
    client->exit = 0;
    return NULL;
}
