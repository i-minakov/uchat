#include "../inc/uchat.h"

char *mx_path_down(t_main *m) {
    char *path = NULL;

    path = mx_strjoin("./source/cash_", m->my_name);
    path = mx_delit_fre(path, "/downloads/");
    return path;
}

static void hide_something(t_main *m) {
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    gtk_widget_hide(m->edit_entry);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
        gtk_widget_hide(i->text_grid);
    }
    the_ic(1, m);
    hide_menu(m);
    hide_set(m);

    gtk_widget_hide(m->micro_on);
    gtk_widget_hide(m->set->chan_name);
    gtk_widget_hide(m->set->chan_pas);
    gtk_widget_hide(m->grid_stic);
    gtk_widget_hide(m->stic_scrol);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->forw->fix_forw);
    gtk_widget_hide(m->search);
}

static void check_cmd(t_main *m) {
    if (m->cmd == SIG_UP) {
        m->my_name = mx_strdup(m->log_in->sig->signame);
        m->cmd = BLCK;
    }
    if (m->cmd == SIG_IN) 
        m->my_name = mx_strdup(m->log_in->log->logname);
        m->cmd = BLCK;
}

t_main *malloc_main() {
    t_main *m = (t_main *)malloc(sizeof(t_main));

	m->log_in = (t_wid *)malloc(sizeof(t_wid) * 10);
	m->log_in->sig = (t_sign *)malloc(sizeof(t_sign) * 16);
	m->log_in->log = (t_login *)malloc(sizeof(t_login) * 10);
	m->log_in->m = m;
	m->log_in->m->log_in = m->log_in;
	m->log_in->sig->sigfile = NULL;

    m->exit = 0;
    m->voice_msg = NULL;
    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->menu = (t_menu *)malloc(sizeof(t_menu) * 100);
    m->style = (t_style *)malloc(sizeof(t_style) * 100);
    m->set = (t_setting *)malloc(sizeof(t_setting) * 100);
    m->dots = (t_dots *)malloc(sizeof(t_dots) * 10);
    m->forw = (t_forw *)malloc(sizeof(t_forw) * 10);
    m->stic = (t_sticker *)malloc(sizeof (t_sticker *) * 100);
    m->emo = (t_emoji *)malloc(sizeof (t_emoji *) * 100);
    m->count_reqw = 0;
    m->count_reqw_edit = 0;
    m->srch= NULL;
    m->users = NULL;
    m->command = NULL;
    m->my_name = NULL;
    m->cap->m = m;
    return m;
}

int mx_chat_screen(t_main **gtk) {
    t_main *m = *gtk;
    int ex = 0;

    m->order = 0;
    check_cmd(m);
    // for (int i = 10; i > 0; i--) 
    //     user_pushback(&m->users, "yarik"); 
    init_components(m);
    init_signals(m);  
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    gtk_widget_destroy(m->log_in->fixed);
    gtk_widget_hide(m->log_in->window);
    gtk_widget_show_all(m->window);
    hide_something(m);
    m->cmd = DEF;
    change_lang(NULL, m);
    change_color(NULL, m);
    mx_del_strarr(&m->command);
    
    return ex;
}

