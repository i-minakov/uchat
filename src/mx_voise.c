#include "../inc/header.h"

void mx_voice(t_main *m) {
    mx_voice_save(m->my_name);
    gtk_widget_show(m->micro_of);
    gtk_widget_hide(m->micro_on);
}
