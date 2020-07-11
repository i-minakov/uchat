#include "../inc/uchat.h"

void connect_css(t_main *m) {
    char *way = NULL;
    if (m->style->color == 1)
        way = "./src/black.css";
    else {
        gtk_widget_destroy(m->css);
        way = "./src/light.css";
    }
    m->css = gtk_css_provider_new();
    //GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(m->css, way, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
}
