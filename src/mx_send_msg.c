#include "../inc/uchat.h"

/* msg send util */
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
static void mx_notif(t_add_m *s, t_user *i) { // PetFriend
    t_add_m *new = NULL;

    if (s->my == false && i->m->set->notif_flag == 1)
        g_idle_add((GSourceFunc)mx_play_audio, "./source/resource/meow.wav");
    if (s->my == true && !mx_strcmp(i->name, "PetFriend")) {
        new = create_struct("Sosi dick i kiday babki", false, 0, NULL);
        add_message(mx_user_by_name("PetFriend", MX_DEF_PHOTO, i->m), new, 
            mx_atoi(mx_user_by_name("PetFriend", MX_DEF_PHOTO, i->m)->exist_id->data) + 1);
    }
}

int mx_id_for_msg(t_user *us, int id) {
    while (us->exist_id && mx_atoi(us->exist_id->data) == id)
        id++;
    mx_push_front(&us->exist_id, mx_itoa(id));
    return id;
}
char *str_for_msg(t_add_m *s) {
    char *str = mx_strnew(mx_strlen(s->text) + ((mx_strlen(s->text)/50) + 1));
    int k = 0;

    for (int j = 0; s->text[j]; j++) {
        str[k++] = s->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    return str;
}

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
