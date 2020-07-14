#include "../inc/uchat.h"

void wid_ch(t_main *m) {
    MX_SHOW_HIDE(m->style->color, m->bottom_b);
    MX_SHOW_HIDE(m->style->color, m->top_b);
    MX_SHOW_HIDE(m->style->color, m->set->sett_box);
    MX_SHOW_HIDE(m->style->color, m->dots->dot_img);
    MX_SHOW_HIDE(m->style->color, m->menu->menu_box);
    MX_SHOW_HIDE(m->style->color, m->set->my_frame);
}

void change_color(GtkToggleButton *togglebutton, t_main *m) {
    if (m->style->color == 1) 
        m->style->color = 2;
    else 
        m->style->color = 1;
    connect_css(m, 2);
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    wid_ch(m);
}
