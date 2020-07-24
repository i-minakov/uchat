#include "../inc/uchat.h"

void micro_click(GtkWidget *w, t_main *m) {
    if(m->micro_flag == 0) {
        m->micro_flag = 1;
        puts("++++\n");
        //запуск микро
    }
    else {
        m->micro_flag = 0;
        //остановка микро
    }
    MX_SHOW_HIDE(m->micro_flag, m->micro_on);
}
