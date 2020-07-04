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
    GtkWidget *w;

    for (t_user *i = m->users; i; i = i->next) {
        i->y_chat = 30;
        i->row = 0;
        i->text_grid = gtk_grid_new();
        // i->text_grid = gtk_fixed_new();
        // w = 
        ///////////////////////////
        // read from DB
        ///////////////////////////
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 0);
    }
}

static void set_cap(t_main *m) {
    GtkWidget *l = gtk_label_new(NULL);
    m->friend_name = gtk_label_new(NULL);
    m->my_photo = resize_image("./src/index.jpeg", 51, 51);
    m->frame_for_my_photo = gtk_image_new_from_file("./src/my photo.png");
    m->burger_but_img = gtk_image_new_from_file("./src/burger.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", "Ilysha");

    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->my_photo, 23, 20);
    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->frame_for_my_photo, 23, 20);
    gtk_label_set_markup(GTK_LABEL(l), markup); 
    gtk_fixed_put(GTK_FIXED(m->fix_cap), l, 83, 38);
    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->friend_name, 353, 42);
    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->burger_but_img, 267, 42);
    gtk_widget_show_all(m->fix_cap);
    g_free(markup);
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
    m->fix_cap = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_cap"));
    m->burger_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "burger_but"));

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
    set_cap(m);
    gtk_label_set_text(GTK_LABEL(m->lab_start), "Please select a chat to start messaging");
    gtk_widget_show_all(m->window);
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
    }
    gtk_main(); 
    g_object_unref(m->window);
    g_object_unref(m->builder);
    free_users(&m->users);
    free(m);
    return 0;
}
