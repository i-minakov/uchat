#include "../inc/uchat.h"

static void other_users(t_user *users) {
    for (t_user *i = users->head; i; i = i->next) {
        if (i->check == true) {
            gtk_widget_hide(i->backg_us_activ);
            gtk_widget_hide(i->frame_photo_act);
            gtk_widget_hide(i->text_grid);
            gtk_widget_show(i->backg_us_slept);
            gtk_widget_show(i->frame_photo_slept);
        }
        i->check = false;
    }
    users->check = true;
    mx_del_strarr(&users->m->command);
    users->m->cmd = UPDATE_SIZE;
    if (gtk_widget_is_visible(users->newmsg) == true)
        gtk_widget_hide(users->newmsg);
    if (gtk_widget_is_visible(users->m->micro_on_but) == false) {
        gtk_widget_show(users->m->micro_of);
        gtk_widget_show(users->m->micro_on_but);
    }
    
}

void user_click(GtkWidget *wid, t_user *users) {
    char *markup = g_markup_printf_escaped
            ("<span color=\"white\" font=\"14\">%s</span>",
                 gtk_label_get_text(GTK_LABEL(users->l_name)));

    (void)wid;
    gtk_widget_hide(users->m->lab_start);
    gtk_widget_show(users->m->sms);
    other_users(users);
    gtk_widget_hide(users->backg_us_slept);
    gtk_widget_show(users->backg_us_activ);
    gtk_widget_hide(users->frame_photo_slept);
    gtk_widget_show(users->frame_photo_act);
    gtk_widget_show(users->text_grid);
    gtk_label_set_markup(GTK_LABEL(users->m->cap->friend_name), markup);
    gtk_widget_show(users->m->cap->friend_name);
    MX_SCROL_END(users->m);
    g_free(markup);
    users->m->command = mx_arrjoin(users->m->command, "mx_update");
    users->m->command = mx_arrjoin(users->m->command, "chat");
    users->m->command = mx_arrjoin(users->m->command, users->name);
}
