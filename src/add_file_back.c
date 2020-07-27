#include "../inc/uchat.h"

static void file_pushback(t_msg **head, t_add_m *s, int sticer) {
    t_msg *tmp = NULL;
    GtkWidget *item[3];
    char *func[] = {"Save", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {save_file, forward_msg, delete_msg};

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
    for (int i = sticer - 1; i < 3; i++) {
        item[i] = gtk_menu_item_new_with_label(func[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

static void send_file_back(t_user *us, t_add_m *s, t_msg *t) {
    GtkWidget *wid;

    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(wid, 630, 30);
    MX_MSG_PACK(s->my, t->label, wid);
    MX_SET_NAME_MSG(s->my, t->label);
    gtk_grid_attach_next_to(GTK_GRID(us->text_grid), wid, NULL, GTK_POS_TOP, 1, 1);
    mx_idle_show(s->my, wid);
    
}

void add_file_back(t_user *us, t_add_m *s, int stic, int count) {
    t_msg *msg = NULL;
    char **p = mx_strsplit(s->text, '/');
    char *name = NULL;

    file_pushback(&us->msg, s, stic);
    for (t_msg *k = us->msg; k; k = k->next)
        if (k->next == NULL) {
            msg = k;
            k->user = us;
        }
    msg->id = s->id;
    msg->count = count;
    if (stic == 0) {
        file_check(s->text, &msg, name, s->my);
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
