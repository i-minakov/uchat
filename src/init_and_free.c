#include "../inc/header.h"

/* init component */
void set_chat_grid(t_main *m, int flag) {
    if (flag == 0) {
        for (t_user *i = m->users; i; i = i->next) {
            i->row = 0;
            i->text_grid = gtk_grid_new();
            gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
            gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 10);
        }   
    }
    else {
        m->users->row = 0;
        m->users->text_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(m->users->text_grid), 20);
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), m->users->text_grid, 0, 10);
    }
}

static void set_cap(t_cap *c) {
    c->my_name = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_proportion(mx_cooljoin(mx_delit_fre 
        (mx_strjoin("./source/cash_", c->m->my_name), "/"),  
            mx_strjoin(c->m->my_name, ".jpg")), 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./source/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./source/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./source/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">%s</span>", c->m->my_name);

    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_photo, 23, 20);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->frame_for_my_photo, 23, 20);
    gtk_label_set_markup(GTK_LABEL(c->my_name), markup); 
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->dot_menu, 941, 32);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_name, 83, 38);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->friend_name, 353, 37);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->burger_but_img, 267, 42);
    gtk_widget_show_all(c->fix_cap);
    g_free(markup);
}

void init_components(t_main *m) {
    init_main_stuff(m);
    set_users(m);
    set_chat_grid(m, 0);
    set_cap(m->cap);
    init_menu(m);
    init_set(m);
    init_dot_forv(m);

}

void free_start(t_main *m) {
	free(m->log_in->sig);
	free(m->log_in->log);
    free(m->log_in->eye);
    free(m->log_in);
}

void free_all(t_main *m) {
    free_users(&m->users);
    free(m->cap);
    free(m->menu);
    free(m->style);
    free(m->set);
    free(m->dots);
    free(m->forw);
    stic_free(m);
    free(m->stic);
    free(m->emo);
    free_start(m);
    free(m);
    m = NULL;
}
