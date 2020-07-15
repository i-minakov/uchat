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

static void attach_file(GtkEntry *entry, GtkEntryIconPosition icon_pos, 
                GdkEvent *event, t_main *m) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    gchar *tmp = NULL;

    if (icon_pos == GTK_ENTRY_ICON_SECONDARY)
        return ;
    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
        add_file(m, tmp);
    }
    gtk_widget_destroy (dialog);
}

void fun (GtkScrolledWindow *scrolled_window, GtkPositionType pos, t_main *m) {
    if (pos == GTK_POS_TOP) 
        printf("YES\n");
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
    gtk_widget_hide(m->menu->menu_fix);
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
    gtk_widget_show(m->search);
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
}

void exit_chat(GtkWidget *w, t_main *m) {
    m->exit = 1;
    gtk_widget_destroy(m->window);
    gtk_main_quit();
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
    set_dots_signal(m->dots);
}
