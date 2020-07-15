#include "../inc/uchat.h"

static void user_recipient(GtkWidget *wid, t_user *us) {
    t_msg_forw *fm = us->m->forw->fm;

    gtk_widget_hide(fm->f->fix_forw);
    user_click(NULL, us);
    if (fm->text) {
        us->m->text = mx_delit_fre(mx_delit_fre(mx_strjoin("forwared by ", fm->autor), ":\n"), fm->text);
        add_message(us->m, us);
    }
    else 
        add_file(us->m, (gchar *)fm->filename);
    reset_users(us->m);
    gtk_widget_destroy(fm->f->grid_forw);
    free(fm);
}

static void cancel_forw(GtkWidget *w, t_forw *f) {
    gtk_widget_destroy(f->grid_forw);
    gtk_widget_hide(f->fix_forw);
    free(f->fm);
}

static void create_window(t_forw *f, t_user *head) {
    int row = 0;
    GtkWidget *but;
    GtkWidget *box;
    GtkWidget *fix;

    for (t_user *i = head; i; i = i->next) {
        if (i->check == true)
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

void forward_msg(GtkMenuItem *item, t_msg *msg) {
    t_forw *f = msg->user->m->forw;

    f->fm = (t_msg_forw *)malloc(sizeof(t_msg_forw) * 10);
    f->fm->f = f;    
    f->fm->text = msg->text;
    f->fm->filename = msg->filename;
    f->fm->autor = msg->user->name;
    f->grid_forw = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(f->grid_forw), 10);
    create_window(f, msg->user->head);
    gtk_fixed_put(GTK_FIXED(f->fox_for_forw), f->grid_forw, 0, 0);
    g_signal_connect(f->but_cancel, "clicked", G_CALLBACK(cancel_forw), f);
    gtk_widget_show_all(f->fix_forw);
}
