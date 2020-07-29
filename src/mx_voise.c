#include "../inc/header.h"

void mx_voice(t_main *m) {
    mx_voice_save(m->my_name, m);
    gtk_widget_show(m->micro_of);
    gtk_widget_hide(m->micro_on);
    g_idle_remove_by_data(m);
}
