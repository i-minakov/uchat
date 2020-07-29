#include "../inc/uchat.h"

void mx_exit(GtkWidget *object, t_main *m) {
    (void)object;
    m->command = mx_arrjoin(m->command, "mx_error");
    m->command = mx_arrjoin(m->command, "error");   
}

static void builder_and_style(t_main *m) {
    m->builder = gtk_builder_new_from_file("./source/resource/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    m->style->start_l = 1;
    m->style->start_c = 1;
    if (m->style->lang != 2 && m->style->lang != 1)
        m->style->lang = 1;
    if (m->style->color != 2 && m->style->color != 1)
        m->style->color = 1;
    g_signal_connect(m->window, "destroy", G_CALLBACK(mx_exit), m);
    gtk_builder_connect_signals(m->builder, m->builder);
}

void icons_micro_set(t_main *m) {
    icon_entr_set(m);
    m->micro_on = gtk_image_new_from_file("./source/resource/microon.gif");
    m->micro_of = gtk_image_new_from_file("./source/resource/micro.png");
    m->micro_on_but = gtk_button_new();
    m->micro_flag = 0;
    gtk_widget_set_size_request(m->micro_on_but, 50, 50);
    gtk_widget_set_opacity(m->micro_on_but, 0.0);
    gtk_fixed_put(GTK_FIXED(m->fix1), m->micro_on, 925, 629);
    gtk_fixed_put(GTK_FIXED(m->fix1), m->micro_of, 925, 629);
    gtk_fixed_put(GTK_FIXED(m->fix1), m->micro_on_but, 925, 629);
}

void init_main_stuff(t_main *m) {
    builder_and_style(m);
    m->bottom_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "bottom_b"));
    m->cap->top_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "top_b"));
    m->fix_for_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_text"));
    m->fix_for_users = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_user"));
    m->cap->fix_cap = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_cap"));
    m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
    m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
    m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));
    m->lab_start = GTK_WIDGET(gtk_builder_get_object(m->builder, "lab_start"));
    m->cap->burger_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "burger_but"));
    m->cap->dot_menu_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
    m->scrol_bar = GTK_WIDGET(gtk_builder_get_object(m->builder, "scrol_text"));
    m->edit_entry = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_edit"));
    m->search = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_search"));
    m->adj = gtk_adjustment_new(1.0, 1.0, 10.0, 1.0, 10.0, 1.0);
    m->bl = 0;
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(m->scrol_bar), m->adj);
    icons_micro_set(m);
}
