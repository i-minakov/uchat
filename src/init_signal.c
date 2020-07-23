#include "../inc/uchat.h"

void show_setings(GtkWidget *wid, t_main *m) {
    show_set(m);
}

void hide_setings(GtkWidget *wid, t_main *m) {
    //провека данных
    hide_set(m);
}

static void entry_activate(GtkEntry *e, t_main *m) {
    send_but(m->but1, m);
}


void fun(GtkScrolledWindow *scrolled_window, GtkPositionType pos, t_main *m) {
    if (pos == GTK_POS_TOP && m->order == 2 && m->users->msg->count < 15) 
        printf("YES\n");
    else 
        return ;
    
    t_user *us = NULL;
    int adj = 0;
    int c = 0;

    for (t_user *i = m->users; i; i = i->next) 
        i->check == true ? us = i : 0;
    for (t_msg *j = us->msg; j; j = j->next) 
        j->next == NULL ? c = j->count - 1 : 0;
    int buf;
    char *s = NULL;
    int j = 0;
    int fd = open("./t.txt", O_RDWR);
    while(read(fd, &buf, 1)) {
        if (buf == 10) {
            add_message_back(us, create_struct(s, j%2 == 0 ? false : true, 0, NULL), c);
            mx_strdel(&s);
            j++;
            c--;
        }
        else s = mx_delit_fre(s, (char *)(&buf));
        buf = 0;
    }
    close(fd);
}

/////////////////////////////////////////////////////////////////////////////////////
void show_hide_dots_menu(GtkWidget *wid, t_dots *d) {
    MX_SHOW_HIDE(d->visible, d->fix_dot_menu);
    if (d->visible == 1) 
        d->visible = 0;
    else 
        d->visible = 1;
}

void clear_history(GtkWidget *wid, t_main *m) {
    t_user *us = NULL;

    for (t_user *i = m->users; i; i = i->next) 
        i->check == true ? us = i : 0;
    if (us == NULL)
        return ;
    gtk_widget_destroy(us->text_grid);
    free_msg(&us->msg);
    us->msg = create_msg(NULL, NULL);
    us->msg->count = -1;
    us->row = 0;
    us->text_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(us->text_grid), 20);
    gtk_fixed_put(GTK_FIXED(m->fix_for_text), us->text_grid, 0, 0);
    gtk_widget_show(us->text_grid);
    reset_l_mess(us);
}   

void block_user(GtkWidget *wid, t_main *m) {

}
//////////////////////////////////////////////////////////////////////////////////

void set_dots_signal(t_dots *d) {
    
    g_signal_connect(d->dot_but, "clicked", G_CALLBACK(show_hide_dots_menu), d);
    g_signal_connect(d->clear_msg_but, "clicked", G_CALLBACK(clear_history), d->m);
    g_signal_connect(d->block_but, "clicked", G_CALLBACK(block_user), d->m);
}

void show_search_msg(GtkWidget *w, t_main *m) {
    m->flag_search = 1;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    gtk_widget_show(m->search);
}

void show_search_users(GtkWidget *w, t_main *m) {
    m->flag_search = 2;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    hide_menu(m);
    gtk_widget_show(m->search);
}

void show_search_contacts(GtkWidget *w, t_main *m) {
    m->flag_search = 3;
    gtk_widget_hide(m->cap->burger_but_img);
    gtk_widget_hide(m->cap->burger_but);
    gtk_widget_hide(m->cap->my_photo);
    gtk_widget_hide(m->cap->frame_for_my_photo);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->cap->my_name);
    hide_menu(m);
    gtk_widget_show(m->search);
}

void free_srch(t_search **s) {
    if (!s || !*s)
        return;
    t_search *i = *s;
    t_search *j = NULL;

    for (; i; ) {
        j = NULL;
        if (i->next)
            j = i->next;
        mx_strdel(&i->name);
        i->next = NULL;
        free(i);
        i = NULL;
        i = j;
    }
    *s = NULL;
}

void close_search(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    if (icon_pos == GTK_ENTRY_ICON_PRIMARY)
        return ;
    gtk_widget_show(m->cap->burger_but_img);
    gtk_widget_show(m->cap->burger_but);
    gtk_widget_show(m->cap->my_photo);
    gtk_widget_show(m->cap->frame_for_my_photo);
    gtk_widget_show(m->cap->my_name);
    gtk_widget_hide(m->search);
    gtk_widget_destroy(m->grid_user);
    set_users(m);
    gtk_widget_show_all(m->fix_for_users);
    show_hide_back_us(m->users);
    burger_leave(NULL, NULL, m);
    if (m->flag_search == 3) 
        free_srch(&m->srch);
}

void exit_chat(GtkWidget *w, t_main *m) {
    m->exit = 1;
    gtk_widget_destroy(m->window);
    gtk_main_quit();
}

void change_photo(GtkWidget *w, t_main *m) {
    attach_file(NULL, 2, NULL, m);
}

void init_signals(t_main *m) {
    g_signal_connect(m->cap->burger_but, "enter-notify-event", G_CALLBACK(burger_notify), m);
    g_signal_connect(m->cap->burger_but, "clicked", G_CALLBACK(switch_menu), m);
    g_signal_connect(m->cap->burger_but, "leave-notify-event", G_CALLBACK(burger_leave), m);
    g_signal_connect(m->but1, "clicked", G_CALLBACK(send_but), m);
    g_signal_connect(m->sms, "activate", G_CALLBACK(entry_activate), m);
    g_signal_connect(m->sms, "icon-press", G_CALLBACK(attach_file), m);
    g_signal_connect(m->dots->search_msg_but, "clicked", G_CALLBACK(show_search_msg), m);
    g_signal_connect(m->scrol_bar, "edge-reached", G_CALLBACK(fun), m);
    g_signal_connect(m->search, "activate", G_CALLBACK(search_activ), m);
    g_signal_connect(m->search, "icon-press", G_CALLBACK(close_search), m);

    g_signal_connect(m->menu->settings, "clicked", G_CALLBACK(show_setings), m);
    g_signal_connect(m->set->set_but, "clicked", G_CALLBACK(hide_setings), m);
    g_signal_connect(m->set->color1, "toggled", G_CALLBACK(change_color), m);
    g_signal_connect(m->set->lang1, "toggled", G_CALLBACK(change_lang), m);
    g_signal_connect(m->menu->exit, "clicked", G_CALLBACK(exit_chat), m);
    g_signal_connect(m->menu->search, "clicked", G_CALLBACK(show_search_users), m);
    g_signal_connect(m->menu->contacts, "clicked", G_CALLBACK(show_search_contacts), m);

    g_signal_connect(m->set->my_name, "clicked", G_CALLBACK(enter_name), m);
    g_signal_connect(m->set->chan_name, "icon-press", G_CALLBACK(backto_name), m);
    g_signal_connect(m->set->chan_name, "activate", G_CALLBACK(change_name), m);
    g_signal_connect(m->set->my_pas, "clicked", G_CALLBACK(enter_pas), m);
    g_signal_connect(m->set->chan_pas, "icon-press", G_CALLBACK(backto_pas), m);
    g_signal_connect(m->set->chan_pas, "activate", G_CALLBACK(change_pas), m);
    g_signal_connect(m->set->chan_ph, "clicked", G_CALLBACK(change_photo), m);

    set_dots_signal(m->dots);
}
