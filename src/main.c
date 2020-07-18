#include "../inc/uchat.h"

static void user_pushback(t_user **head) {
    t_user *tmp = *head;

    if (tmp == NULL) {
        *head = mx_create_user();
        (*head)->head = *head;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = mx_create_user();
    tmp->next->head = *head;
}

void set_chat_grid(t_main *m) {
    // int buf;
    // char *s = NULL;
    // int j = 0;

    for (t_user *i = m->users; i; i = i->next) {
        i->y_chat = 30;
        i->row = 0;
        i->text_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
        // int fd = open("../t.txt", O_RDWR);
        // while(read(fd, &buf, 1)) {
        //     s = mx_delit_fre(s, (char *)(&buf));
        //     if (buf == 10) {
        //         m->text = s;
        //         add_message(m, i, j%2 == 0 ? false : true, false);
        //         s = NULL;
        //         j++;
        //     }
        // }
        // close(fd);
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 10);
    }
}

static void set_cap(t_cap *c) {
    c->my_name = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_proportion("./src/resource/index.jpeg", 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./src/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./src/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", "Ilysha");

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

/////////////////////////////////////////////

void init_components(t_main *m) {
    init_main_stuff(m);
    set_users(m);
    set_chat_grid(m);
    set_cap(m->cap);
    init_menu(m);
    init_set(m);
    init_dot_forv(m);
}

/////////////////////////////////////////////

void hide_something(t_main *m) {
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
    //gtk_widget_hide(m->fix_for_stic);
    gtk_widget_hide(m->set->chan_name);
    gtk_widget_hide(m->set->chan_pas);
    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->forw->fix_forw);
    gtk_widget_hide(m->search);
}

t_main *malloc_main() {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 100);

    m->exit = 0;
    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->menu = (t_menu *)malloc(sizeof(t_menu) * 100);
    m->style = (t_style *)malloc(sizeof(t_style) * 100);
    m->set = (t_setting *)malloc(sizeof(t_setting) * 100);
    m->dots = (t_dots *)malloc(sizeof(t_dots) * 10);
    m->forw = (t_forw *)malloc(sizeof(t_forw) * 10);
    m->stic = (t_sticker *)malloc(sizeof (t_sticker *) * 100);
    m->users = NULL;
    return m;
}

void free_all(t_main *m) {
    free_users(&m->users);
    free(m->cap);
    free(m->menu);
    free(m->style);
    free(m->set);
    free(m->dots);
    free(m->forw);
    free(m);
}

int chat_screen() {
    t_main *m = malloc_main();
    int ex = 0;

    gtk_init(NULL, NULL);
    for (int i = 10; i > 0; i--)
        user_pushback(&m->users);
    init_components(m);
    connect_css(m, 1);
    init_signals(m);  
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    gtk_widget_show_all(m->window);
    hide_something(m);
    gtk_main(); 
    ex = m->exit;
    free_all(m);
    return ex;
}

int main(int argc, char *argv[]) {

    while (1) {
        // if (log_screen() == 1)
        //     break ;
        if (chat_screen() == 0)
            break;
    }
    // system("leaks -q uchat");
    return 0;
}
