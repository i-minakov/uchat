#include "../inc/uchat.h"

void change_pas(GtkEntry *e, t_main *m) {
    gchar *tmp = NULL;

    tmp = (char *)gtk_entry_get_text (GTK_ENTRY (m->set->chan_pas));
    if(tmp != NULL){
        gtk_button_set_label(GTK_BUTTON(m->set->my_pas), tmp);
        gtk_widget_hide(m->set->chan_pas);
        gtk_widget_show(m->set->my_pas);
    }
}
