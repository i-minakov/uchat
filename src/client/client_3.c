#include "../../inc/header.h"

static void mx_recv_file_adt(FILE *file, char **size,
                             char **name, t_client *client) {
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
        mx_move_to_part_dir(*name, client->gtk->my_name);
        mx_strdel(size);
        mx_strdel(name);
    }
}

void mx_client_recv_file(char ch[], t_client *client) {
    if (ch[1] == 'E') {
        char *name = NULL;

        mx_static_read(ch, &name);
        client->for_files->file_name = mx_super_join("./", name, 2);
        mx_del_if_exist(client->for_files->file_name);
        client->for_files->file = fopen(client->for_files->file_name, "wb");
    }
    else if (ch[1] == 'L')
        mx_static_read(ch, &client->for_files->file_size);
    else if (client->for_files->file && ch[1] == 'B') {
        if ((int)fwrite(&ch[2], 1, 1, client->for_files->file) == -1)
            return ;
    }
    else if (client->for_files->file && ch[1] == 'C')
        mx_recv_file_adt(client->for_files->file,
                           &client->for_files->file_size,
                           &client->for_files->file_name,
                           client);
}
