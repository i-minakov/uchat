#include "uchat.h"

void show_hide_back_us(t_user *users) {
    for (t_user *i = users; i; i = i->next) {
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
