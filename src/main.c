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

    for (t_user *i = m->users; i; i = i->next) {
        i->y_chat = 30;
        i->row = 0;
        i->text_grid = gtk_grid_new();
        gtk_grid_set_row_spacing(GTK_GRID(i->text_grid), 20);
        //////////////////
        // read from DB //
        //////////////////
        gtk_fixed_put(GTK_FIXED(m->fix_for_text), i->text_grid, 0, 0);
    }
}

static void set_cap(t_cap *c) {
    c->my_name = gtk_label_new(NULL);
    c->friend_name = gtk_label_new(NULL);
    c->my_photo = resize_image("./src/resource/index.jpeg", 51, 51);
    c->frame_for_my_photo = gtk_image_new_from_file("./src/resource/my photo.png");
    c->burger_but_img = gtk_image_new_from_file("./src/resource/burger.png");
    c->dot_menu = gtk_image_new_from_file("./src/resource/dots.png");
    char *markup = g_markup_printf_escaped("<span color=\"white\" font=\"14\">\%s</span>", "Ilysha");

    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_photo, 23, 20);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->frame_for_my_photo, 23, 20);
    gtk_label_set_markup(GTK_LABEL(c->my_name), markup); 
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->dot_menu, 941, 32);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->my_name, 83, 38);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->friend_name, 353, 42);
    gtk_fixed_put(GTK_FIXED(c->fix_cap), c->burger_but_img, 267, 42);
    gtk_widget_show_all(c->fix_cap);
    g_free(markup);
}

/////////////////////////////////////////////


void init_menu(t_main *m) {
    m->style->color = 1;
    m->style->lang = 1;
    m->menu->menu_box = GTK_WIDGET(gtk_builder_get_object(m->builder, "menu_img"));
    m->menu->menu_fix = GTK_WIDGET(gtk_builder_get_object(m->builder, "menu_box"));
    m->menu->search = GTK_WIDGET(gtk_builder_get_object(m->builder, "search"));
    m->menu->settings = GTK_WIDGET(gtk_builder_get_object(m->builder, "setting"));
    m->menu->contacts = GTK_WIDGET(gtk_builder_get_object(m->builder, "contacts"));
    m->menu->exit = GTK_WIDGET(gtk_builder_get_object(m->builder, "exit"));
    m->menu->flag = 0;
    m->set->sett_box = GTK_WIDGET(gtk_builder_get_object(m->builder, "set_img"));
    m->set->sett_fix = GTK_WIDGET(gtk_builder_get_object(m->builder, "setting_bar"));
    m->set->color_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "Colorlab"));
    m->set->lang_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "Langlab"));
    m->set->lang1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "Lang1"));
    m->set->lang2 = GTK_WIDGET(gtk_builder_get_object(m->builder, "Lang2"));
    m->set->color1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "color1"));
    m->set->color2 = GTK_WIDGET(gtk_builder_get_object(m->builder, "color2"));
    m->set->my_name = GTK_WIDGET(gtk_builder_get_object(m->builder, "my_name"));
    m->set->set_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "set_but"));
    m->set->my_photo = resize_proportion("./src/resource/index.jpeg", 80, 80);
    m->set->my_frame2 = resize_proportion("./src/resource/slept photo2.png", 80, 80);
    m->set->my_frame = resize_proportion("./src/resource/slept photo.png", 80, 80);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_photo, 30, 30);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_frame2, 30, 30);
    gtk_fixed_put(GTK_FIXED(m->set->sett_fix), m->set->my_frame, 30, 30);
    m->set->flag = 0;
}

