#include "../inc/uchat.h"

void connect_css(t_main *m, int flag) {
    char *way = NULL;
    if (flag != 1)
        gtk_widget_destroy(GTK_WIDGET(m->css));
    m->css = gtk_css_provider_new();
    gtk_css_provider_load_from_path(m->css, MX_CSS(m->style->color), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
}
