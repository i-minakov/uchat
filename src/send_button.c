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
    GtkWidget *sms_img;
    char *str = mx_strnew(mx_strlen(m->text) + ((mx_strlen(m->text)/50) + 1));
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
    int r = mx_strlen(str) > 50 ? 250 : (250 + mx_strlen(str)*10);
    gtk_grid_insert_row(GTK_GRID(m->grid_user), i->row);
    w = gtk_fixed_new();
    lab = gtk_label_new(str);
    gtk_widget_set_halign(w, GTK_ALIGN_END);
    gtk_fixed_put(GTK_FIXED(w), lab, r, 30);
    // gtk_widget_set_size_request(lab, 300, 50);
    gtk_grid_attach(GTK_GRID(i->text_grid), w, 0, i->row, 1, 1);
    // gtk_fixed_put(GTK_FIXED(i->text_grid), w, INDENT_YOU(mx_strlen(str)), i->y_chat);
    // printf("%d\n", gtk_widget_get_allocated_width(lab));
    gtk_widget_show_all(w);
    i->y_chat += 50;
    i->row++;
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
}
// Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
