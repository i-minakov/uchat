#include "uchat.h"

void free_msg(t_msg **list) {
    t_msg *tmp = *list;
    t_msg *hren = NULL;

    while(tmp) {
        hren = tmp->next;
        free(tmp->text);
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
        free_msg(&tmp->msg);
        free(tmp);
        tmp = NULL;
        tmp = hren;
    }
}
