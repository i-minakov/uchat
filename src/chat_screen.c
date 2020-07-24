#include "../inc/uchat.h"

void user_pushfront(t_user **head, char *name) {
    t_user *tmp = *head;

    *head = mx_create_user(name);
    (*head)->next = tmp;
    (*head)->head = *head;
    for (t_user *i = tmp; i; i = i->next) {
        i->count++;
        i->head = *head;
    }
}

t_search *mx_create_node_search(char *name, char *path) {
    t_search *new = (t_search *)malloc(sizeof(t_search));

    new->name = mx_strdup(name);
    new->path = mx_strdup(path);
    new->next = NULL;
    return new;
}

void pushfront_search_contact(t_search **head, t_main *m, char *name, char *path) {
    t_search *tmp = mx_create_node_search(name, path);

    if (!head || !*head) {
        *head = tmp;
        (*head)->m = m;
        return;
    }
    tmp->next = *head;
    *head = tmp;
    (*head)->m = m;
}

t_user *mx_user_by_name(char *name, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next) 
        !mx_strcmp(i->name, name) ? us = i : 0;
    if (us == NULL) {
        user_pushfront(&m->users, name);
        gtk_widget_destroy(m->grid_user);
        set_users(m);
        set_chat_grid(m, 1);
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

void mx_hide(GtkWidget *w) {
    gtk_widget_hide(w);
    g_idle_remove_by_data(w);
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

void set_chat_grid(t_main *m, int flag) {
    if (flag == 0) {
        for (t_user *i = m->users; i; i = i->next) {
            i->row = 0;
            i->text_grid = gtk_grid_new();
            gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
            gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 10);
        }   
    }
    else {
        m->users->row = 0;
        m->users->text_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(m->users->text_grid), 20);
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), m->users->text_grid, 0, 10);
    }
}

static void set_cap(t_cap *c) {
    c->my_name = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_proportion("./source/resource/index.jpg", 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./source/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./source/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./source/resource/dots.png");
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
    set_chat_grid(m, 0);
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

    gtk_widget_hide(m->micro_on);
    gtk_widget_hide(m->set->chan_name);
    gtk_widget_hide(m->set->chan_pas);
    gtk_widget_hide(m->grid_stic);
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
    m->emo = (t_emoji *)malloc(sizeof (t_emoji *) * 100);
    m->srch= NULL;
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
    stic_free(m);
    free(m->stic);
    free(m->emo);
    free(m);
}

void check_cmd(t_main *m) {
    if (m->cmd == SIG_UP) {
        m->my_name = mx_strdup(m->log_in->sig->signame);
        m->command = mx_arrjoin(m->command, "mx_add_new_user");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, m->log_in->sig->sigpas);
        m->command = mx_arrjoin(m->command, "./index.jpg");
    }
    if (m->cmd == SIG_IN) 
        m->my_name = mx_strdup(m->log_in->log->logname);
}

int chat_screen(t_main **gtk) {
    t_main *m = *gtk;
    int ex = 0;

    m->order = 0;
    check_cmd(m);
    for (int i = 10; i > 0; i--) 
        user_pushback(&m->users, "yarik");
    init_components(m);
    connect_css(m, 1);
    init_signals(m);  
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    g_idle_add((GSourceFunc)move_scrol, m);
    gtk_widget_show_all(m->window);
    hide_something(m);
    if (m->style->color == 2)
        change_color(NULL, m);
    if (m->style->lang == 2)
        change_lang(NULL, m);
    m->cmd = DEF;
    return ex;
}

int interface() {
    t_main *m = malloc_main();
    
    gtk_init(NULL, NULL);
    log_screen(&m);
    chat_screen(&m);
    gtk_main();
    free_all(m);
    return 0;
}
