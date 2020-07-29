#include "../inc/header.h"

void mx_remove_user_by_name(t_user **users, char *name) {
    t_user *us = *users;
    t_user *tmp = NULL;

    for (t_user *i = us; i->next; i = i->next) {
        if (!mx_strcmp(name, i->next->name)) {
            tmp = i->next->next;
            mx_strdel(&i->next->name);
            free_msg(&i->next->msg);
            gtk_grid_remove_row(GTK_GRID(us->m->grid_user), i->next->count);
            gtk_grid_remove_row(GTK_GRID(us->fix), i->next->count);
            free(i->next);
            i->next = tmp;
            break;
        }
    }
}

t_msg *mx_msg_by_id(t_user *us, int id) {
    t_msg *msg = NULL;

    for (t_msg *i = us->msg->next; i; i = i->next)
        i->id == id ? msg = i : 0;
    return msg;
}

t_user *mx_activ_us(t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next)
        i->check == true ? us = i : 0;
    return us;
}

void user_pushfront(t_user **head, char *name, char *path) {
    t_user *tmp = *head;

    *head = mx_create_user(name, path);
    (*head)->next = tmp;
    (*head)->head = *head;
    for (t_user *i = tmp; i; i = i->next) {
        i->count++;
        i->head = *head;
    }
}

t_user *mx_user_by_name(char *name, char *path, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next) 
        !mx_strcmp(i->name, name) ? us = i : 0;
    if (us == NULL) {
        user_pushfront(&m->users, name, path);
        mx_idle_destroy(false, m->grid_user);
        set_users(m);
        set_chat_grid(m, 1);
        g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
        for (t_user *i = m->users; i; i = i->next) 
            i->next == NULL ? us = i : 0;
    }
    return us;
}
