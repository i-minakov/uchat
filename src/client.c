#include "../inc/header.h"

/* Ilay */
/* for files */
bool mx_check_file_format(char *path) {
    char **slesh = mx_strsplit(path, '/');
    char **dots = mx_strsplit(slesh[mx_arr_size(slesh) - 1], '.');

    if (mx_arr_size(dots) == 1) {
        mx_del_strarr(&dots);
        mx_del_strarr(&slesh);
        return false;
    }
    mx_del_strarr(&dots);
    mx_del_strarr(&slesh);
    return true;
}
void mx_move_to_part_dir(char *name, char *user) {
    if (!name || !user)
        return ;
    char *old = mx_super_join("./", name, 0);
    char *new = mx_super_join("./source/cash_", user, 0);

    new = mx_super_join(new, "/downloads/", 1);
    new = mx_super_join(new, name, 1);
    remove(new);
    rename(old, new);
    mx_strdel(&new);
    mx_strdel(&old);
}

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

/* edit and delete */
static void reset_edit_msg(t_msg *edited, char **arr) {
    mx_strdel(&edited->text);
    edited->text = mx_strdup(arr[TXT]);
    gtk_button_set_label(GTK_BUTTON(edited->label), arr[TXT]);
}
void check_edited(t_user *us, t_list *list, int size) {
    char *cmd = NULL;
    char **arr = NULL;
    t_msg *edited = NULL;

    if (size/10 != us->m->count_reqw_edit)
        return;
    for (t_list *i = list; i->data; i = i->next) {
        cmd = mx_get_value(i->data, "command");
        arr = mx_get_arr(i->data);
        if (mx_strcmp(arr[NAME], us->m->my_name) && mx_get_substr_index(arr[TIME], "edit") > -1) {
            edited = mx_msg_by_id(us, mx_atoi(cmd));
            if (edited && edited->text) 
                reset_edit_msg(edited, arr);
        }
        mx_strdel(&cmd); 
        mx_del_strarr(&arr);
    }
    us->m->count_reqw_edit = 0;
}
void mx_check_rename(t_main *m, t_info *info) {
    char *name = NULL;
    bool flag = false;

    for (t_list *i = info->list; i; i = i->next) {
        name = ((t_data *)i->data)->name;
        for (t_user *j = m->users; j; j = j->next) {
            !mx_strcmp(name, j->name) ? flag = true : 0;
        }
        if (flag == false)
            mx_remove_user_by_name(&m->users, name);
        flag = false;
    }
}

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

/* check sigin and sigup */
void mx_check_sigup(t_main *m) {
    if (m->cmd == SRCH_MSG) {
        m->command = mx_arrjoin(m->command, "mx_mssg_search");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, mx_activ_us(m)->name);
        m->command = mx_arrjoin(m->command, m->search_str);
        m->cmd = SRCH_US;
    }
    if (m->cmd == CHECK_US) {
        m->my_name = mx_strdup(m->log_in->sig->signame);
        m->command = mx_arrjoin(m->command, "mx_add_new_user");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, m->log_in->sig->sigpas);
        m->command = mx_arrjoin(m->command, 
            m->log_in->sig->sigfile ? m->log_in->sig->sigfile : MX_DEF_PHOTO);
        m->cmd = BLCK;
    }
}
void mx_check_sigin(t_main *m) {
    if (m->cmd == CHECK_PASS) {
        m->command = mx_arrjoin(m->command, "mx_check_user_pass");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, m->log_in->log->logpas);
        m->cmd = BLCK;
    }
    else if (m->cmd == LANG) {
        gtk_widget_hide(m->log_in->window);
		gtk_widget_destroy(m->log_in->fixed);
        m->command = mx_arrjoin(m->command, "mx_get_type");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, "0");
        m->cmd = BLCK;
    }
    else if (m->cmd == THEME) {
        m->command = mx_arrjoin(m->command, "mx_get_type");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, "1");
        m->cmd = BLCK;
    }
    mx_check_sigup(m);
}
/* end Ilay*/
