#include "../inc/uchat.h"

void wid_ch(t_main *m) {
    MX_SHOW_HIDE(m->style->color, m->bottom_b);
    MX_SHOW_HIDE(m->style->color, m->top_b);
}

void change_color(GtkToggleButton *togglebutton, t_main *m) {
    if (m->style->color == 1) 
        m->style->color = 2;
    else 
        m->style->color = 1;
    connect_css(m, 2);
    // reset_users(m);
    wid_ch(m);
}
