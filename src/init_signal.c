#include "../inc/uchat.h"

/* init signal */
static void entry_activate(GtkEntry *e, t_main *m) {
    (void)e;
    send_but(m->but1, m);
}

static void set_dots_signal(t_dots *d) {
    g_signal_connect(d->dot_but, "clicked", G_CALLBACK(show_hide_dots_menu), d);
    g_signal_connect(d->clear_msg_but, "clicked", G_CALLBACK(clear_history), d->m);
    g_signal_connect(d->block_but, "clicked", G_CALLBACK(block_user), d->m);
}

static void init_signals_sec(t_main *m) {
    g_signal_connect(m->menu->exit, "clicked", G_CALLBACK(mx_log_out), m);
    g_signal_connect(m->menu->search, "clicked", G_CALLBACK(show_search_contacts), m);
    g_signal_connect(m->menu->contacts, "clicked", G_CALLBACK(show_search_users), m);
    g_signal_connect(m->set->my_name, "clicked", G_CALLBACK(enter_name), m);
    g_signal_connect(m->set->chan_name, "icon-press", G_CALLBACK(backto_name), m);
    g_signal_connect(m->set->chan_name, "activate", G_CALLBACK(change_name), m);
    g_signal_connect(m->set->my_pas, "clicked", G_CALLBACK(enter_pas), m);
    g_signal_connect(m->set->chan_pas, "icon-press", G_CALLBACK(backto_pas), m);
    g_signal_connect(m->set->chan_pas, "activate", G_CALLBACK(change_pas), m);
    g_signal_connect(m->set->chan_ph, "clicked", G_CALLBACK(mx_change_my_photo), m);
    g_signal_connect(m->micro_on_but, "clicked", G_CALLBACK(micro_start), m);
    set_dots_signal(m->dots);
}

void init_signals(t_main *m) {
    g_signal_connect(m->cap->burger_but, "enter-notify-event", G_CALLBACK(burger_notify), m);
    g_signal_connect(m->cap->burger_but, "clicked", G_CALLBACK(switch_menu), m);
    g_signal_connect(m->cap->burger_but, "leave-notify-event", G_CALLBACK(burger_leave), m);
    g_signal_connect(m->but1, "clicked", G_CALLBACK(send_but), m);
    g_signal_connect(m->sms, "activate", G_CALLBACK(entry_activate), m);
    g_signal_connect(m->sms, "icon-press", G_CALLBACK(attach_file), m);
    g_signal_connect(m->edit_entry, "icon-press", G_CALLBACK(attach_file), m);
    g_signal_connect(m->dots->search_msg_but, "clicked", G_CALLBACK(show_search_msg), m);
    g_signal_connect(m->scrol_bar, "edge-overshot", G_CALLBACK(mx_increase_msg_list), m);
    g_signal_connect(m->search, "activate", G_CALLBACK(search_activ), m);
    g_signal_connect(m->search, "icon-press", G_CALLBACK(close_search), m);
    g_signal_connect(m->menu->black_list, "clicked", G_CALLBACK(mx_reqw_for_bl), m);
    g_signal_connect(m->menu->settings, "clicked", G_CALLBACK(show_setings), m);
    g_signal_connect(m->set->set_but, "clicked", G_CALLBACK(hide_setings), m);
    g_signal_connect(m->set->color1, "toggled", G_CALLBACK(change_color), m);
    g_signal_connect(m->set->lang1, "toggled", G_CALLBACK(change_lang), m);
    g_signal_connect(m->set->notif1, "toggled", G_CALLBACK(change_notif), m);
    init_signals_sec(m);
}
