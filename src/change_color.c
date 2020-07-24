#include "../inc/uchat.h"

void wid_ch(t_main *m) {
    MX_SHOW_HIDE(m->style->color, m->bottom_b);
    MX_SHOW_HIDE(m->style->color, m->cap->top_b);
    MX_SHOW_HIDE(m->style->color, m->set->sett_box);
    MX_SHOW_HIDE(m->style->color, m->dots->dot_img);
    MX_SHOW_HIDE(m->style->color, m->menu->menu_box);
    MX_SHOW_HIDE(m->style->color, m->set->my_frame);
    MX_SHOW_HIDE(m->style->color, m->forw->forw_img);
    MX_SHOW_HIDE(m->style->color, m->stic_fix_img);
    the_ic(m->style->color, m);
    icon_entr_set(m);
    gtk_widget_destroy(m->cap->frame_for_my_photo);
    m->cap->frame_for_my_photo = gtk_image_new_from_file(MX_MY_PHOTO(m->style->color));
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->frame_for_my_photo, 23, 20);
    gtk_widget_show(m->cap->frame_for_my_photo);
}

void change_color(GtkToggleButton *togglebutton, t_main *m) {
    char *str = NULL;

    if (m->style->color == 1) 
        m->style->color = 2;
    else 
        m->style->color = 1;
    connect_css(m, 2);
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    wid_ch(m);
    str = mx_itoa(m->style->color);
    m->command = mx_arrjoin(m->command, "mx_set_type");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, str);
    m->command = mx_arrjoin(m->command, "1");
    free(str);
}

