#include "uchat.h"

void enter_pas(GtkWidget *widget, t_main *m) {
    gtk_widget_hide(m->set->my_pas);
    gtk_widget_show(m->set->chan_pas);
}
