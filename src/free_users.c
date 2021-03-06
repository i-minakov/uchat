#include "../inc/header.h"

void free_msg(t_msg **list) {
    t_msg *tmp = *list;
    t_msg *hren = NULL;

    while(tmp) {
        hren = tmp->next;
        mx_strdel(&tmp->text);
        mx_strdel(&tmp->filename);
        mx_strdel(&tmp->time);
        free(tmp);
        tmp = NULL;
        tmp = hren;
    }
}

void free_users(t_user **list) {
    t_user *tmp = *list;
    t_user *hren = NULL;

    while(tmp) {
        hren = tmp->next;
        free(tmp->name);
        free(tmp->photo_name);
        mx_free_list(&tmp->exist_id);
        free_msg(&tmp->msg);
        free(tmp);
        tmp = NULL;
        tmp = hren;
    }
}
