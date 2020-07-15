#include "../inc/uchat.h"

void add_message(t_main *m, t_user *i) {
    GtkWidget *wid;
    char *str = mx_strnew(mx_strlen(m->text) + ((mx_strlen(m->text)/50) + 1));
    int k = 0;

    for (int j = 0; m->text[j]; j++) {
        str[k++] = m->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    msg_pushfront(&i->msg, str);
    gtk_grid_insert_row(GTK_GRID(m->grid_user), i->msg->next->count);
    i->msg->next->user = i;
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(wid, 630, 30);
    MX_MSG_PACK(i->msg->next->my, i->msg->next->label, wid);
    gtk_grid_attach(GTK_GRID(i->text_grid), wid, 0, i->msg->next->count, 1, 1);
    gtk_widget_show_all(wid);
    i->msg->next->adj_value = gtk_adjustment_get_value(m->adj);
    i->row++;
    reset_l_mess(i);
    free(str);
}

void send_but(GtkWidget *wid, t_main *m) {

    m->text = (char *)gtk_entry_get_text(GTK_ENTRY(m->sms));
    if (!m->text || !mx_strlen(m->text))
        return ;
    reset_users(m);
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true)
            add_message(m, i);
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
    gtk_adjustment_set_value(m->adj, 
                gtk_adjustment_get_upper(m->adj) -
                     gtk_adjustment_get_page_size(m->adj) + 50.0);
}
// Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