void init_components(t_main *m) {
    m->builder = gtk_builder_new_from_file("./src/resource/test.glade");
    m->window = GTK_WIDGET(gtk_builder_get_object(m->builder, "window1"));
    g_signal_connect(m->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(m->builder, m->builder);
    m->bottom_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "bottom_b"));
    m->top_b = GTK_WIDGET(gtk_builder_get_object(m->builder, "top_b"));
    m->fix_for_text = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_text"));
    m->fix_for_users = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_user"));
    m->cap->fix_cap = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_cap"));
    m->fix1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix"));
    m->sms = GTK_WIDGET(gtk_builder_get_object(m->builder, "sms"));
    m->but1 = GTK_WIDGET(gtk_builder_get_object(m->builder, "but1"));
    m->lab_start = GTK_WIDGET(gtk_builder_get_object(m->builder, "lab_start"));
    m->cap->burger_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "burger_but"));
    m->cap->dot_menu_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
    m->scrol_bar = GTK_WIDGET(gtk_builder_get_object(m->builder, "scrol_text"));
    m->edit_entry = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_edit"));
    m->search = GTK_WIDGET(gtk_builder_get_object(m->builder, "entry_search"));
    m->adj = gtk_adjustment_new(1.0, 1.0, 10.0, 1.0, 10.0, 1.0);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(m->scrol_bar), m->adj);
    m->style->color = 1;
    m->style->lang = 1;
    init_menu(m);

    m->dots->dot_img = GTK_WIDGET(gtk_builder_get_object(m->builder, "dot_img1"));
    m->dots->dot_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "dots_but"));
    m->dots->fix_dot_menu = GTK_WIDGET(gtk_builder_get_object(m->builder, "dot_menu"));
    m->dots->block_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "block_but"));
    m->dots->clear_msg_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "clear_but"));
    m->dots->search_msg_but = GTK_WIDGET(gtk_builder_get_object(m->builder, "search_but"));
    m->dots->visible = 1;
    m->dots->m = m;

    m->forw->fix_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_forw"));
    m->forw->search_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "search_forw"));
    m->forw->fox_for_forw = GTK_WIDGET(gtk_builder_get_object(m->builder, "fix_for_forw"));
    m->forw->but_cancel = GTK_WIDGET(gtk_builder_get_object(m->builder, "cancel_forw"));
    m->forw->m = m;

}

/////////////////////////////////////////////

void hide_something(t_main *m) {
    gtk_widget_hide(m->sms);
    gtk_widget_hide(m->but1);
    gtk_widget_hide(m->edit_entry);
    for (t_user *i = m->users; i; i = i->next) {
        gtk_widget_hide(i->frame_photo_act);
        gtk_widget_hide(i->backg_us_activ);
    }
    hide_menu(m);
    hide_set(m);

    gtk_widget_hide(m->dots->fix_dot_menu);
    gtk_widget_hide(m->forw->fix_forw);
    gtk_widget_hide(m->search);
}

t_main *malloc_main() {
    t_main *m = (t_main *)malloc(sizeof(t_main) * 100);

    m->cap = (t_cap *)malloc(sizeof(t_cap) * 100);
    m->menu = (t_menu *)malloc(sizeof(t_menu) * 100);
    m->style = (t_style *)malloc(sizeof(t_style) * 100);
    m->set = (t_setting *)malloc(sizeof(t_setting) * 100);
    m->dots = (t_dots *)malloc(sizeof(t_dots) * 10);
    m->forw = (t_forw *)malloc(sizeof(t_forw) * 10);
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

// void loop(t_main *m) {  

//     while (1) {

//         init_components(m);
//         connect_css(m, 1);
//         set_users(m);
//         set_chat_grid(m);
//         set_cap(m->cap);
//         init_signals(m);  
//         log_screen();
//         gtk_label_set_text(GTK_LABEL(m->lab_start),
//                         "Please select a chat to start messaging");
//         gtk_widget_show_all(m->window);
//         hide_something(m);
//         gtk_main(); 
//     }
// }

int main(int argc, char *argv[]) {
    t_main *m = malloc_main();

    gtk_init(&argc, &argv);
    for (int i = atoi(argv[1]); i > 0; i--)
        user_pushback(&m->users);

    init_components(m);
    connect_css(m, 1);
    set_users(m);
    set_chat_grid(m);
    set_cap(m->cap);
    init_signals(m);  
    log_screen();
    gtk_label_set_text(GTK_LABEL(m->lab_start),
                     "Please select a chat to start messaging");
    gtk_widget_show_all(m->window);
    hide_something(m);\
    gtk_main(); 

    free_all(m);
    return 0;
}
