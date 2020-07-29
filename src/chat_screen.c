#include "../inc/uchat.h"

/* idle func */
void mx_destroy(GtkWidget *wid) {
    gtk_widget_destroy(wid);
    g_idle_remove_by_data(wid);
}
void mx_show(GtkWidget *wid) {
    gtk_widget_show_all(wid);
    g_idle_remove_by_data(wid);
}
void mx_hide(GtkWidget *w) {
    gtk_widget_hide(w);
    g_idle_remove_by_data(w);
}
void mx_idle_destroy(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_destroy(wid);
    else 
        g_idle_add((GSourceFunc)mx_show, wid);
}
void mx_idle_show(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_show_all(wid);
    else 
        g_idle_add((GSourceFunc)mx_show, wid);
}
void mx_idle_hide(bool flag, GtkWidget *wid) {
    if (flag == true)
        gtk_widget_hide(wid);
    else 
        g_idle_add((GSourceFunc)mx_hide, wid);
}

/* user utils */
void mx_remove_user_by_name(t_user **users, char *name) {
    t_user *us = *users;
    t_user *tmp = NULL;

    for (t_user *i = us; i->next; i = i->next) {
        if (!mx_strcmp(name, i->next->name)) {
            tmp = i->next->next;
            mx_strdel(&i->next->name);
            free_msg(&i->next->msg);
            gtk_grid_remove_row(GTK_GRID(us->m->grid_user), i->next->count);
            gtk_grid_remove_row(GTK_GRID(us->fix), i->next->count);
            free(i->next);
            i->next = tmp;
            break;
        }
    }
}
t_msg *mx_msg_by_id(t_user *us, int id) {
    t_msg *msg = NULL;

    for (t_msg *i = us->msg->next; i; i = i->next)
        i->id == id ? msg = i : 0;
    return msg;
}
t_user *mx_activ_us(t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next)
        i->check == true ? us = i : 0;
    return us;
}
void user_pushfront(t_user **head, char *name, char *path) {
    t_user *tmp = *head;

    *head = mx_create_user(name, path);
    (*head)->next = tmp;
    (*head)->head = *head;
    for (t_user *i = tmp; i; i = i->next) {
        i->count++;
        i->head = *head;
    }
}
t_user *mx_user_by_name(char *name, char *path, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next) 
        !mx_strcmp(i->name, name) ? us = i : 0;
    if (us == NULL) {
        user_pushfront(&m->users, name, path);
        mx_idle_destroy(false, m->grid_user);
        set_users(m);
        set_chat_grid(m, 1);
        g_idle_add((GSourceFunc)mx_show, m->fix_for_users);
        for (t_user *i = m->users; i; i = i->next) 
            i->next == NULL ? us = i : 0;
    }
    return us;
}

/* search user util */
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

/* init component */
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
    c->my_photo = resize_proportion(mx_cooljoin(mx_delit_fre 
        (mx_strjoin("./source/cash_", c->m->my_name), "/"),  
            mx_strjoin(c->m->my_name, ".jpg")), 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./source/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./source/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./source/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">%s</span>", c->m->my_name);

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

/* chat screen main */
static void hide_something(t_main *m) {
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
    gtk_widget_hide(m->micro_of_but);
    gtk_widget_hide(m->set->chan_name);
    gtk_widget_hide(m->set->chan_pas);
    gtk_widget_hide(m->grid_stic);
    gtk_widget_hide(m->stic_scrol);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->forw->fix_forw);
    gtk_widget_hide(m->search);
}
static void check_cmd(t_main *m) {
    if (m->cmd == SIG_UP) {
        m->my_name = mx_strdup(m->log_in->sig->signame);
        m->cmd = BLCK;
    }
    if (m->cmd == SIG_IN) 
        m->my_name = mx_strdup(m->log_in->log->logname);
        m->cmd = BLCK;
}
t_main *malloc_main() {
    t_main *m = (t_main *)malloc(sizeof(t_main));

	m->log_in = (t_wid *)malloc(sizeof(t_wid) * 10);
	m->log_in->sig = (t_sign *)malloc(sizeof(t_sign) * 16);
	m->log_in->log = (t_login *)malloc(sizeof(t_login) * 10);
	m->log_in->m = m;
	m->log_in->m->log_in = m->log_in;
	m->log_in->sig->sigfile = NULL;

    m->exit = 0;
    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->menu = (t_menu *)malloc(sizeof(t_menu) * 100);
    m->style = (t_style *)malloc(sizeof(t_style) * 100);
    m->set = (t_setting *)malloc(sizeof(t_setting) * 100);
    m->dots = (t_dots *)malloc(sizeof(t_dots) * 10);
    m->forw = (t_forw *)malloc(sizeof(t_forw) * 10);
    m->stic = (t_sticker *)malloc(sizeof (t_sticker *) * 100);
    m->emo = (t_emoji *)malloc(sizeof (t_emoji *) * 100);
    m->count_reqw = 0;
    m->count_reqw_edit = 0;
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
    m = NULL;
}
int mx_chat_screen(t_main **gtk) {
    t_main *m = *gtk;
    int ex = 0;

    m->order = 0;
    check_cmd(m);
    // for (int i = 10; i > 0; i--) 
    //     user_pushback(&m->users, "yarik"); 
    init_components(m);
    init_signals(m);  
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    gtk_widget_destroy(m->log_in->fixed);
    gtk_widget_hide(m->log_in->window);
    gtk_widget_show_all(m->window);
    hide_something(m);
    m->cmd = DEF;
    change_lang(NULL, m);
    change_color(NULL, m);
    mx_del_strarr(&m->command);
    return ex;
}

