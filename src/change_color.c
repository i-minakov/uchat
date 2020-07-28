#include "../inc/uchat.h"

static void sent_reqw(t_main *m) {
    char *str = mx_itoa(m->style->color - 1);

    m->command = mx_arrjoin(m->command, "mx_set_type");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, str);
    m->command = mx_arrjoin(m->command, "1");
    free(str);
}

static void wid_ch(t_main *m) {
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
    m->cap->frame_for_my_photo = gtk_image_new_from_file
        (MX_MY_PHOTO(m->style->color));
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), 
        m->cap->frame_for_my_photo, 23, 20);
    gtk_widget_show(m->cap->frame_for_my_photo);
}

static void change_toggle(t_main *m) {
    m->style->start_l = 0;
    if (m->style->color == 2) {
        g_signal_handlers_block_by_func(m->set->color1, 
            (gpointer) change_color, m);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(m->set->color2), TRUE);
        g_signal_handlers_unblock_by_func(m->set->color1, 
            (gpointer) change_color, m);
    }
}

void change_color(GtkToggleButton *togglebutton, t_main *m) {
    (void)togglebutton;
    if (m->style->start_l == 0) {
        if (m->style->color == 1) 
            m->style->color = 2;
        else 
            m->style->color = 1;
    }
    connect_css(m);
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    wid_ch(m);
    if (m->style->start_l == 0)
        sent_reqw(m);
    else
        change_toggle(m);
}

