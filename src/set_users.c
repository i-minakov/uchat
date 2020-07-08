#include "../inc/uchat.h"

void attach_file(GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, t_main *m) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    gchar *tmp = NULL;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
    }
    gtk_widget_destroy (dialog);
    for (int i = 0; tmp[i]; i++) {
        if (tmp[i] == '.' && (!strcmp(&tmp[i], ".png") || !strcmp(&tmp[i], ".jpg")
				|| !strcmp(&tmp[i], ".gif") || !strcmp(&tmp[i], ".svg"))) {
                    return;
                }
    }
}

static void burger_notify(GtkWidget *widget, GdkEvent *event, t_main *m) {
    gtk_widget_destroy(m->burger_but_img);
    m->burger_but_img = gtk_image_new_from_file("./src/resource/burger2.png");
    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->burger_but_img, 267, 37);
    gtk_widget_show(m->burger_but_img);
}

static void burger_leave(GtkWidget *widget, GdkEvent *event, t_main *m) {
    gtk_widget_destroy(m->burger_but_img);
    m->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    gtk_fixed_put(GTK_FIXED(m->fix_cap), m->burger_but_img, 267, 42);
    gtk_widget_show(m->burger_but_img);
}

static void entry_activate(GtkEntry *e, t_main *m) {
    send_but(m->but1, m);
}

static void init_signals_users(t_main *m) {
    g_signal_connect(m->burger_but, "enter-notify-event", G_CALLBACK(burger_notify), m);
    g_signal_connect(m->burger_but, "leave-notify-event", G_CALLBACK(burger_leave), m);
    g_signal_connect(m->but1, "clicked", G_CALLBACK(send_but), m);
    g_signal_connect(m->sms, "activate", G_CALLBACK(entry_activate), m);
    g_signal_connect(m->sms, "icon-press", G_CALLBACK(attach_file), m);
    // g_signal_connect(m->file_ch, "file-set", G_CALLBACK(attach_file), m);
    for (t_user *i = (m->users); i; i = i->next) {
        g_signal_connect(i->but, "clicked", G_CALLBACK(user_click), i);
    }
}

void set_users(t_main *m) {
    int y = 7;
    int row = 0;
    char *markup = NULL;

    m->grid_user = gtk_grid_new();
    for (t_user *i = m->users; i; i = i->next) {
        i->m = m;
        gtk_grid_insert_row(GTK_GRID(m->grid_user), row);
        i->fix = gtk_fixed_new();
        i->img = resize_image("./src/resource/index.jpeg", 51, 51);
        i->but = gtk_button_new();
        i->backg_us_activ = gtk_image_new_from_file("./src/resource/activated.png");
        i->backg_us_slept = gtk_image_new_from_file("./src/resource/slept.png");
        i->frame_photo_slept = gtk_image_new_from_file("./src/resource/slept photo.png");
        i->frame_photo_act = gtk_image_new_from_file("./src/resource/activated photo.png");
        gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_activ), 11, y);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_slept), 11, y);
        gtk_widget_set_opacity(i->but, 0.0);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->img), 23, y + 14);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_slept), 23, y + 14);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_act), 23, y + 14);
        gtk_widget_set_size_request(i->but, 305, 79);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->but), 11, y);
        i->l_name = gtk_label_new(NULL);
        markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", "Olya");
        gtk_label_set_markup(GTK_LABEL(i->l_name), markup); 
        i->l_mess = gtk_label_new(NULL);
        reset_l_mess(i);
        i->l_time = gtk_label_new("15:20");
        gtk_fixed_put(GTK_FIXED(i->fix), (i->l_name), 83, y + 21);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->l_mess), 83, y + 48);
        gtk_fixed_put(GTK_FIXED(i->fix), (i->l_time), 269, y + 21);
        gtk_grid_attach(GTK_GRID(m->grid_user), i->fix, 0, row, 305, 79);
        g_free(markup);
        y += 86;
        i->count = row;
        row++;
    }
    gtk_container_add(GTK_CONTAINER(m->fix_for_users), m->grid_user);
    init_signals_users(m);
}
