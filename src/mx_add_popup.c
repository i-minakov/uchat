#include "../inc/header.h"

static void popup_menu(GtkButton *widget, GdkEventButton  *event,
                         t_msg *msg) {
    (void)widget;
    if (event->button != 1) {
        gtk_menu_popup_at_widget(GTK_MENU(msg->menu), (msg->label), GDK_GRAVITY_SOUTH_WEST, 
            GDK_GRAVITY_SOUTH_EAST, (GdkEvent *)event);
    }
    else if (msg->filename != NULL && msg->stic != 2)
        save_file(NULL, msg);
}

void mx_add_popup_menu(int flag, t_msg *msg) { 
    char *s[] = {"Edit", "Reply", "Save", "Forward", "Delete", NULL};
    void (*menu_option[])(GtkMenuItem *item, t_msg *msg) = 
        {edit_msg, reply_msg, save_file, forward_msg, delete_msg};
    GtkWidget *item[5];
    int i = 0;

    msg->menu = gtk_menu_new();
    gtk_widget_set_name(msg->menu, "rbut");
    g_signal_connect(msg->label, "button_press_event", G_CALLBACK(popup_menu), msg);
    if (flag == 0 && (msg->my == false || msg->forward == 1))
        i = 1;
    flag == 1 ? i = 2 : 0;
    flag == 2 ? i = 3 : 0;
    for ( ; i < 5; i++) {
        flag == 0 && i == 2 ? i++ : 0; 
        item[i] = gtk_menu_item_new_with_label(s[i]);
        g_signal_connect(item[i], "activate", G_CALLBACK(menu_option[i]), msg);
        gtk_menu_shell_append(GTK_MENU_SHELL(msg->menu), item[i]);
        gtk_widget_show(item[i]);
    }
}

