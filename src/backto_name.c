#include "../inc/uchat.h"

void backto_name(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    (void)entry;
    (void)icon_pos;
    (void)event;
    gtk_widget_hide(m->set->chan_name);
    gtk_widget_show(m->set->my_name);
}
