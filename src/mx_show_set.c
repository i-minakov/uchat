#include "../inc/header.h"

/* show settings */
void show_setings(GtkWidget *wid, t_main *m) {
    (void)wid;
    show_set(m);
}

void hide_setings(GtkWidget *wid, t_main *m) {
    (void)wid;
    hide_set(m);
}

void show_hide_dots_menu(GtkWidget *wid, t_dots *d) {
    (void)wid;
    if (mx_activ_us(d->m) == NULL)
        return;
    MX_SHOW_HIDE(d->visible, d->fix_dot_menu);
    if (d->visible == 1) 
        d->visible = 0;
    else 
        d->visible = 1;
}

