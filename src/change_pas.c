#include "../inc/uchat.h"

void change_pas(GtkEntry *e, t_main *m) {
    gchar *tmp = NULL;

    (void)e;
    tmp = (char *)gtk_entry_get_text (GTK_ENTRY (m->set->chan_pas));
    if (tmp != NULL){
        gtk_widget_hide(m->set->chan_pas);
        gtk_widget_show(m->set->my_pas);
        m->command = mx_arrjoin(m->command, "mx_change_pass");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, (char *)tmp);

    }
}
