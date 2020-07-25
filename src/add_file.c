#include "../inc/uchat.h"

static void save_but(GtkWidget *widget, GdkEvent *event, t_msg *msg) {
    save_file(NULL, msg);
}

static void msg_file_pushfront(t_msg **head, t_add_m *s, int sticer) {
    t_msg *tmp = NULL;
    GtkWidget *item[3];
    char *func[] = {"Save", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {save_file, forward_msg, delete_msg};

    tmp = create_msg(NULL, s->text);
    tmp->my = s->my;
    tmp->prev = *head;
    tmp->next = (*head)->next; 
    tmp->stic = sticer;
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
    for (int i = sticer - 1; i < 3; i++) {
        item[i] = gtk_menu_item_new_with_label(func[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

void file_check(gchar *tmp, t_msg **msg, char *name, bool my) {
    t_msg *t = *msg;

    if (mx_strstr(tmp, ".jpg") || mx_strstr(tmp, ".jpeg")
        || mx_strstr(tmp, ".gif")) {
            if (mx_strstr(tmp, ".gif"))
                t->file = gtk_image_new_from_file(tmp);
            else 
                t->file = resize_image(tmp, 200, 200);
            gtk_button_set_image(GTK_BUTTON(t->label), t->file);
    }
    else {
        t->file = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        MX_BOX_START(t->file, gtk_image_new_from_file("./source/resource/load image.png"));
        gtk_box_pack_start(GTK_BOX(t->file), gtk_label_new(name), FALSE, FALSE, 10); 
        gtk_container_add(GTK_CONTAINER(t->label), t->file);
        MX_IDLE_SHOW(my, t->label);
    }
}

static void send_file(t_user *us, t_add_m *s, t_msg *t, int flag) {
    GtkWidget *wid;

    wid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 900);
    gtk_widget_set_size_request(wid, 630, 30);
    MX_MSG_PACK(s->my, t->label, wid);
    MX_SET_NAME_MSG(s->my, t->label);
    gtk_grid_attach(GTK_GRID(us->text_grid), wid, 0, t->count, 1, 1);
    MX_IDLE_SHOW(s->my, wid);   
    us->row++;
    if (s->my == true) 
        command_msg(us, s, flag);
}

void add_file(t_user *us, t_add_m *s, int stic, int id) {
    t_msg *t = NULL;
    char **p = mx_strsplit(s->text, '/');
    char *name = NULL;

    for (int i = 0; p[i]; i++)
        p[i + 1] == NULL ? name = p[i] : 0;
    msg_file_pushfront(&us->msg, s, stic + 1);
    t = us->msg->next;
    t->user = us;
    t->id = id;
    if (stic == 0) {
        file_check(s->text, &t, name, s->my);
        send_file(us, s, t, stic);
    }
    else {
        t->file = gtk_image_new_from_file(s->text);
        gtk_button_set_image(GTK_BUTTON(t->label), t->file);
        send_file(us, s, t, stic);
    }
    mx_del_strarr(&p);
    free(s);
}
