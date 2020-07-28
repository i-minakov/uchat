#include "../inc/uchat.h"

static void con(t_main *m) {
    if (m->style->color == 1) {
        m->css = gtk_css_provider_new();
        gtk_css_provider_load_from_path(m->css, "./src/black.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else {
        m->css2 = gtk_css_provider_new();
        gtk_css_provider_load_from_path(m->css2, "./src/light.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css2),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

static void rem(t_main *m) {
    if (m->style->color == 1) {
        m->css = gtk_css_provider_new();
        gtk_css_provider_load_from_path(m->css, "./src/unset.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
    else{
        m->css2 = gtk_css_provider_new();
        gtk_css_provider_load_from_path(m->css2, "./src/unset.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(m->css2),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}

void connect_css(t_main *m, int flag) {
    if (flag != 1)
    puts("++++\n");
        rem(m);
    con(m);
}
