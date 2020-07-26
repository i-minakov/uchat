#include "../inc/uchat.h"

void enter_name(GtkWidget *widget, t_main *m) {
    (void)widget;
    gtk_widget_hide(m->set->my_name);
    gtk_widget_show(m->set->chan_name);
}
