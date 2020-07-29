#include "../inc/header.h"

void mx_check_sigup(t_main *m) {
    if (m->cmd == SRCH_MSG) {
        m->command = mx_arrjoin(m->command, "mx_mssg_search");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, mx_activ_us(m)->name);
        m->command = mx_arrjoin(m->command, m->search_str);
        m->cmd = SRCH_US;
    }
    if (m->cmd == CHECK_US) {
        m->my_name = mx_strdup(m->log_in->sig->signame);
        m->command = mx_arrjoin(m->command, "mx_add_new_user");
        m->command = mx_arrjoin(m->command, m->my_name);
        m->command = mx_arrjoin(m->command, m->log_in->sig->sigpas);
        m->command = mx_arrjoin(m->command, 
            m->log_in->sig->sigfile ? m->log_in->sig->sigfile : MX_DEF_PHOTO);
        m->cmd = BLCK;
    }
}

void mx_check_sigin(t_main *m) {
    if (m->cmd == CHECK_PASS) {
        m->command = mx_arrjoin(m->command, "mx_check_user_pass");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, m->log_in->log->logpas);
        m->cmd = BLCK;
    }
    else if (m->cmd == LANG) {
        gtk_widget_hide(m->log_in->window);
		gtk_widget_destroy(m->log_in->fixed);
        m->command = mx_arrjoin(m->command, "mx_get_type");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, "0");
        m->cmd = BLCK;
    }
    else if (m->cmd == THEME) {
        m->command = mx_arrjoin(m->command, "mx_get_type");
        m->command = mx_arrjoin(m->command, m->log_in->log->logname);
        m->command = mx_arrjoin(m->command, "1");
        m->cmd = BLCK;
    }
    mx_check_sigup(m);
}
