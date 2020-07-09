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
        i->row = 0;
        i->text_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
        //////////////////
        // read from DB //
        //////////////////
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 0);
    }
}

static void set_cap(t_cap *c) {
    GtkWidget *l = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_image("./src/resource/index.jpeg", 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./src/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./src/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", "Ilysha");

    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_photo, 23, 20);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->frame_for_my_photo, 23, 20);
    gtk_label_set_markup(GTK_LABEL(l), markup); 
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->dot_menu, 941, 32);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), l, 83, 38);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->friend_name, 353, 42);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->burger_but_img, 267, 42);
    gtk_widget_show_all(c->fix_cap);
    g_free(markup);
}

int main(int argc, char *argv[]) {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 100);
    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->users = NULL;
    
    for (int i = atoi(argv[1]); i > 0; i--)
        user_pushback(&m->users);
    gtk_init(&argc, &argv);
    m->builder = gtk_builder_new_from_file("./src/resource/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    g_signal_connect(m->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(m->builder, m->builder);
    m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
    m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
    m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));
    m->fix_for_users = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_user"));
    m->lab_start = GTK_WIDGET(gtk_builder_get_object(m->builder, "lab_start"));
    m->fix_for_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_text"));
    m->cap->fix_cap = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_cap"));
    m->cap->burger_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "burger_but"));
    m->cap->dot_menu_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
    m->scrol_bar = GTK_WIDGET(gtk_builder_get_object(m->builder, "scrol_text"));
    m->edit_entry = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_edit"));
    m->file_ch = GTK_WIDGET(gtk_builder_get_object(m->builder, "file_chooser"));
    m->adj = gtk_adjustment_new(1.0, 1.0, 10000.0, 1.0, 10.0, 1.0);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(m->scrol_bar), m->adj);
    
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
    set_cap(m->cap);
    init_signals(m);
    gtk_label_set_text(GTK_LABEL(m->lab_start), "Please select a chat to start messaging");
    gtk_widget_show_all(m->window);
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    gtk_widget_hide(m->edit_entry);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
    }
    bool loop = true;
    while (loop) {
        loop = gtk_main_iteration();
    }
    free_users(&m->users);
    free(m);
    return 0;
}
