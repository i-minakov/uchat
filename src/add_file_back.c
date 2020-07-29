#include "../inc/uchat.h"

static void file_pushback(t_msg **head, t_add_m *s) {
    t_msg *tmp = NULL;

    tmp = create_msg(NULL, s->text);
    tmp->my = s->my;
    tmp->forward = s->forw;
    for (t_msg *i = (*head); i; i = i->next) {
        if (i->next == NULL) {
            i->next = tmp;
            tmp->prev = i;
            break ;
        }
    }
}

static void send_file_back(t_user *us, t_add_m *s, t_msg *t) {
    t->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(t->box, 630, 30);
    MX_MSG_PACK(s->my, t->label, t->box);
    MX_SET_NAME_MSG(s->my, t->label);
    gtk_grid_attach_next_to(GTK_GRID(us->text_grid), t->box, NULL, GTK_POS_TOP, 1, 1);
    mx_idle_show(s->my, t->box);
    mx_add_popup_menu(t->stic, t);
}

static t_msg *mx_back_msg(t_msg *list) {
    t_msg *msg = NULL;

    for (t_msg *k = list; k; k = k->next) {
        if (k->next == NULL) {
            msg = k;
            k->user = list->user;
        }
    }
    return msg;
}

void add_file_back(t_user *us, t_add_m *s, int stic, int count) {
    t_msg *msg = NULL;
    char **p = mx_strsplit(s->text, '/');
    char *name = NULL;

    if (p)
        name = p[mx_len_of_array(p) - 1];
    else 
        name = s->text;
    file_pushback(&us->msg, s);
    msg = mx_back_msg(us->msg);
    msg->id = s->id;
    msg->user = us;
    msg->count = count;
    msg->stic = stic;
    if (stic == 1) {
        file_check(&msg, name, s->my);
        send_file_back(us, s, msg);
    }
    else {
        msg->file = gtk_image_new_from_file(s->text);
        gtk_button_set_image(GTK_BUTTON(msg->label), msg->file);
        send_file_back(us, s, msg);
    }
    mx_del_strarr(&p);
    free(s);
}
