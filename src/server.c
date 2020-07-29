#include "../inc/header.h"

/* callbacks */
static void mx_rep_for_mssg(char ***arr, t_list *node, int flag) {
    *arr = mx_arrjoin(*arr, (((t_history *)node->data)->r_f_mssg
                        ? ((t_history *)node->data)->r_f_mssg : "NULL"));
    *arr = mx_arrjoin(*arr, (((t_history *)node->data)->r_f_time
                        ? ((t_history *)node->data)->r_f_time : "NULL"));
    if (flag == 1)
        *arr = mx_arrjoin(*arr, (((t_history *)node->data)->forward
                            ? ((t_history *)node->data)->forward : "NULL"));
}
static void mx_send_history_line_adt(t_list *node, char *from, char *to, char ***arr) {
    if (mx_strcmp(((t_history *)node->data)->mssg_id, "NULL") != 0
        && mx_strcmp(((t_history *)node->data)->forward, "NULL") == 0) {
        mx_reply_forward(from, to, ((t_history *)node->data)->mssg_id, &node);
        mx_rep_for_mssg(arr, node, 0);
    }
    else if (mx_strcmp(((t_history *)node->data)->forward, "NULL") != 0) {
        mx_reply_forward(from, ((t_history *)node->data)->forward,
                            ((t_history *)node->data)->mssg_id, &node);
        mx_rep_for_mssg(arr, node, 1);
    }
}
static void mx_send_history_line(t_list **list, char *from, char *to, SSL *ssl) {
    char *command = NULL;
    char **arr = NULL;
    char *json;

    for (t_list *node = *list; node; node = node->next) {
        command = mx_itoa(((t_history *)node->data)->id);
        if (mx_strcmp(((t_history *)node->data)->flag, "1") == 0)
            arr = mx_arrjoin(arr, ((t_history *)node->data)->file_name);
        else
            arr = mx_arrjoin(arr, ((t_history *)node->data)->message);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->time);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->name);
        arr = mx_arrjoin(arr, ((t_history *)node->data)->flag);
        mx_send_history_line_adt(node, from, to, &arr);
        json = mx_request(command, arr);
        mx_bites_str(ssl, json, 'H');
        mx_strdel(&json);
        mx_strdel(&command);
        mx_del_strarr(&arr);
    }
}
void mx_send_history_list(t_node **node, char *name, char *json) {
    t_list *list = NULL;
    char *size = NULL;
    char **arr = NULL;

    if (mx_strcmp(name, (*node)->chat) == 0)
        size = mx_strdup((*node)->size);
    else
        size = mx_strdup("1");
    if (mx_strcmp((*node)->history, "normal") != 0
        && mx_strcmp(name, (*node)->chat) == 0) {
        arr = mx_get_arr(json);
        list = mx_mssg_search((*node)->user, (*node)->chat, arr[2], size);
        mx_replace(&(*node)->history, "normal");
        mx_del_strarr(&arr);
    }
    else
        list = mx_history_back((*node)->user, name, size);
    mx_send_history_line(&list, (*node)->user, (*node)->chat, (*node)->ssl);
    mx_strdel(&size);
    mx_del_list(&list, 1);
}
void mx_send_answer_type(t_node **node, int type, int flag) {
    char *type_str = NULL;
    char send[SIZE_SEND];

    mx_memset(send, '\0', SIZE_SEND);
    send[0] = 'T';
    type_str = mx_itoa(type);
    if (flag == 0)
        send[1] = 'L';
    if (flag == 1)
        send[1] = 'T';
    mx_mom(send, type_str, mx_strlen(type_str), 0);
    if (SSL_write((*node)->ssl, send, SIZE_SEND) == -1)
        return ;
    mx_strdel(&type_str);
}
static void mx_send_size_list(t_node **node, t_list *list) {
    t_list *i = list;
    int j = 0;
    char *str = NULL;

    for (; i; i = i->next)
        j++;
    str = mx_itoa(j);
    mx_bites_str((*node)->ssl, str, 'S');
    mx_strdel(&str);
}
static int mx_send_user_f_s(char *img_path, FILE *file, t_node **node) {
    char *len = NULL;
    char **slesh = mx_strsplit(img_path, '/');

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_file_format(slesh, (*node)->ssl, 'I', 'N');
    mx_file_size_close((*node)->ssl, len, 'I', 'S');
    mx_strdel(&len);
    mx_del_strarr(&slesh);
    return 0;
}
void mx_send_user_file(char *img_path, t_node **node) {
    FILE *file = NULL;

    file = fopen(img_path, "rb");
    if (file) {
        if (mx_send_user_f_s(img_path, file, node) != 1) {
            mx_file_bites(file, (*node)->ssl, 'I', 'B');
            mx_file_size_close((*node)->ssl, "close", 'I', 'C');
        }
        fclose(file);
    }
}
void mx_send_answer_list(t_node **node, t_list *list, int hist_flag, char *json) {
    t_list *i = list;
    t_table_list *data = NULL;
    char *cmd = mx_get_value(json, "command");

    mx_bites_str((*node)->ssl, cmd, 'C');
    mx_send_size_list(node, list);
    for (; i; i = i->next) {
        data = (t_table_list *)i->data;
        mx_bites_str((*node)->ssl, data->name, 'N');
        if ((*node)->flag == 0 && mx_strcmp(cmd, "mx_regular_request") == 0)
            mx_send_user_file(data->path_img, node);
        else if ((*node)->flag >= (FLAG * mx_list_size(list)))
            (*node)->flag = 0;
        if (hist_flag == 1)
            mx_send_history_list(node, data->name, json);
        data = NULL;
    }
    mx_bites_str((*node)->ssl, "end", 'E');
    mx_strdel(&cmd);
}

