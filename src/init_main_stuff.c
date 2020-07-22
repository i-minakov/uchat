#include "../inc/uchat.h"

static void builder_and_stule(t_main *m) {
    m->builder = gtk_builder_new_from_file("./src/resource/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    g_signal_connect(m->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(m->builder, m->builder);
}
void init_main_stuff(t_main *m) {
    builder_and_stule(m);
    m->bottom_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "bottom_b"));
    m->top_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "top_b"));
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
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(m->scrol_bar), m->adj);
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(m->sms), 
        GTK_ENTRY_ICON_PRIMARY, MX_ICON_ENTRY_PR(m->style->color));
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(m->sms), 
        GTK_ENTRY_ICON_SECONDARY, MX_ICON_ENTRY_SEC(m->style->color));
}

