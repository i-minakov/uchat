#include "../inc/uchat.h"

t_user *mx_user_by_name(char *name, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next) 
        !mx_strcmp(i->name, name) ? us = i : 0;
    if (us == NULL) {
        user_pushback(&m->users, name);
        reset_users(m);
        set_chat_grid(m);
        g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
        for (t_user *i = m->users; i; i = i->next) 
            i->next == NULL ? us = i : 0;
    }
    return us;
}

void mx_show(GtkWidget *wid) {
    gtk_widget_show_all(wid);
    g_idle_remove_by_data(wid);
}

void user_pushback(t_user **head, char *name) {
    t_user *tmp = *head;

    if (tmp == NULL) {
        *head = mx_create_user(name);
        (*head)->head = *head;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = mx_create_user(name);
    tmp->next->head = *head;
}

void set_chat_grid(t_main *m) {

    for (t_user *i = m->users; i; i = i->next) {
        if (i->next == NULL) {
            i->row = 0;
            i->text_grid = gtk_grid_new();
            gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
            gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 10);
        }
    }
}

static void set_cap(t_cap *c) {
    c->my_name = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_proportion("./src/resource/index.jpg", 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./src/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./src/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", c->m->my_name);

    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_photo, 23, 20);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->frame_for_my_photo, 23, 20);
    gtk_label_set_markup(GTK_LABEL(c->my_name), markup); 
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->dot_menu, 941, 32);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_name, 83, 38);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->friend_name, 353, 37);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->burger_but_img, 267, 42);
    gtk_widget_show_all(c->fix_cap);
    g_free(markup);
}

void init_components(t_main *m) {
    init_main_stuff(m);
    set_users(m);
    set_chat_grid(m);
    set_cap(m->cap);
    init_menu(m);
    init_set(m);
    init_dot_forv(m);

}

/////////////////////////////////////////////

void hide_something(t_main *m) {
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    gtk_widget_hide(m->edit_entry);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
        gtk_widget_hide(i->text_grid);
    }
    the_ic(1, m);
    hide_menu(m);
    hide_set(m);
    gtk_widget_hide(m->stic_scrol);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->forw->fix_forw);
    gtk_widget_hide(m->search);
}

t_main *malloc_main() {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 100);

    m->exit = 0;
    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->menu = (t_menu *)malloc(sizeof(t_menu) * 100);
    m->style = (t_style *)malloc(sizeof(t_style) * 100);
    m->set = (t_setting *)malloc(sizeof(t_setting) * 100);
    m->dots = (t_dots *)malloc(sizeof(t_dots) * 10);
    m->forw = (t_forw *)malloc(sizeof(t_forw) * 10);
    m->stic = (t_sticker *)malloc(sizeof (t_sticker *) * 100);
    m->users = NULL;
    m->command = NULL;
    m->my_name = NULL;
    m->cap->m = m;
    return m;
}

void free_all(t_main *m) {
    free_users(&m->users);
    free(m->cap);
    free(m->menu);
    free(m->style);
    free(m->set);
    free(m->dots);
    free(m->forw);
    free(m->stic->but);
    free(m->stic->img);
    mx_del_strarr(&m->stic->way);
    free(m);
}

int chat_screen(t_main **gtk) {
    t_main *m = *gtk;
    int ex = 0;

    m->order = 0;
    m->my_name = m->log_in->sig->signame;
    m->command = mx_arrjoin(m->command, "mx_add_new_user");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, m->log_in->sig->sigpas);
    m->command = mx_arrjoin(m->command, "./index.jpg");
    // for (int i = 10; i > 0; i--)
        // user_pushback(&m->users, "yarik");
    init_components(m);
    connect_css(m, 1);
    init_signals(m);  
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    g_idle_add((GSourceFunc)move_scrol, m);
    gtk_widget_show_all(m->window);
    hide_something(m);
    return ex;
}

int interface() {
    t_main *m = malloc_main();
    
    gtk_init(NULL, NULL);
    // log_screen();
    chat_screen(&m);
    gtk_main();
    free_all(m);
    return 0;
}
