#include "../inc/uchat.h"

void command_msg(t_user *us, t_add_m *s, int flag) {
    char *r_id = mx_itoa(flag);

    us->m->command = mx_arrjoin(us->m->command, "mx_recv_new_mess");
    us->m->command = mx_arrjoin(us->m->command, us->m->my_name);
    us->m->command = mx_arrjoin(us->m->command, us->name);
    us->m->command = mx_arrjoin(us->m->command, s->text);
    us->m->command = mx_arrjoin(us->m->command, r_id);
    us->m->command = mx_arrjoin(us->m->command, 
        s->forw == 1 ? s->forw_from : "NULL");
    mx_strdel(&r_id);
    if (s->reply_id != -1) {
        r_id = mx_itoa(s->reply_id);
        us->m->command = mx_arrjoin(us->m->command, r_id);
        free(r_id);
    }
    else 
        us->m->command = mx_arrjoin(us->m->command, "NULL");
}

void add_time(t_user *i, t_add_m *s) {
    char **m = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    if (s->time_m == NULL) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        s->time_m = mx_strdup(asctime(timeinfo));
        m = mx_strsplit(s->time_m, '\n');
        gtk_widget_set_tooltip_text(i->msg->next->label, m[0]);
        i->msg->next->time = mx_strdup(m[0]);
        mx_del_strarr(&m);
    }
    else {
        i->msg->next->time = mx_strdup(s->time_m);
        gtk_widget_set_tooltip_text(i->msg->next->label, s->time_m);
    }
}

void add_message(t_user *i, t_add_m *s, int id) {
    GtkWidget *wid;
    char *str = mx_strnew(mx_strlen(s->text) + ((mx_strlen(s->text)/50) + 1));
    int k = 0;

    for (int j = 0; s->text[j]; j++) {
        str[k++] = s->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    msg_pushfront(&i->msg, str, s->my, s->forw);
    gtk_grid_insert_row(GTK_GRID(i->text_grid), i->row);
    i->msg->next->user = i;
    i->msg->next->id = id;
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(wid, 650, 30);
    add_time(i, s);
    MX_MSG_PACK(s->my, i->msg->next->label, wid);
    gtk_grid_attach(GTK_GRID(i->text_grid), wid, 0, i->row++, 1, 1);
    mx_idle_show(s->my, wid);
    reset_l_mess(i);
    free(str);
    MX_SCROL_END(i->m);
    if (s->my == false && i->check == false &&
         gtk_widget_is_visible(i->newmsg) == false)
        mx_idle_show(false, i->newmsg);
}

void send_but(GtkWidget *wid, t_main *m) {
    char *text = NULL;
    t_add_m *s = NULL;

    (void)wid;
    text = (char *)gtk_entry_get_text(GTK_ENTRY(m->sms));
    if (text == NULL || !mx_strlen(text))
        return ;
    reset_users(m);
    s = create_struct(text, true, 0, NULL);
    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true) {
            add_message(i, s, i->msg->next 
                ? i->msg->next->id + 1 : 1);
            command_msg(i, s, 0);
            free(s->time_m);
            free(s);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
}
// Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
