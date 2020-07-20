#include "../inc/uchat.h"

void save_file(GtkMenuItem *item, t_msg *msg) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;
    gchar *tmp = NULL;

    dialog = gtk_file_chooser_dialog_new ("Save File", GTK_WINDOW(msg->user->m->window), action, ("_Cancel"), 
                        GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        tmp = gtk_file_chooser_get_filename (chooser);
        g_free(tmp);
    }
    gtk_widget_destroy(dialog);
}

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

void popup_menu(GtkButton *widget, GdkEventButton  *event, t_msg *msg) {
    if (event->button != 1) {
        gtk_menu_popup_at_widget(GTK_MENU(msg->menu), (msg->label), GDK_GRAVITY_SOUTH_WEST, 
            GDK_GRAVITY_SOUTH_EAST, (GdkEvent *)event);
    }
    else if (msg->filename != NULL && msg->stic != 2)
        save_file(NULL, msg);
}

t_msg *create_msg(char *text, char *filename) {
    t_msg *new = (t_msg *)malloc(sizeof(t_msg) * 10);

    new->next = NULL;
    new->prev = NULL;
    new->count = 0;
    new->stic = 0;
    new->user = NULL;
    new->filename = filename;
    new->text = NULL;
    new->my = true;
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

void msg_pushfront(t_msg **head, char *text, bool my, int forw) {
    t_msg *tmp = NULL;
    GtkWidget *item[4];
    int i = 0;
    char *s[] = {"Edit", "Reply", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {edit_msg, reply_msg, forward_msg, delete_msg};

    tmp = create_msg(text, NULL);
    tmp->my = my;
    tmp->forward = forw;
    MX_SET_NAME_MSG(my, tmp->label);
    tmp->prev = *head;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
    if (tmp->next != NULL) {
        tmp->next->prev = tmp;
        tmp->count = tmp->next->count + 1;
    }
    for (my == false || forw == 1 ? i = 1 : 0; i < 4; i++) {
        item[i] = gtk_menu_item_new_with_label(s[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), tmp);
        gtk_menu_shell_append(GTK_MENU_SHELL(tmp->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

