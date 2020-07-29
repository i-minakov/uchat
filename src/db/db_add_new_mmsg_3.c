#include "../../inc/header.h"

static bool mx_first_message(char *name_from, char *name_to) {
    int flag = 1;
    t_list *list = mx_get_tables_list();
    char *table = NULL;

    table = mx_super_join(name_from, "_", 0);
    table = mx_super_join(table, name_to, 1);
    for (t_list *node = list; node; node = node->next)
        if (mx_strcmp((char *)node->data, table) == 0)
            flag = 0;
    mx_strdel(&table);
    mx_free_list(&list);
    return flag;
}

static int mx_whos_mssg(char *name_from, char *name_to, char *who) {
    int result = 0;
    char *command = NULL;

    command = mx_super_join("UPDATE ", name_from, 0);
    command = mx_super_join(command, "_", 1);
    command = mx_super_join(command, name_to, 1);
    command = mx_super_join(command, " SET Name = '", 1);
    command = mx_super_join(command, who, 1);
    command = mx_super_join(command, "' WHERE Name = 'NULL';", 1);
    result += mx_exe_command(command);
    mx_strdel(&command);
    return result;
}

static int mx_recv_new_mess_adt(t_input *data) {
    int result = 0;
    char *shift = NULL;

    if (mx_first_message(data->name_from, data->name_to))
        result +=
            mx_add_user_to_table(data->name_from, data->name_to, 0);
    if (mx_first_message(data->name_to, data->name_from))
        result +=
            mx_add_user_to_table(data->name_to, data->name_from, 0);
    result += mx_insert_mssg(data);
    result +=
        mx_whos_mssg(data->name_from, data->name_to, data->name_from);
    shift = data->name_from;
    data->name_from = data->name_to;
    data->name_to = shift;
    result += mx_insert_mssg(data);
    result +=
        mx_whos_mssg(data->name_from, data->name_to, data->name_to);
    return result;
}

int mx_recv_new_mess(t_input *data) {
    if (!data->name_from
        || !data->name_to
        || (data->flag < 0 && data->flag > 2)
        || !data->message
        || mx_check_blacklist(data->name_from, data->name_to))
        return 1;
    int result = 0;

    result += mx_recv_new_mess_adt(data);
    if (data->flag == 1) {
        result += mx_move_file(data->name_from, data->name_to,
                               data->message, data->name_to);
        result += mx_move_file(data->name_to, data->name_from,
                               data->message, data->name_to);
        mx_del_after(data->name_to, data->file_name);
    }
    return result;
}

