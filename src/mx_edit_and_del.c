#include "../inc/header.h"

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
