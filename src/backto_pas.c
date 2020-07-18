#include "uchat.h"
void backto_pas(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    gtk_widget_hide(m->set->chan_pas);
    gtk_widget_show(m->set->my_pas);
}
