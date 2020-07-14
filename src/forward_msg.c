#include "../inc/uchat.h"

static void user_recipient(GtkWidget *wid, t_user *us) {
    t_msg_forw *fm = us->m->forw->fm;

    gtk_widget_hide(fm->f->fix_forw);
    user_click(NULL, us);
    if (fm->text) {
        us->m->text = mx_strjoin(mx_delit_fre(mx_strjoin("forwared by ", fm->autor), ":\n"), fm->text);
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
}

void forward_msg(GtkMenuItem *item, t_msg *msg) {
    t_forw *f = msg->user->m->forw;
    GtkWidget *but;
    GtkWidget *box;
    f->fm = (t_msg_forw *)malloc(sizeof(t_msg_forw) * 10);
    f->fm->f = f;
    int row = 0;
    
    f->fm->text = msg->text;
    f->fm->filename = msg->filename;
    f->fm->autor = msg->user->name;
    f->grid_forw = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(f->grid_forw), 10);
    for (t_user *i = msg->user->head; i; i = i->next) {
        if (i->check == true)
            continue;
        gtk_grid_insert_row(GTK_GRID(f->grid_forw), row);
        box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        MX_BOX_START(box, resize_image(i->photo_name, 50, 50));
        MX_BOX_END(box, gtk_label_new(gtk_label_get_text(GTK_LABEL(i->l_name))));
        but = gtk_button_new();
        gtk_widget_set_size_request(but, 200, 50);
        gtk_container_add(GTK_CONTAINER(but), box);
        gtk_grid_attach(GTK_GRID(f->grid_forw), but, 0, row, 1, 1);
        gtk_widget_show_all(but);
        g_signal_connect(but, "clicked", G_CALLBACK(user_recipient), i);
        row++;
    }
    gtk_fixed_put(GTK_FIXED(f->fox_for_forw), f->grid_forw, 0, 0);
    g_signal_connect(f->but_cancel, "clicked", G_CALLBACK(cancel_forw), f);
    gtk_widget_show_all(f->fix_forw);
}
