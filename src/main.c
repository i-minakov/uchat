#include "../inc/uchat.h"

static void user_pushback(t_user **head) {
    t_user *tmp = *head;

    if (tmp == NULL) {
        *head = mx_create_user();
        (*head)->head = *head;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = mx_create_user();
    tmp->next->head = *head;
}

void set_chat_grid(t_main *m) {

    for (t_user *i = m->users; i; i = i->next) {
        i->y_chat = 30;
        i->text_grid = gtk_grid_new();
        ///////////////////////////
        // read from DB
        ///////////////////////////
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 0);
    }
}

int main(int argc, char *argv[]) {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 100);
    m->users = NULL;

    for (int i = atoi(argv[1]); i > 0; i--)
        user_pushback(&m->users);
    gtk_init(&argc, &argv);
    m->builder = gtk_builder_new_from_file("./src/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    g_signal_connect(m->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(m->builder, m->builder);
    m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
    m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
    m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));
    m->fix_for_users = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_user"));
    m->lab_start = GTK_WIDGET(gtk_builder_get_object(m->builder, "lab_start"));
    m->fix_for_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_text"));

    //////////////////////////////////////////////////////////////////////
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "./src/backg.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                GTK_STYLE_PROVIDER(cssProvider),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
    //////////////////////////////////////////////////////////////////////

    set_users(m);
    set_chat_grid(m);
    gtk_label_set_text(GTK_LABEL(m->lab_start), "Please select a chat to start messaging");
    gtk_widget_show_all(m->window);
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
    }
    gtk_main(); 
    free_users(&m->users);
    free(m);
    return 0;
}
