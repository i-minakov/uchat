#include "uchat.h"

void hide_set(t_main *m) {
    hide_menu(m);
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
    gtk_widget_hide(m->set->sett_fix);
    // gtk_widget_hide(m->set->sett_box);
    // gtk_widget_hide(m->set->sett_fix);
    // gtk_widget_hide(m->set->lang_text);
    // gtk_widget_hide(m->set->color_text);
    // gtk_widget_hide(m->set->lang1);
    // gtk_widget_hide(m->set->lang2);
    // gtk_widget_hide(m->set->color1);
    // gtk_widget_hide(m->set->color2);
    // gtk_widget_hide(m->set->my_name);
    // gtk_widget_hide(m->set->set_but);
    // gtk_widget_hide(m->set->my_photo);
    // gtk_widget_hide(m->set->my_frame);
    m->set->flag = 0; 
}
