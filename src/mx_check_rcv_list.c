#include "../inc/header.h"

/* check rcv list and activ */
static void mx_msg_or_file(char **arr, char *id, t_user *us) {
    if (arr == NULL || id == NULL)
        return;
    if (mx_atoi(arr[FLG]) == 0)
        add_message(us, create_struct(arr[TXT], !mx_strcmp(us->m->my_name,
            arr[NAME]) ? true : false, 
                !arr[RPL_FORW] ? 0 : 1, arr[TIME]), mx_atoi(id));
    else 
        add_file(us, create_struct(arr[TXT], !mx_strcmp(us->m->my_name,
            arr[NAME]) ? true : false, 
                !arr[RPL_FORW] ? 0 : 1, arr[TIME]), mx_atoi(arr[FLG]), mx_atoi(id));
}

static bool mx_check_activ(t_main *m, t_list *list, int size) {
    t_user *us = mx_activ_us(m);
    char **arr = NULL;
    char *id_new = NULL;
    (void)size;

    if (!us || mx_strcmp(us->name, ((t_data *)list->data)->name) != 0)
        return false;
    if (mx_check_last_index(us, list) == true)
        return true;
    check_edited(us, ((t_data *)list->data)->list, size); // EDIT
    id_new = mx_get_value(((t_data *)list->data)->list->data, "command");
    if (!us->msg->next || mx_atoi(id_new) > mx_atoi(us->exist_id->data)) {
        arr = mx_get_arr(((t_data *)list->data)->list->data);
        mx_msg_or_file(arr, id_new, us);
        mx_del_strarr(&arr);
    }
    mx_strdel(&id_new);
    return true;
}

static void mx_cmp_list(t_main *m, t_info *info) {
    t_user *us = NULL;
    char *json = NULL;
    char *cmd = NULL;
    char **arr = NULL;

    for (t_list *i = info->list; i; i = i->next) {
        if (mx_check_activ(m, i, (mx_list_size(info->list) * FLAG)) == false) {
            us = mx_user_by_name(((t_data *)i->data)->name, ((t_data *)i->data)->path, m);
            json = ((t_data *)i->data)->list->data;
            cmd = mx_get_value(json, "command");
            arr = mx_get_arr(json);
            if (!us->msg->next || us->msg->next->id < mx_atoi(cmd)) 
                mx_msg_or_file(arr, cmd, us);
            mx_strdel(&cmd); 
            mx_del_strarr(&arr);
        }
    }
    mx_check_rename(m, info);
    m->count_reqw++;
    m->count_reqw_edit++;
}

void mx_check_rcv_list(t_info *info, t_main *m) {
    char *size = NULL;

    if (m->cmd == SRCH_US || m->cmd == SRCH_MSG) 
        show_result_of_search(info->list, m);
    else if (m->cmd == DEF)
        mx_cmp_list(m, info);
    else if (m->cmd == UPDATE_SIZE) {
        size = mx_itoa(mx_activ_us(m)->size_request);
        m->command = mx_arrjoin(m->command, "mx_update");
        m->command = mx_arrjoin(m->command, "size");
        m->command = mx_arrjoin(m->command, size);
        mx_strdel(&size);
        m->cmd = DEF;
    }
    else if (m->cmd == BLACK_LIST)
        mx_blacklist(m, info->list);
}