/* not mutex */
void mx_send_your_photo(t_node **node) {
    char *img = mx_super_join("./source/cash/", (*node)->user, 0);

    img = mx_super_join(img, ".jpg", 1);
    mx_bites_str((*node)->ssl, "mx_your_photo", 'C');
    mx_strdel(&img);
    img = mx_super_join("./database/", (*node)->user, 0);
    img = mx_super_join(img, "/", 1);
    img = mx_super_join(img, (*node)->user, 1);
    img = mx_super_join(img, ".jpg", 1);
    mx_send_user_file(img, node);
    mx_strdel(&img);
}
static void mx_check_user_pass_adt(char **arr, t_node **node) {
    if (mx_check_user_pass(arr[0], arr[1])) {
        mx_send_your_photo(node);
        mx_bites_str((*node)->ssl, "mx_check_user_pass", 'G');
    }
    else {
        mx_bites_str((*node)->ssl, "Wrong pass or user name", 'B');
        mx_strdel(&(*node)->user);
    }
}
static t_list *mx_list_adition(char *command, char **arr, int *hist_flagh) {
    t_list *list = NULL;

    if (mx_strcmp(command, "mx_send_list_back") == 0)
        list = mx_send_list_back(arr[0], mx_atoi(arr[1]));
    else if (mx_strcmp(command, "mx_regular_request") == 0
        || mx_strcmp(command, "mx_mssg_search") == 0) {
        list = mx_send_list_back(arr[0], 0);
        *hist_flagh = 1;
    }
    else if (mx_strcmp(command, "mx_user_search") == 0)
        list = mx_user_search(arr[0], arr[1], arr[2]);
    return list;
}
static int mx_type_adition(char *command, char **arr, t_node **node, char **json) {
    if (mx_strcmp(command, "mx_get_type") == 0)
        return mx_get_type(arr[0], mx_atoi(arr[1]));
    else if (mx_strcmp(command, "mx_get_img_path") == 0) {
        pthread_mutex_lock(&(*node)->files_mutex);
        mx_push_file_way(&(*node)->list, *json);
        *json = NULL;
        pthread_mutex_unlock(&(*node)->files_mutex);
    }
    else if (mx_strcmp(command, "mx_check_user_pass") == 0)
        mx_check_user_pass_adt(arr, node);
    return -1;
}
static void mx_send_back_adt(t_node **node, t_list *list, char **json) {
    if (!list
        && mx_check_json_cmd(*json, "command", "mx_send_list_back"))
        mx_bites_str((*node)->ssl, "mx_send_list_back", 'B');
    else if (!list
             && mx_check_json_cmd(*json, "command", "mx_mssg_search"))
        mx_bites_str((*node)->ssl, "mx_mssg_search", 'B');
}
void mx_send_back(t_node **node, char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);
    int hist_flagh = 0;
    int type = -1;
    t_list *list = NULL;

    list = mx_list_adition(command, arr, &hist_flagh);
    type = mx_type_adition(command, arr, node, json);
    if (list) {
        mx_send_answer_list(node, list, hist_flagh, *json);
        mx_del_list(&list, 0);
        if (hist_flagh == 1)
            hist_flagh = 0;
        (*node)->flag += 1;
    }
    else if (type != -1)
        mx_send_answer_type(node, type, mx_atoi(arr[1]));
    mx_send_back_adt(node, list, json);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}
