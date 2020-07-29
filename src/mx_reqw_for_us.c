#include "../inc/header.h"

/* reqw for user */
void mx_increase_msg_list(GtkScrolledWindow *scrol_bar, 
                        GtkPositionType pos, t_main *m) {
    if (pos == GTK_POS_BOTTOM)
        return;
    (void)scrol_bar;    
    t_user *us = mx_activ_us(m);
    char *new = NULL;

    new = mx_itoa(us->size_request);
    m->command = mx_arrjoin(m->command, "mx_update");
    m->command = mx_arrjoin(m->command, "size");
    us->size_request += 20;
    m->command = mx_arrjoin(m->command, new);
    mx_strdel(&new);
}

void mx_reqw_for_bl(GtkWidget *wid, t_main *m) {
    (void)wid;
    hide_menu(m);
    gtk_widget_destroy(m->cap->burger_but_img);
    m->cap->burger_but_img = gtk_image_new_from_file("./source/resource/cancel.png");
    gtk_fixed_put(GTK_FIXED(m->cap->fix_cap), m->cap->burger_but_img, 267, 42);
    gtk_widget_show(m->cap->burger_but_img);
    m->command = mx_arrjoin(m->command, "mx_send_list_back");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, "2");
    m->cmd = BLACK_LIST;
}

void clear_history(GtkWidget *wid, t_main *m) {
    t_user *us = NULL;

    (void)wid;
    for (t_user *i = m->users; i; i = i->next) 
        i->check == true ? us = i : 0;
    if (us == NULL)
        return ;
    gtk_widget_destroy(us->text_grid);
    free_msg(&us->msg);
    us->msg = create_msg(NULL, NULL);
    us->msg->count = -1;
    us->msg->id = 0;
    us->row = 0;
    us->text_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(us->text_grid), 20);
    gtk_fixed_put(GTK_FIXED(m->fix_for_text), us->text_grid, 0, 10);
    gtk_widget_show(us->text_grid);
    reset_l_mess(us);
    m->command = mx_arrjoin(m->command, "mx_del_history");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, us->name);
}  

void block_user(GtkWidget *wid, t_main *m) {
    (void)wid;
    m->command = mx_arrjoin(m->command, "mx_add_user_to_table");
    m->command = mx_arrjoin(m->command, m->my_name);
    m->command = mx_arrjoin(m->command, mx_activ_us(m)->name);
    m->command = mx_arrjoin(m->command, "2");
}

void mx_log_out(GtkWidget *w, t_main *m) {
    (void)w;
    m->command = mx_arrjoin(m->command, "mx_log_out");
    m->command = mx_arrjoin(m->command, "log_out");
    m->cmd = LOG_OUT;
}
