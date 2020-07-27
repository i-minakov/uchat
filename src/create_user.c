#include "../inc/uchat.h"

t_user *mx_create_user(char *name, char *path) {
    t_user *user = (t_user *)malloc(sizeof(t_user) * 100);

    user->check = false;
    user->row = 0;
    user->next = NULL;
    user->head = NULL;
    user->msg = create_msg(NULL, NULL);
    user->msg->count = -1;
    user->size_request = 20;
    user->m = NULL;
    user->photo_name = mx_strdup(path);
    user->name = mx_strdup(name);
    return user;
}
