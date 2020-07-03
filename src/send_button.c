#include "../inc/uchat.h"

static void reset_l_mess(t_main *m, t_user *i) {
    int k = 0;
    char *s = NULL;

    if (mx_strlen(m->text) > 27) {
        s = mx_strpart(m->text, 26);
        s = mx_delit_fre(s, "...");
        gtk_label_set_text(GTK_LABEL(i->l_mess), s);
        free(s);
    }
    else 
        gtk_label_set_text(GTK_LABEL(i->l_mess), m->text);
}

static void add_message(t_main *m, t_user *i) {
    GtkWidget *w;
    GtkWidget *lab;
    char *str = mx_strnew(mx_strlen(m->text) + (mx_strlen(m->text)%70));
    int k = 0;

    reset_l_mess(m, i);
    while (*m->text) {
        for (int j = 0; *m->text && j < 50; j++) {
            str[k] = *m->text;
            k++;
            m->text++;
        }
        str[k] = '\n';
        k++;
    }
    w = gtk_fixed_new();
    lab = gtk_label_new(str);
    gtk_grid_insert_row(GTK_GRID(m->grid_user), i->row);
    gtk_widget_set_halign(w, GTK_ALIGN_END);
    gtk_fixed_put(GTK_FIXED(w), lab, INDENT_YOU(mx_strlen(str)), i->y_chat);
    gtk_grid_attach(GTK_GRID(i->text_grid), w, 0, 0, 1, 1);
    gtk_widget_show_all(w);
    i->row++;
    i->y_chat += 50;
    free(str);
}

void send_but(GtkWidget *wid, t_main *m) {

    m->text = (char *)gtk_entry_get_text(GTK_ENTRY(m->sms));
    if (!mx_strlen(m->text))
        return ;
    reset_users(m);
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true) {
            add_message(m, i);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
    // gtk_grid_attach(GTK_GRID(i->text_grid), gtk_label_new(m->text));
}
