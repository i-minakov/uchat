#include "../inc/uchat.h"

void user_click(GtkWidget *wid, t_user *users) {

    gtk_widget_hide(users->m->lab_start);
    gtk_widget_show(users->m->sms);
    gtk_widget_show(users->m->but1);
    for (t_user *i = users->head; i; i = i->next) {
        if (i->check == true) {
            gtk_widget_hide(i->backg_us_activ);
            gtk_widget_hide(i->frame_photo_act);
            gtk_widget_hide(i->text_grid);
            gtk_widget_show(i->backg_us_slept);
            gtk_widget_show(i->frame_photo_slept);
        }
        i->check = false;
    }
    users->check = true;
    gtk_widget_hide(users->backg_us_slept);
    gtk_widget_show(users->backg_us_activ);
    gtk_widget_hide(users->frame_photo_slept);
    gtk_widget_show(users->frame_photo_act);
    gtk_widget_show(users->text_grid);
}
