#include "../inc/uchat.h"

void show_setings(GtkWidget *wid, t_main *m) {
    (void)wid;
    show_set(m);
}

void hide_setings(GtkWidget *wid, t_main *m) {
    (void)wid;
    hide_set(m);
}

static void entry_activate(GtkEntry *e, t_main *m) {
    (void)e;
    send_but(m->but1, m);
}

void show_hide_dots_menu(GtkWidget *wid, t_dots *d) {
    (void)wid;
    if (mx_activ_us(d->m) == NULL)
        return;
    MX_SHOW_HIDE(d->visible, d->fix_dot_menu);
    if (d->visible == 1) 
        d->visible = 0;
    else 
        d->visible = 1;
}

void clear_history(GtkWidget *wid, t_main *m) {
    t_user *us = NULL;

    (void)wid;
    for (t_user *i = m->users; i; i = i->next) 
        i->check == true ? us = i : 0;
    if (us == NULL)
        return ;
    gtk_widget_destroy(us->text_grid);
    free_msg(&us->msg);
    us->msg = create_msg(NULL, NULL);
    us->msg->count = -1;
    us->msg->id = 0;
    us->row = 0;
    us->text_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(us->text_grid), 20);
    gtk_fixed_put(GTK_FIXED(m->fix_for_text), us->text_grid, 0, 10);
    gtk_widget_show(us->text_grid);
    reset_l_mess(us);
    m->command = mx_arrjoin(m->command, "mx_del_history");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, us->name);
}   

void block_user(GtkWidget *wid, t_main *m) {
    (void)wid;
    m->command = mx_arrjoin(m->command, "mx_add_user_to_table");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, mx_activ_us(m)->name);
    m->command = mx_arrjoin(m->command, "2");
}

void set_dots_signal(t_dots *d) {
    g_signal_connect(d->dot_but, "clicked", G_CALLBACK(show_hide_dots_menu), d);
    g_signal_connect(d->clear_msg_but, "clicked", G_CALLBACK(clear_history), d->m);
    g_signal_connect(d->block_but, "clicked", G_CALLBACK(block_user), d->m);
}

void show_search_msg(GtkWidget *w, t_main *m) {
    (void)w;
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
    (void)w;
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
    (void)w;
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
    (void)entry;
    (void)event;
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
    if (m->flag_search == 1) {
        gtk_widget_destroy(m->grid_search);
        gtk_widget_show_all(mx_activ_us(m)->text_grid);
    }
}

void exit_chat(GtkWidget *w, t_main *m) {
    (void)w;
    m->command = mx_arrjoin(m->command, "mx_log_out");
    m->command = mx_arrjoin(m->command, "log_out");
    m->cmd = LOG_OUT;
}

void mx_reset_my_photo(char *path, t_main *m) {
    gtk_widget_destroy(m->cap->my_photo);
    m->cap->my_photo = resize_proportion(path, 51, 51);
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->my_photo, 23, 20);
    gtk_widget_show(m->cap->my_photo);
    gtk_widget_destroy(m->set->my_photo);
    m->set->my_photo = resize_proportion(path, 80, 80);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_photo, 30, 30);
    gtk_widget_show(m->set->my_photo);
}

void change_photo(GtkWidget *w, t_main *m) {
    (void)w;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gchar *tmp = NULL;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename(chooser);
        mx_reset_my_photo((char *)tmp, m);
        m->command = mx_arrjoin(m->command, "mx_change_img");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, (char *)tmp);
    }
    gtk_widget_destroy(dialog);
    g_free(tmp);
}

void mx_increase_msg_list(GtkScrolledWindow *scrol_bar, 
                        GtkPositionType pos, t_main *m) {
    if (pos == GTK_POS_BOTTOM)
        return;
    (void)scrol_bar;    
    t_user *us = mx_activ_us(m);
    char *new = NULL;

    new = mx_itoa(us->size_request);
    m->command = mx_arrjoin(m->command, "mx_update");
    m->command = mx_arrjoin(m->command, "size");
    us->size_request += 20;
    m->command = mx_arrjoin(m->command, new);
    mx_strdel(&new);
}

void mx_reqw_for_bl(GtkWidget *wid, t_main *m) {
    (void)wid;
    hide_menu(m);
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file("./source/resource/cancel.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
    m->command = mx_arrjoin(m->command, "mx_send_list_back");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, "2");
    m->cmd = BLACK_LIST;
    for (int i = 0; m->command[i]; i++)
        printf("%s\n", m->command[i]);
}

void init_signals(t_main *m) {
    g_signal_connect(m->cap->burger_but, "enter-notify-event", G_CALLBACK(burger_notify), m);
    g_signal_connect(m->cap->burger_but, "clicked", G_CALLBACK(switch_menu), m);
    g_signal_connect(m->cap->burger_but, "leave-notify-event", G_CALLBACK(burger_leave), m);
    g_signal_connect(m->but1, "clicked", G_CALLBACK(send_but), m);
    g_signal_connect(m->sms, "activate", G_CALLBACK(entry_activate), m);
    g_signal_connect(m->sms, "icon-press", G_CALLBACK(attach_file), m);
    g_signal_connect(m->edit_entry, "icon-press", G_CALLBACK(attach_file), m);
    g_signal_connect(m->dots->search_msg_but, "clicked", G_CALLBACK(show_search_msg), m);
    g_signal_connect(m->scrol_bar, "edge-overshot", G_CALLBACK(mx_increase_msg_list), m);
    g_signal_connect(m->search, "activate", G_CALLBACK(search_activ), m);
    g_signal_connect(m->search, "icon-press", G_CALLBACK(close_search), m);
    g_signal_connect(m->menu->black_list, "clicked", G_CALLBACK(mx_reqw_for_bl), m);

    g_signal_connect(m->menu->settings, "clicked", G_CALLBACK(show_setings), m);
    g_signal_connect(m->set->set_but, "clicked", G_CALLBACK(hide_setings), m);
    g_signal_connect(m->set->color1, "toggled", G_CALLBACK(change_color), m);
    g_signal_connect(m->set->lang1, "toggled", G_CALLBACK(change_lang), m);
    g_signal_connect(m->set->notif1, "toggled", G_CALLBACK(change_notif), m);
    g_signal_connect(m->menu->exit, "clicked", G_CALLBACK(exit_chat), m);
    g_signal_connect(m->menu->search, "clicked", G_CALLBACK(show_search_contacts), m);
    g_signal_connect(m->menu->contacts, "clicked", G_CALLBACK(show_search_users), m);

    g_signal_connect(m->set->my_name, "clicked", G_CALLBACK(enter_name), m);
    g_signal_connect(m->set->chan_name, "icon-press", G_CALLBACK(backto_name), m);
    g_signal_connect(m->set->chan_name, "activate", G_CALLBACK(change_name), m);
    g_signal_connect(m->set->my_pas, "clicked", G_CALLBACK(enter_pas), m);
    g_signal_connect(m->set->chan_pas, "icon-press", G_CALLBACK(backto_pas), m);
    g_signal_connect(m->set->chan_pas, "activate", G_CALLBACK(change_pas), m);
    g_signal_connect(m->set->chan_ph, "clicked", G_CALLBACK(change_photo), m);

    g_signal_connect(m->micro_on_but, "clicked", G_CALLBACK(micro_start), m);
    g_signal_connect(m->micro_of_but, "clicked", G_CALLBACK(micro_end), m);

    set_dots_signal(m->dots);
}
