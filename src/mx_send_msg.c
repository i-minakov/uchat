#include "../inc/uchat.h"

/**/
t_add_m *create_struct(char *text, bool my, int forw, char *time_m) {
    t_add_m *new = (t_add_m *)malloc(sizeof(t_add_m) * 6);

    new->text = text;
    new->my = my;
    new->id = -1;
    new->forw = forw;
    new->time_m = time_m;
    new->forw_from = NULL;
    new->reply_id = -1;
    return new;
}

void add_message(t_user *i, t_add_m *s, int id) {
    char *str = str_for_msg(s);

    msg_pushfront(&i->msg, str, s->my, s->forw);
    gtk_grid_insert_row(GTK_GRID(i->text_grid), i->row);
    i->msg->next->user = i;
    i->msg->next->id = mx_id_for_msg(i, id);
    i->msg->next->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(i->msg->next->box, 650, 30);
    add_time(i, s);
    MX_MSG_PACK(s->my, i->msg->next->label, i->msg->next->box);
    gtk_grid_attach(GTK_GRID(i->text_grid), i->msg->next->box, 0, i->row++, 1, 1);
    mx_idle_show(s->my, i->msg->next->box);
    MX_SCROL_END(i->m);
    reset_l_mess(i);
    free(str);
    if (s->my == false && i->check == false &&
            gtk_widget_is_visible(i->newmsg) == false) {
        mx_idle_show(false, i->newmsg);
    }
    mx_notif(s, i);
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
            add_message(i, s, i->exist_id ? mx_atoi(i->exist_id->data) + 1 : 1);
            command_msg(i, s, 0);
            free(s->time_m);
            free(s);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(m->sms), "");
}
