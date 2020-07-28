#include "../inc/uchat.h"

void change_notif(GtkToggleButton *togglebutton, t_main *m) {
    (void)togglebutton;
    if(m->set->notif_flag == 1)
        m->set->notif_flag = 0;
    else 
        m->set->notif_flag = 1;
}
