#include "../inc/uchat.h"

static void add_time(t_user *i, t_add_m *s) {
    char **m = NULL;
    time_t rawtime;
    struct tm * timeinfo;

    if (s->time_m == NULL) {
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        s->time_m = asctime(timeinfo);
        m = mx_strsplit(s->time_m, '\n');
        gtk_widget_set_tooltip_text(i->msg->next->label, m[0]);
        mx_del_strarr(&m);
    }
    else
        gtk_widget_set_tooltip_text(i->msg->next->label, s->time_m);
}

static void msg_pushback(t_msg **head, char *text, bool my, int forw) {
    t_msg *tmp = NULL;
    GtkWidget *item[4];
    int i = 0;
    char *s[] = {"Edit", "Reply", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {edit_msg, reply_msg, forward_msg, delete_msg};

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
    for (my == false || forw == 1 ? i = 1 : 0; i < 4; i++) {
        item[i] = gtk_menu_item_new_with_label(s[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

void add_message_back(t_user *i, t_add_m *s, int count) {
    GtkWidget *wid;
    char *str = mx_strnew(mx_strlen(s->text) + ((mx_strlen(s->text)/50) + 1));
    int k = 0;
    t_msg *msg = NULL;

    for (int j = 0; s->text[j]; j++) {
        str[k++] = s->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    msg_pushback(&i->msg, str, s->my, s->forw);
    for (t_msg *k = i->msg; k; k = k->next)
        if (k->next == NULL) {
            msg = k;
            k->user = i;
        }
    msg->count = count;
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(wid, 650, 30);
    add_time(i, s);
    MX_MSG_PACK(s->my, msg->label, wid);
    MX_SET_NAME_MSG(s->my, msg->label);
    gtk_grid_attach_next_to(GTK_GRID(i->text_grid), wid, NULL, GTK_POS_TOP, 1, 1);
    g_idle_add((GSourceFunc)mx_show, wid);
    msg->adj_value = gtk_adjustment_get_value(i->m->adj);
    reset_l_mess(i);
    free(str);
}
