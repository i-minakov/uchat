#include "../inc/uchat.h"

static void msg_pushback(t_msg **head, char *text, bool my, int forw) {
    t_msg *tmp = NULL;

    tmp = create_msg(text, NULL);
    tmp->my = my;
    tmp->forward = forw;
    for (t_msg *i = (*head); i; i = i->next) {
        if (i->next == NULL) {
            i->next = tmp;
            tmp->prev = i;
            break ;
        }
    }
    mx_add_popup_menu(0, tmp);
}

static t_msg *msg_new(t_add_m *s, t_user *i) {
    char *str = mx_strnew(mx_strlen(s->text) + ((mx_strlen(s->text)/50) + 1));
    t_msg *msg = NULL;
    int k = 0;

    for (int j = 0; s->text[j]; j++) {
        str[k++] = s->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    msg_pushback(&i->msg, str, s->my, s->forw);
    for (t_msg *k = i->msg; k; k = k->next) {
        if (k->next == NULL) {
            msg = k;
            k->user = i;
        }
    }
    free(str);
    return msg;
}

void add_message_back(t_user *i, t_add_m *s, int count, int id) {
    GtkWidget *wid;
    t_msg *msg = msg_new(s, i);

    msg->id = id;
    msg->count = count;
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(wid, 650, 30);
    add_time(i, s);
    MX_MSG_PACK(s->my, msg->label, wid);
    MX_SET_NAME_MSG(s->my, msg->label);
    gtk_grid_attach_next_to(GTK_GRID(i->text_grid), wid, NULL, GTK_POS_TOP, 1, 1);
    mx_idle_show(false, wid);
    reset_l_mess(i);
    free(s);
}
