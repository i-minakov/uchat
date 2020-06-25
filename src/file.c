#include "../inc/uchat.h"

typedef struct s_data_users {
    GtkWidget *but;
    GtkWidget *fix;
    bool check;
    struct s_data_users *head;
    struct s_data_users *next;
}              t_user;

typedef struct s_main {
    GtkWidget *window;
    GtkWidget *fix1;
    GtkWidget *sms;
    GtkWidget *but1;
    GtkBuilder *builder;
    char *text;
    struct s_data_users *users;
}              t_main;

static t_user *mx_create_user() {
    t_user *users = (t_user *)malloc(sizeof(t_user) * 3);

    users->check = false;
    users->next = NULL;
    users->head = NULL;
    return users;
}

static void user_pushback(t_user **head) {
    t_user *tmp = *head;

    if (tmp == NULL) {
        *head = mx_create_user();
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = mx_create_user();
    tmp->next->head = *head;
}   

void user_click(GtkWidget *wid, t_user *users) {
    for (t_user *i = users->head; i; i = i->next)
        i->check = false;
    users->check = true;
}

void send_but(GtkWidget *wid, t_main *m) {
    m->text = gtk_entry_get_text(GTK_ENTRY(m->sms));
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true)
            gtk_button_set_label(GTK_BUTTON(i->but), m->text);
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
}


void init_signals_users(t_main *m) {
    g_signal_connect(m->but1, "clicked", G_CALLBACK(send_but), m);
    for (t_user *i = (m->users); i; i = i->next) {
        g_signal_connect(i->but, "clicked", G_CALLBACK(user_click), i);
    }
}

void chlen(GtkWidget *wid) {
    printf("chlen\n");
}

int main(int argc, char *argv[]) {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 7);
    m->users = NULL;
    int y = 30;
    int j = 0;
    char *s = NULL;
    GtkWidget *img;

    for (int i = atoi(argv[1]); i > 0; i--)
        user_pushback(&m->users);
    gtk_init(&argc, &argv);
    img = gtk_image_new_from_file("/home/ilya/Pictures/cat.png");
    m->builder = gtk_builder_new_from_file("./src/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    g_signal_connect(m->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(m->builder, m->builder);
    m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
    m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
    m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));

    for (t_user *i = m->users; i; i = i->next) {
        s = mx_cooljoin(mx_strdup("us"), mx_itoa(j));
        i->fix = GTK_WIDGET(gtk_builder_get_object(m->builder, s));
        i->but = gtk_button_new_with_label("View chat");
        gtk_fixed_put(GTK_FIXED(m->fix1), i->but, 400, y);
        gtk_widget_set_size_request(i->but, 40, 35);
        gtk_fixed_put(GTK_FIXED(i->fix), img, 0, y);
        // gtk_button_set_image(GTK_BUTTON(i->but), img);
        // gtk_button_set_image_position(GTK_BUTTON(i->but), GTK_POS_LEFT);
        // gtk_button_set_always_show_image (GTK_BUTTON (i->but), TRUE);
        y += 85;
        j++;
        free(s);
    }
    init_signals_users(m);
    gtk_widget_show_all(m->window);
    gtk_main();
    
    return 0;
}
