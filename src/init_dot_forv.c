#include "../inc/uchat.h"

void init_dot_forv(t_main *m) {
    m->dots->dot_img = GTK_WIDGET(gtk_builder_get_object(m->builder, "dot_img1"));
    m->dots->dot_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
    m->dots->fix_dot_menu = GTK_WIDGET(gtk_builder_get_object(m->builder, "dot_menu"));
    m->dots->block_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "block_but"));
    m->dots->clear_msg_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "clear_but"));
    m->dots->search_msg_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "search_but"));
    m->dots->visible = 1;
    m->dots->m = m;
    m->forw->forw_img = GTK_WIDGET(gtk_builder_get_object(m->builder, "forw_img"));
    m->forw->fix_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_forw"));
    m->forw->search_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "search_forw"));
    m->forw->fox_for_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_forw"));
    m->forw->but_cancel = GTK_WIDGET(gtk_builder_get_object(m->builder, "cancel_forw"));
    m->forw->m = m;
}
