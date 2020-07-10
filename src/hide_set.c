#include "../inc/uchat.h"

void hide_set(t_main *m) {
    gtk_widget_hide(m->set->sett_box);
    gtk_widget_hide(m->set->sett_fix);
    gtk_widget_hide(m->set->lang_text);
    gtk_widget_hide(m->set->color_text);
    gtk_widget_hide(m->set->lang1);
    gtk_widget_hide(m->set->lang2);
    gtk_widget_hide(m->set->color1);
    gtk_widget_hide(m->set->color2);
    gtk_widget_hide(m->set->my_name);
    gtk_widget_hide(m->set->set_but);
    gtk_widget_hide(m->set->my_photo);
    gtk_widget_hide(m->set->my_frame);
    m->set->flag = 0; 
}
