#include "../inc/uchat.h"

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

// static void set_new_grid(t_main *m) {
//     int row = 0;
//     int y = 0;

//     m->grid_user = gtk_grid_new();
//     for (t_user *i = m->users; i; i = i->next) {
//         gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
//         i->fix = gtk_fixed_new();
//         gtk_fixed_put(GTK_FIXED(i->fix), g_object_ref(i->img), 0, y);
//         gtk_fixed_put(GTK_FIXED(i->fix), g_object_ref(i->but), 0, y);
//         gtk_fixed_put(GTK_FIXED(i->fix), g_object_ref(i->l_name), 80, y + 10);
//         gtk_fixed_put(GTK_FIXED(i->fix), g_object_ref(i->l_mess), 80, y + 50);
//         gtk_grid_attach(GTK_GRID(m->grid_user), i->fix, 0, 0, 400, 85);
//         row++;
//         y += 85;
//     }
//     gtk_container_add(GTK_CONTAINER(m->fix_for_users), m->grid_user);
// }

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
    // set_new_grid(m);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true) {
            gtk_widget_hide(i->backg_us_slept);
            gtk_widget_hide(i->frame_photo_slept);
        }
        else {
            gtk_widget_hide(i->backg_us_activ);
            gtk_widget_hide(i->frame_photo_act);
        }
    }
}
