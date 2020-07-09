#include "../inc/uchat.h"

void msg_file_pushfornt(t_msg **head, char *filename) {
    t_msg *tmp = NULL;
    GtkWidget *item[2];
    char *s[] = {"Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {forward_msg, delete_msg};

    tmp = create_msg(NULL, filename);
    tmp->prev = *head;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
    for (int i = 0; i < 2; i++) {
        item[i] = gtk_menu_item_new_with_label(s[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

void add_file(t_main *m, gchar *tmp) {
    t_user *us = NULL;
    t_msg *t = NULL;
    GtkWidget *wid;

    for (t_user *i = m->users; i; i = i->next) {
        if (i->check == true)
            us = i;
    }
    msg_file_pushfornt(&us->msg, (char *)tmp);
    t = us->msg->next;
    t->user = us;
    if (mx_strstr(tmp, ".png") || mx_strstr(tmp, ".jpg") || mx_strstr(tmp, ".jpeg")
        || mx_strstr(tmp, ".gif") || mx_strstr(tmp, ".svg")) {
            t->file = resize_image(tmp, 200, 200);
            gtk_button_set_image(GTK_BUTTON(t->label), t->file);
    }
    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(wid, 630, 30);
    gtk_box_pack_end(GTK_BOX(wid), t->label, FALSE, FALSE, 10);
    gtk_grid_attach(GTK_GRID(us->text_grid), wid, 0, t->count, 1, 1);
    gtk_widget_show_all(wid);
    us->row = t->count;
}
