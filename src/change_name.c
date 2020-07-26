#include "../inc/uchat.h"

void change_name(GtkEntry *e, t_main *m) {
    gchar *tmp = NULL;

    (void)e;
    tmp = (char *)gtk_entry_get_text (GTK_ENTRY (m->set->chan_name));
    if(tmp != NULL){
        gtk_button_set_label(GTK_BUTTON(m->set->my_name), tmp);
        gtk_widget_hide(m->set->chan_name);
        gtk_widget_show(m->set->my_name);
    }
}

