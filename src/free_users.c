#include "../inc/uchat.h"

void free_users(t_user **list) {
    t_user *tmp = *list;
    while(tmp) {
        t_user *hren = tmp->next;
        free(tmp);
        tmp = NULL;
        tmp = hren;
    }
}
