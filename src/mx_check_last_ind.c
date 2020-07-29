#include "../inc/header.h"

/* file or msg back and last ind */
static void mx_msg_or_file_back(char **arr, char *id, t_user *us, int count) {
    t_add_m *s = NULL;

    if (mx_atoi(arr[3]) == 0)
            add_message_back(us, create_struct(arr[TXT], !mx_strcmp(us->m->my_name,
                arr[NAME]) ? true : false, !arr[RPL_FORW] ? 0 : 1, arr[TIME]), count, mx_atoi(id));
    else {
        s = create_struct(arr[TXT], !mx_strcmp(us->m->my_name,
            arr[NAME]) ? true : false, !arr[RPL_FORW] ? 0 : 1, arr[TIME]);
        s->id = mx_atoi(id);
        add_file_back(us, s, mx_atoi(arr[FLG]), count);
    }
}

void mx_new_msg_back(t_user *us, t_list *list) {
    int c = 0;
    char *id_new = NULL;
    char **arr = NULL;

    for (t_msg *j = us->msg; j; j = j->next) 
        j->next == NULL ? c = j->count - 1 : 0;
    for (t_list *i = list; i; i = i->next) {
        id_new = mx_get_value(i->data, "command");
        arr = mx_get_arr(i->data);
        mx_msg_or_file_back(arr, id_new, us, c);
        mx_del_strarr(&arr);
        mx_strdel(&id_new);
        c--;
    }

}

static int find_last_ind_new(t_list *list) {
    char *id_new = NULL;
    int last_id_new = 0;

    for (t_list *k = ((t_data *)list->data)->list; k->data; k = k->next) {
        if (k->next->data == NULL) {
            id_new = mx_get_value(k->data, "command");
            last_id_new = mx_atoi(id_new);
            free(id_new);
        } 
    }
    return last_id_new;
}

bool mx_check_last_index(t_user *us, t_list *list) {
    char *id_new = NULL;
    int last_id_new = find_last_ind_new(list);
    int last_id_old = 0;
    t_list *new_ms = NULL;

    for (t_msg *i = us->msg->next; i; i = i->next)
        i->next == NULL ? last_id_old = i->id : 0;
    if (last_id_new < last_id_old) {
        for (t_list *k = ((t_data *)list->data)->list; k->data; k = k->next) { 
            id_new = mx_get_value(k->data, "command");
            if (mx_atoi(id_new) < us->msg->next->id)
                mx_push_back(&new_ms, mx_strdup(k->data));
            free(id_new);
        }
        mx_new_msg_back(us, new_ms);
        mx_free_list(&new_ms);
        return true;
    }
    return false;
}
