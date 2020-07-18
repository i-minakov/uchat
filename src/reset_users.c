#include "uchat.h"

static void user_pushfront(t_user **head, t_user *user) {
    t_user *tmp = *head;
    t_user *node = NULL;

    for (t_user *i = *head; i->next; i = i->next) {
        if (i->next->count == user->count) {
            node = i->next->next;
            *head = i->next;
            (*head)->next = tmp;
            (*head)->count = 0;
            i->next = node;
            i->count++;
            break; 
        }
        i->count++;
    }
    for (t_user *i = *head; i; i = i->next)
        i->head = *head;
}  

void reset_users(t_main *m) {
    t_user *tmp = NULL;

    gtk_widget_destroy(m->grid_user);
    for (t_user *i = m->users; i->next; i = i->next) {
        if (i->next->check == true) {      
            tmp = i->next->next;
            user_pushfront(&m->users, i->next);
            i->next = tmp;
            break;
        }
    }
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
}
