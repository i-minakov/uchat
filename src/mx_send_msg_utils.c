#include "../inc/header.h"

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

void mx_notif(t_add_m *s, t_user *i) { // PetFriend
    t_add_m *new = NULL;

    if (s->my == false && i->m->set->notif_flag == 1)
        g_idle_add((GSourceFunc)mx_play_audio, "./source/resource/meow.wav");
    if (s->my == true && !mx_strcmp(i->name, "PetFriend")) {
        new = create_struct("Help the animal", false, 0, NULL);
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
