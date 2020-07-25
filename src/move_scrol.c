#include "../inc/uchat.h"

void move_scrol(t_main *m) {
    gtk_adjustment_set_value(m->adj, 
        gtk_adjustment_get_upper(m->adj) -
                gtk_adjustment_get_page_size(m->adj) + 2.0);
    g_idle_remove_by_data(m);
}
