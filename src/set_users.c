#include "../inc/uchat.h"

static void init_signals_users(t_main *m) {
    for (t_user *i = (m->users); i; i = i->next)
        g_signal_connect(i->but, "clicked", G_CALLBACK(user_click), i);
}

static void init_component(t_user *i, t_main *m) {
    i->m = m;
    i->fix = gtk_fixed_new();
    i->img = resize_proportion(i->photo_name, 51, 51);
    i->but = gtk_button_new();
    i->backg_us_activ = gtk_image_new_from_file(MX_ACTIVE(m->style->color));
    i->backg_us_slept = gtk_image_new_from_file(MX_SLEPT(m->style->color));
    i->frame_photo_slept = gtk_image_new_from_file(MX_SL_PH(m->style->color));
    i->frame_photo_act = gtk_image_new_from_file(MX_ACT_PH(m->style->color));
    i->l_name = gtk_label_new(NULL);
    i->l_mess = gtk_label_new(NULL);
    i->l_time = gtk_label_new("15:20");
}

static void insert_component(t_user *i) {
    char *markup = NULL;

    gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_activ), 11, 0);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_slept), 11, 0);
    gtk_widget_set_opacity(i->but, 0.0);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->img), 23, 14);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_slept), 23, 14);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_act), 23, 14);
    gtk_widget_set_size_request(i->but, 305, 79);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->but), 11, 0);
    markup = g_markup_printf_escaped(MX_NAME_COLOR(i->m->style->color), i->name);
    gtk_label_set_markup(GTK_LABEL(i->l_name), markup); 
    reset_l_mess(i);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->l_name), 83, 21);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->l_mess), 83, 48);
    gtk_fixed_put(GTK_FIXED(i->fix), (i->l_time), 269,  21);
    g_free(markup);
}

void set_users(t_main *m) {
    int row = 0;

    m->grid_user = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(m->grid_user), 8);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
        init_component(i, m);
        insert_component(i);
        gtk_grid_attach(GTK_GRID(m->grid_user), i->fix, 0, row, 1, 1);
        i->count = row;
        row++;
    }
    gtk_fixed_put(GTK_FIXED(m->fix_for_users), m->grid_user, 0, 8);
    init_signals_users(m);
}
