#include "../inc/header.h"

int main(int argc, char *argv[]) {
    if (!strcmp(argv[1], "server"))
        return mx_server(argc, argv);
    else if (!strcmp(argv[1], "client"))
        return mx_client(argc, argv);
    else if (!strcmp(argv[1], "chat"))
        return interface();
    return 0;
}

/*void *mx_first(void *old) {
    t_server *server = (t_server *)old;

    printf("%s\n", server->json);
    server->json = mx_strdup("lol");
    printf("%s\n", server->json);
    return NULL;
}

void *mx_second(void *old) {
    t_server *server = (t_server *)old;

    printf("%s\n", server->json);
    server->json = mx_strdup("zoom");
    printf("%s\n", server->json);
    return NULL;
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

    pthread_create(&first, NULL, mx_first, (void *)&str);
    pthread_join(first, NULL);

    pthread_create(&second, NULL, mx_second, (void *)&str);
    pthread_join(second, NULL);
    return 0;
}*/

/*int main() {
    char *json = NULL;
    char *command = mx_strdup("mx_update");
    char **argv = (char **)malloc(sizeof(char *) * 4);

    argv[0] = mx_strdup("command1");
    argv[1] = mx_strdup("command2");
    argv[2] = mx_strdup("command3");
    argv[3] = NULL;
    json = mx_request(command, argv);
    printf("%s\n\n", json);
    
    char *get_value_command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    printf("%s\n", get_value_command);
    for (int i = 0; arr[i]; i++)
        printf("%s\n", arr[i]);
    system("leaks -q uchat");
    return 0;
}*/

/*int main(int argc, char *argv[]) {
    if (argc != 2)
        return 1;
    FILE *img = fopen(argv[1], "rb");
    char ch[4];
    int nb = fread(ch, 4, 1, img);
    while (nb != 0) {
        printf("%s\n", ch);
        nb = fread(ch, 4, 1, img);
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

int main(int argc, char *argv[]) {
    if (!strcmp(argv[1], "server"))
        return mx_server(argc, argv);
    else if (!strcmp(argv[1], "client"))
        return mx_client(argc, argv);
    return 0;
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
    int result = 0;

    if (argc == 2 && mx_strcmp(argv[1], "1") == 0)
        result = mx_create_table_users();
    else if (argc == 5 && mx_strcmp(argv[1], "2") == 0)
        result = mx_add_new_user(argv[2], argv[3], argv[4]);
    else if (argc == 5 && mx_strcmp(argv[1], "3") == 0)
        result = mx_add_user_to_table(argv[2], argv[3], mx_atoi(argv[4]));
    else if (argc == 3 && mx_strcmp(argv[1], "4") == 0)
        result = mx_delete_user(argv[2]);
    else if (argc == 4 && mx_strcmp(argv[1], "5") == 0)
        result = mx_change_log(argv[2], argv[3]);
    else if (argc == 4 && mx_strcmp(argv[1], "6") == 0)
        result = mx_change_pass(argv[2], argv[3]);
    else if (argc == 4 && mx_strcmp(argv[1], "7") == 0) {
        t_list *list = mx_send_list_back(argv[2], mx_atoi(argv[3]));

        for (t_list *node = list; node; node = node->next) {
            printf("%s\t%s\t", ((t_table_list *)node->data)->name, ((t_table_list *)node->data)->path_img);
            printf("%s\t", ((t_table_list *)node->data)->last_mssg ? ((t_table_list *)node->data)->last_mssg : "NULL");
            printf("%s\n", ((t_table_list *)node->data)->last_mssg_time ? ((t_table_list *)node->data)->last_mssg_time : "NULL");
        }
    }
    else if (argc == 4 && mx_strcmp(argv[1], "8") == 0)
        result = mx_change_img(argv[2], argv[3]);
    else if (argc == 8 && mx_strcmp(argv[1], "9") == 0) {
        t_input data;
        data.name_from = mx_strdup(argv[2]);
        data.name_to = mx_strdup(argv[3]);
        data.message = mx_strdup(argv[4]);
        data.flag = mx_atoi(argv[5]);
        data.reply = mx_strdup(argv[6]);
        data.forward = mx_strdup(argv[7]);
        if (mx_atoi(argv[5]) == 1)
            data.file_name = mx_strdup(argv[4]);
        else
            data.file_name = mx_strdup("NULL");

        result = mx_recv_new_mess(&data);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "10") == 0) {
        t_list *list = mx_history_back(argv[2], argv[3], argv[4]);

        mx_print_list(list, argv[2], argv[3]);
    }
    else if (argc == 4 && mx_strcmp(argv[1], "11") == 0)
        result = mx_del_history(argv[2], argv[3]);
    else if (argc == 5 && mx_strcmp(argv[1], "12") == 0)
        result = mx_del_message(argv[2], argv[3], argv[4]);
    else if (argc == 6 && mx_strcmp(argv[1], "13") == 0)
        result = mx_edit(argv[2], argv[3], argv[4], argv[5]);
    else if (argc == 4 && mx_strcmp(argv[1], "14") == 0)
        mx_check_user_pass(argv[2], argv[3]) ? printf("ok :)\n") : printf("not ok T_T\n");
    else if (argc == 4 && mx_strcmp(argv[1], "15") == 0)
        printf("%s\n", mx_hash(argv[1], argv[2]));
    else if (argc == 4 && mx_strcmp(argv[1], "16") == 0) {
        t_list *list = mx_user_search(argv[2], argv[3]);

        for (t_list *node = list; node; node = node->next) {
            printf("%s\t", ((t_table_list *)node->data)->name);
            printf("%s\n", ((t_table_list *)node->data)->path_img);
        }
    }
    else if (argc == 6 && mx_strcmp(argv[1], "17") == 0) {
        t_list *list = mx_mssg_search(argv[2], argv[3], argv[4], argv[5]);

        mx_print_list(list, argv[2], argv[3]);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "18") == 0)
        result += mx_set_type(argv[2], argv[3], mx_atoi(argv[4]));
    else if (argc == 4 && mx_strcmp(argv[1], "19") == 0)
        printf("%d\n", mx_get_type(argv[2], mx_atoi(argv[3])));
    else if (argc == 5 && mx_strcmp(argv[1], "20") == 0) {
        char *img_name = NULL;
        char *path = mx_get_img_path(argv[2], argv[3], mx_atoi(argv[4]), &img_name);

        printf("%s\t%s\n", path, img_name);
    }
    else if (argc == 5 && mx_strcmp(argv[1], "21") == 0)
        result += mx_del_user_from_table(argv[2], argv[3], mx_atoi(argv[4]));
    // system("leaks -q uchat");
    return result;
}*/
