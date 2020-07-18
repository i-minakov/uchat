#include "uchat.h"

static void user_recipient(GtkWidget *wid, t_user *us) {
    t_msg_forw *fm = us->m->forw->fm;
    t_add_m *s = NULL;

    gtk_widget_hide(fm->f->fix_forw);
    user_click(NULL, us);
    if (fm->text) {
        if (fm->was_forw == 0) 
            us->m->text = mx_delit_fre(mx_delit_fre(
                mx_strjoin("forwared by ", fm->autor), ":\n"), fm->text);
        else
            us->m->text = fm->text;
        s = create_struct(us->m->text, true, 1, NULL);
        s->forw_from = mx_strdup(fm->autor);
        add_message(us, s);
    }
    else 
        add_file(us->m, (gchar *)fm->filename, true);
    reset_users(us->m);
    gtk_widget_destroy(fm->f->grid_forw);
    free(fm);
}

static void cancel_forw(GtkWidget *w, t_forw *f) {
    gtk_widget_destroy(f->grid_forw);
    gtk_widget_hide(f->fix_forw);
    free(f->fm);
}

static void create_window(t_forw *f, t_user *head, char *s) {
    int row = 0;
    GtkWidget *but;
    GtkWidget *box;
    GtkWidget *fix;

    for (t_user *i = head; i; i = i->next) {
        if (s != NULL && !mx_strstr(i->name, s))
            continue;
        fix = gtk_fixed_new();
        gtk_grid_insert_row(GTK_GRID(f->grid_forw), row);
        but = gtk_button_new();
        gtk_widget_set_opacity(but, 0.0);
        gtk_widget_set_size_request(but, 250, 50);
        gtk_fixed_put(GTK_FIXED(fix), but, 0, 0);
        gtk_fixed_put(GTK_FIXED(fix), gtk_label_new(gtk_label_get_text(GTK_LABEL(i->l_name))), 75, 20);
        gtk_fixed_put(GTK_FIXED(fix), resize_proportion(i->photo_name, 50, 50), 5, 5);
        gtk_grid_attach(GTK_GRID(f->grid_forw), fix, 0, row, 1, 1);
        gtk_widget_show_all(fix);
        g_signal_connect(but, "clicked", G_CALLBACK(user_recipient), i);
        row++;
    }
}

static void search_forw(GtkEntry *e, t_forw *f) {
    char *s = NULL;

    s = (char *)gtk_entry_get_text(e);
    gtk_widget_destroy(f->grid_forw);
    f->grid_forw = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(f->grid_forw), 10);
    create_window(f, f->m->users, s);
    gtk_fixed_put(GTK_FIXED(f->fox_for_forw), f->grid_forw, 0, 0);
    gtk_widget_show_all(f->fix_forw);
}

void forward_msg(GtkMenuItem *item, t_msg *msg) {
    t_forw *f = msg->user->m->forw;

    f->fm = (t_msg_forw *)malloc(sizeof(t_msg_forw) * 10);
    f->fm->f = f;    
    f->fm->text = msg->text;
    f->fm->was_forw = msg->forward;
    f->fm->filename = msg->filename;
    f->fm->autor = msg->user->name;
    f->grid_forw = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(f->grid_forw), 10);
    create_window(f, msg->user->head, NULL);
    gtk_fixed_put(GTK_FIXED(f->fox_for_forw), f->grid_forw, 0, 0);
    g_signal_connect(f->but_cancel, "clicked", G_CALLBACK(cancel_forw), f);
    g_signal_connect(f->search_forw, "activate", G_CALLBACK(search_forw), f);
    gtk_widget_show_all(f->fix_forw);
}