static void mx_update(t_node **node, char **arr) {
    if (mx_strcmp(arr[0], "user") == 0)
        mx_replace(&(*node)->user, arr[1]);
    else if (mx_strcmp(arr[0], "chat") == 0) {
        mx_replace(&(*node)->chat, arr[1]);
        mx_replace(&(*node)->size, "20");
    }
    else if (mx_strcmp(arr[0], "size") == 0)
        mx_replace(&(*node)->size, arr[1]);
    else if (mx_strcmp(arr[0], "history") == 0)
        mx_replace(&(*node)->history, arr[1]);
}
void mx_not_mutex(t_node **node, char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);

    if (mx_strcmp(command, "mx_update") == 0)
        mx_update(node, arr);
    else
        mx_send_back(node, json);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}

/* mutex or not */
void mx_log_out_fie_del(t_way **list) {
    if (!list || !*list)
        return ;
    t_way *i = *list;
    int j = 0;

    for (; i->next; i = i->next);
    for (; i->back; i = i->back)
        j++;
    for (; j > 0; j--)
        mx_unset_file_node(&i);
    i = NULL;
}
static void mx_mutex_first_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_error") == 0)
        (*node)->exit = 0;
    else if (mx_strcmp(command, "mx_add_new_user") == 0) {
        if (mx_add_new_user(arr[0], arr[1], arr[2]) == 0) {
            mx_send_your_photo(node);
            mx_bites_str((*node)->ssl, "mx_add_new_user", 'G');
        }
        else {
            mx_bites_str((*node)->ssl, "User already exist", 'B');
            mx_strdel(&(*node)->user);
        }
    }
    else if (mx_strcmp(command, "mx_add_user_to_table") == 0)
        mx_add_user_to_table(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_add_user_to_table", 'G')
            : mx_bites_str((*node)->ssl, "Can't add user", 'B');
    else if (mx_strcmp(command, "mx_delete_user") == 0)
        mx_delete_user(arr[0]) == 0
            ? mx_bites_str((*node)->ssl, "mx_delete_user", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete user", 'B');
}
static void mx_mutex_second_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_recv_new_mess") == 0) {
        t_input data;

        data.name_from = arr[0];
        data.name_to = arr[1];
        data.message = arr[2];
        data.flag = mx_atoi(arr[3]);
        data.reply = arr[4];
        data.forward = arr[5];
        if (mx_atoi(arr[3]) == 1)
            data.file_name = mx_strdup(arr[2]);
        else
            data.file_name = mx_strdup("NULL");
        mx_recv_new_mess(&data) == 0
            ? mx_bites_str((*node)->ssl, "mx_recv_new_mess", 'G')
            : mx_bites_str((*node)->ssl, "Can't send message", 'B');
    }
}
static void mx_mutex_third_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_del_history") == 0)
        mx_del_history(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_history", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete history", 'B');
    else if (mx_strcmp(command, "mx_del_message") == 0)
        mx_del_message(arr[0], arr[1], arr[2]) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_message", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete message", 'B');
    else if (mx_strcmp(command, "mx_edit") == 0)
        mx_edit(arr[0], arr[1], arr[2], arr[3]) == 0
            ? mx_bites_str((*node)->ssl, "mx_edit", 'G')
            : mx_bites_str((*node)->ssl, "Can't edit message", 'B');
    else if (mx_strcmp(command, "mx_change_log") == 0)
        mx_change_log(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_change_log", 'G')
            : mx_bites_str((*node)->ssl, "Can't change user name", 'B');
    else if (mx_strcmp(command, "mx_change_pass") == 0)
        mx_change_pass(arr[0], arr[1]) == 0
            ? mx_bites_str((*node)->ssl, "mx_change_pass", 'G')
            : mx_bites_str((*node)->ssl, "Can't change password", 'B');
}
static void mx_mutex_fourth_adt(t_node **node, char *command, char **arr) {
    if (mx_strcmp(command, "mx_set_type") == 0)
        mx_set_type(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_set_type", 'G')
            : mx_bites_str((*node)->ssl, "Can't change type", 'B');
    else if (mx_strcmp(command, "mx_change_img") == 0) {
        if (mx_change_img(arr[0], arr[1]) == 0) {
            mx_send_your_photo(node);
            mx_bites_str((*node)->ssl, "mx_change_img", 'G');
        }
        else
            mx_bites_str((*node)->ssl, "Can't change image", 'B');
    }
    else if (mx_strcmp(command, "mx_del_user_from_table") == 0)
        mx_del_user_from_table(arr[0], arr[1], mx_atoi(arr[2])) == 0
            ? mx_bites_str((*node)->ssl, "mx_del_user_from_table", 'G')
            : mx_bites_str((*node)->ssl, "Can't delete user from table", 'B');
}
void mx_mutex_command(t_node **node, char *json) {
    char *command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    mx_mutex_first_adt(node, command, arr);
    mx_mutex_second_adt(node, command, arr);
    mx_mutex_third_adt(node, command, arr);
    mx_mutex_fourth_adt(node, command, arr);
    if (mx_strcmp(command, "mx_log_out") == 0
        || mx_strcmp(command, "mx_delete_user") == 0) {
        pthread_mutex_lock(&(*node)->files_mutex);
        mx_log_out_fie_del(&(*node)->list);
        pthread_mutex_unlock(&(*node)->files_mutex);
        mx_replace(&(*node)->user, "NULL");
        mx_replace(&(*node)->chat, "NULL");
        mx_replace(&(*node)->size, "20");
        mx_replace(&(*node)->history, "normal");
    }
    mx_strdel(&command);
    mx_del_strarr(&arr);
}
static bool mx_check_command(char *json) {
    if (mx_check_json_cmd(json, "command", "mx_error")
        || mx_check_json_cmd(json, "command", "mx_add_new_user")
        || mx_check_json_cmd(json, "command", "mx_add_user_to_table")
        || mx_check_json_cmd(json, "command", "mx_delete_user")
        || mx_check_json_cmd(json, "command", "mx_recv_new_mess")
        || mx_check_json_cmd(json, "command", "mx_del_history")
        || mx_check_json_cmd(json, "command", "mx_del_message")
        || mx_check_json_cmd(json, "command", "mx_edit")
        || mx_check_json_cmd(json, "command", "mx_log_out")
        || mx_check_json_cmd(json, "command", "mx_change_log")
        || mx_check_json_cmd(json, "command", "mx_change_pass")
        || mx_check_json_cmd(json, "command", "mx_del_user_from_table")
        || mx_check_json_cmd(json, "command", "mx_set_type"))
        return true;
    return false;
}
void mx_exe_request(t_node **node, char **json) {
    if (mx_check_command(*json)) {
        pthread_mutex_lock((*node)->mutex);
        mx_mutex_command(node, *json);
        pthread_mutex_unlock((*node)->mutex);
    }
    else
        mx_not_mutex(node, json);
}

/* recv request */
static char *mx_create_usual_request(t_node *node) {
    char *json = NULL;
    char *command = NULL;
    char **arr = NULL;

    command = mx_strdup("mx_regular_request");
    arr = mx_arrjoin(arr, node->user);
    arr = mx_arrjoin(arr, node->chat);
    arr = mx_arrjoin(arr, node->size);
    arr = mx_arrjoin(arr, node->history);
    json = mx_request(command, arr);
    mx_strdel(&command);
    mx_del_strarr(&arr);
    return json;
}
static void mx_recv_file(t_node *node, char ch[]) {
    if (ch[1] == 'N') {
        node->for_files->file_name = mx_super_join(node->user, ".", 0);
        mx_static_read(ch, &node->for_files->file_name);
        mx_del_if_exist(node->for_files->file_name);
        node->for_files->file = fopen(node->for_files->file_name, "wb");
    }
    else if (ch[1] == 'S')
        mx_static_read(ch, &node->for_files->file_size);
    else if (node->for_files->file && ch[1] == 'B')
        fwrite(&ch[2], 1, 1, node->for_files->file);
    else if (node->for_files->file && ch[1] == 'C') {
        mx_check_file_size(node->for_files->file,
                           &node->for_files->file_size,
                           &node->for_files->file_name);
    }
}
static void mx_recv_request(t_node *node, char **json) {
    char ch[SIZE_SEND];
    int fd = -1;

    while ((fd = SSL_read(node->ssl, ch, SIZE_SEND)) != -1) {
        if (ch[0] == 'T') {
            mx_static_read(ch, json);
            if (ch[1] == 'E')
                break;
        }
        else if (ch[0] == 'F')
            mx_recv_file(node, ch);
        mx_memset(ch, '\0', SIZE_SEND);
    }
    if (fd == -1) {
        mx_strdel(json);
        mx_del_file(node->for_files->file, &node->for_files->file_size,
                    &node->for_files->file_name);
        *json = mx_strdup("mx_error");
    }
}
void mx_choose(t_node *node, char **json) {
    struct pollfd ufds;

    ufds.fd = node->client;
    ufds.events = POLLIN;
    if (poll(&ufds, 1, TIMER) == 0)
        *json = mx_create_usual_request(node);
    else if (ufds.revents & POLLIN)
        mx_recv_request(node, json);
}

/* delete node */
static void mx_free_struct(t_node **node, int flag) {
    if (!node || !*node)
        return;
    mx_strdel(&(*node)->json);
    mx_strdel(&(*node)->user);
    mx_strdel(&(*node)->chat);
    mx_strdel(&(*node)->size);
    mx_strdel(&(*node)->history);
    mx_strdel(&(*node)->for_files->file_size);
    mx_strdel(&(*node)->for_files->file_name);
    if ((*node)->ssl && flag != 1)
        SSL_free((*node)->ssl);
    if ((*node)->ctx && flag != 1)
        SSL_CTX_free((*node)->ctx);
    if ((*node)->client != -1)
        close((*node)->client);
    if ((*node)->for_files->file)
        fclose((*node)->for_files->file);
    free((*node)->for_files);
    free(*node);
    *node = NULL;
}
static void mx_unset_node_adt(t_way **list, t_way **next, t_way **back) {
    if ((*list)->next)
        (*next) = (*list)->next;
    if ((*list)->back)
        (*back) = (*list)->back;
    if (*next && *back)
        (*next)->back = *back;
    else if (*next)
        (*next)->back = NULL;
    if (*back && *next)
        (*back)->next = *next;
    else if (*back)
        (*back)->next = NULL;
}
static void mx_unset_node(t_way **list, void *data) {
    t_way *next = NULL;
    t_way *back = NULL;

    mx_unset_node_adt(list, &next, &back);
    mx_free_node(list);
    if (next)
        *((t_way **)data) = next;
    else if (back)
        *((t_way **)data) = back;
    else
        *((t_way **)data) = NULL;
}
void mx_del_client(t_way **list, t_node **node, void *data, int flag) {
    mx_free_struct(node, flag);
    mx_unset_node(list, data);
    free(*list);
    *list = NULL;
}
void *mx_server_handel(void *data) {
    t_way *list = *((t_way **)data);
    t_node *node = (t_node *)list->data;
    char *json = NULL;

    while (node->exit == 1) {
        mx_choose(node, &json);
        if (json) {system("clear"); printf("%s\n", json);}                       // delete
        // if (json) {printf("%d\n", node->client); printf("%s\n", json);}          // delete
        mx_exe_request(&node, &json);
        mx_strdel(&json);
    }
    mx_strdel(&json);
    return NULL;
}

/* handel for files */
static int mx_send_size_name(t_node *node, FILE *file, char *img_name) {
    char *len = NULL;

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_bites_str(node->ssl, img_name, 'F');
    mx_file_size_close(node->ssl, len, 'F', 'L');
    mx_strdel(&len);
    return 0;
}
static void mx_server_files_send(char *json, t_node *node) {
    char **arr = mx_get_arr(json);
    char *img_name = NULL;
    char *img_path = mx_get_img_path(arr[0], arr[1],
                                     mx_atoi(arr[2]), &img_name);
    FILE *file = fopen(img_path, "rb");

    if (file) {
        if (mx_send_size_name(node, file, img_name) != 1) {
            mx_file_bites(file, node->ssl, 'F', 'B');
            mx_file_size_close(node->ssl, "close", 'F', 'C');
        }
        fclose(file);
    }
    mx_strdel(&img_name);
    mx_strdel(&img_path);
    mx_del_strarr(&arr);
}
void *mx_server_files(void *data) {
    t_way *list = *((t_way **)data);
    t_node *node = (t_node *)list->data;

    while (node->exit == 1) {
        if (node->list) {
            pthread_mutex_lock(&node->files_mutex);
            mx_server_files_send((char *)node->list->data, node);
            mx_strdel((char **)&node->list->data);
            mx_unset_file_node(&node->list);
            pthread_mutex_unlock(&node->files_mutex);
        }
    }
    mx_del_client(&list, &node, data, 0);
    return NULL;
}

static void mx_create_t_node_adt(t_node **node) {
    (*node)->ssl = NULL;
    (*node)->ctx = NULL;
    (*node)->json = NULL;
    (*node)->list = NULL;
    (*node)->for_files = (t_files *)malloc(sizeof(t_files));
    (*node)->for_files->file = NULL;
    (*node)->for_files->file_size = NULL;
    (*node)->for_files->file_name = NULL;
    (*node)->chat = mx_strdup("NULL");
    (*node)->user = mx_strdup("NULL");
    (*node)->size = mx_strdup("20");
    (*node)->history = mx_strdup("normal");
}
static t_node *mx_create_t_node(t_server server) {
    t_node *node = (t_node *)malloc(sizeof(t_node));

    mx_create_t_node_adt(&node);
    node->client = -1;
    node->exit = 1;
    node->flag = 0;
    node->mutex = &(server.mutex);
    pthread_mutex_init(&node->files_mutex, NULL);
    return node;
}
static void mx_server_properties(t_server *server, char *argv[]) {
    server->server = socket(AF_INET, SOCK_STREAM, 0);
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(mx_atoi(argv[2]));
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->list = NULL;
    pthread_mutex_init(&(server->mutex), NULL);
    signal(SIGPIPE, SIG_IGN);
}
static void mx_server_sin_log(t_server server) {
    pthread_create(&((t_node *)server.list->data)->thread, NULL, mx_server_handel, &server.list);
    pthread_create(&((t_node *)server.list->data)->files, NULL, mx_server_files, &server.list);
}
int mx_server(int argc, char *argv[]) {
    if (argc != 3) // add usage and move it to daemon
        return 1;
    t_server server;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    mx_server_properties(&server, argv);
    bind(server.server, (struct sockaddr *)&server.server_addr, sizeof(server.server_addr));
    while (1) {
        listen(server.server, 1);
        t_node *node = mx_create_t_node(server);

        node->client = accept(server.server, (struct sockaddr *)&node->client_addr, &addr_size);        
        server.list = NULL;
        mx_push_back_t_way(&(server.list), (void *)node);
        if (mx_server_handshake(&server) == 1)
            mx_del_client(&server.list, (t_node **)&server.list->data, &server.list, 1);
        else
            mx_server_sin_log(server);
    }
    pthread_mutex_destroy(&(server.mutex));
    close(server.server);
    return 0;
}
