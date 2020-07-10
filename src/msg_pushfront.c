#include "../inc/uchat.h"

void delete_msg(GtkMenuItem *item, t_msg *msg) {
    t_msg *t = NULL;

    gtk_grid_remove_row(GTK_GRID(msg->user->text_grid), msg->count);
    for (t_msg *i = msg->prev; i->count != -1; i = i->prev)
        i->count--;
    t = msg->next;
    t != NULL ? t->prev = msg->prev : 0;
    msg->prev->next = t;
    reset_l_mess(msg->user);
    msg->user->row--;
    free(msg);
    msg = NULL;
}

void edit_done(GtkEntry *e, t_msg *msg) {
    char *str = mx_strnew(mx_strlen(msg->text) + ((mx_strlen(msg->text)/50) + 1));
    int k = 0;

    mx_strdel(&msg->text);
    msg->text = mx_strdup((char *)gtk_entry_get_text
        (GTK_ENTRY(msg->user->m->edit_entry)));
    for (int j = 0; msg->text[j]; j++) {
        str[k++] = msg->text[j];
        (j%50 == 0 && j != 0) ? str[k++] = '\n' : 0;
    }
    gtk_button_set_label(GTK_BUTTON(msg->label), str);
    gtk_widget_hide(msg->user->m->edit_entry);
    gtk_widget_show(msg->user->m->sms);
    free(str);
}

void edit_msg(GtkMenuItem *item, t_msg *msg) {
    // GtkWidget *lab = gtk_label_new(NULL);
    // char *markup = g_markup_printf_escaped(
    //         "<span color=\"white\" font=\"10\"> Editing: %s</span>", msg->text);

    // gtk_label_set_markup(GTK_LABEL(lab), markup); 
    // gtk_fixed_put(GTK_FIXED(msg->user->m->fix1), lab, 364, 636);
    // gtk_widget_show(lab);
    // g_free(markup);
    gtk_widget_hide(msg->user->m->sms);
    gtk_widget_show(msg->user->m->edit_entry);
    gtk_entry_set_text(GTK_ENTRY(msg->user->m->edit_entry), msg->text);
    g_signal_connect(msg->user->m->edit_entry, "activate", G_CALLBACK(edit_done), msg);
}

void forward_msg(GtkMenuItem *item, t_msg *msg) {

}

static void popup_menu(GtkButton *widget, GdkEventButton  *event, t_msg *msg) {
    if (event->button != 1) {
        gtk_menu_popup_at_widget(GTK_MENU(msg->menu), (msg->label), GDK_GRAVITY_SOUTH_WEST, 
            GDK_GRAVITY_SOUTH_EAST, (GdkEvent *)event);
    }
}

t_msg *create_msg(char *text, char *filename) {
    t_msg *new = (t_msg *)malloc(sizeof(t_msg) * 10);

    new->next = NULL;
    new->prev = NULL;
    new->count = 0;
    new->user = NULL;
    new->filename = filename;
    new->text = NULL;
    if (!text && !filename)
        return new;
    new->label = gtk_button_new();
    gtk_widget_set_size_request(new->label, 100, 30);
    if (text) {
        new->text = mx_strdup(text);
        gtk_button_set_label(GTK_BUTTON(new->label), new->text);
    }
    new->menu = gtk_menu_new();
    g_signal_connect(new->label, "button_press_event", G_CALLBACK(popup_menu), new);
    return new;
}

void msg_pushfront(t_msg **head, char *text) {
    t_msg *tmp = NULL;
    GtkWidget *item[3];
    char *s[] = {"Edit", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {edit_msg, forward_msg, delete_msg};

    tmp = create_msg(text, NULL);
    tmp->prev = *head;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
    for (int i = 0; i < 3; i++) {
        item[i] = gtk_menu_item_new_with_label(s[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}
