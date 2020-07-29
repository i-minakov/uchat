#include "../inc/uchat.h"

void micro_start(GtkWidget *w, t_main *m) {
    (void)w;
    gtk_widget_hide(m->micro_of);
    gtk_widget_show(m->micro_on);
    g_signal_handlers_block_by_func((void *)m->micro_on_but, 
		(void *)micro_start, (void *)m);
    g_idle_add((GSourceFunc)mx_voice, m);
    g_signal_handlers_unblock_by_func((void *)m->micro_on_but, 
		(void *)micro_start, (void *)m);
}
