#include "../inc/uchat.h"

t_user *mx_create_user() {
    t_user *user = (t_user *)malloc(sizeof(t_user) * 100);

    user->check = false;
    user->row = 0;
    user->next = NULL;
    user->head = NULL;
    user->msg = create_msg(NULL);
    user->msg->count = -1;
    user->m = NULL;
    return user;
}
