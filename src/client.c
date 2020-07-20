#include "../inc/header.h"

/* !!!delete!!! */
static void mx_enter_argv(char ***arr, t_client *client) {
    char **request = client->gtk->command;

    if (request) {
        *arr = mx_copy_arr(request);
        mx_del_strarr(&client->gtk->command);
        client->gtk->command = NULL;
        request = NULL;
    }
}

/* sort */
int mx_intcmp(char *str1, char *str2) {
    int num1 = mx_atoi(str1);
    int num2 = mx_atoi(str2);

    if (num1 != num2)
        return num1 - num2;
    return 0;
}
int mx_monthcmp(char *month1, char *month2) {
    enum e_month {Jan, Feb, Mar, Apr, May, Jun,
                  Jul, Aug, Sep, Oct, Nov, Dec};
    static struct {char *m; enum e_month e;} map[] = {
        {"Jan", Jan}, {"Feb", Feb}, {"Mar", Mar}, {"Apr", Apr},
        {"May", May}, {"Jun", Jun}, {"Jul", Jul}, {"Aug", Aug},
        {"Sep", Sep}, {"Oct", Oct}, {"Nov", Nov}, {"Dec", Dec},};
    int num1 = 0;
    int num2 = 0;

    for (int i = 0; i < sizeof(map)/sizeof(map[0]); i++) {
        if (mx_strcmp(month1, map[i].m) == 0)
            num1 = map[i].e;
        if (mx_strcmp(month2, map[i].m) == 0)
            num2 = map[i].e;
    }
    if (num1 != num2)
        return num1 - num2;
    return 0;
}
static int mx_switch_time(int i, char **arr1, char **arr2) {
    switch(i) {
        case 1:
            return mx_intcmp(arr1[4], arr2[4]);
        case 2:
            return mx_monthcmp(arr1[1], arr2[1]);
        case 3:
            return mx_intcmp(arr1[2], arr2[2]);
        case 4:
            return mx_intcmp(arr1[0], arr2[0]);
        case 5:
            return mx_intcmp(arr1[1], arr2[1]);
        case 6:
            return mx_intcmp(arr1[2], arr2[2]);
        default:
            return 0;
    }
}
static void mx_change_cmp(char ***arr) {
    if (!arr || !*arr)
        return;
    char **shift = mx_strsplit((*arr)[3], ':');

    mx_del_strarr(&(*arr));
    *arr = shift;
}
static int mx_parse_time(char *str1, char *str2) {
    int result = 0;
    char **arr1 = mx_strsplit(str1, ' ');
    char **arr2 = mx_strsplit(str2, ' ');

    for (int i = 0; i < 6; i++) {
        if (i == 3) {
            mx_change_cmp(&arr1);
            mx_change_cmp(&arr2);
        }
        if ((result = mx_switch_time(i + 1, arr1, arr2)) != 0)
            break;
    }
    mx_del_strarr(&arr1);
    mx_del_strarr(&arr2);
    return result;
}
static int mx_pre_parse_time(char *json1, char *json2) {
    int result = 0;
    char **arr1 = mx_get_arr(json1);
    char **arr2 = mx_get_arr(json2);

    result = mx_parse_time(arr1[1], arr2[1]);
    mx_del_strarr(&arr1);
    mx_del_strarr(&arr2);
    return result;
}
void mx_sort_mssg(t_list **list, int flag) {
    int out = 0;
    void *data = NULL;

    while (out == 0) {
        out = 1;
        for (t_list *i = *list; i && i->next; i = i->next)
            if ((flag == 0 && mx_pre_parse_time((char *)((t_data *)i->data)->list->data,
                    (char *)((t_data *)i->next->data)->list->data) > 0)
                || (flag == 1 && mx_strcmp(((t_data *)i->data)->name,
                    ((t_data *)i->next->data)->name) > 0)) {
                data = i->data;
                i->data = i->next->data;
                i->next->data = data;
                data = NULL;
                out = 0;
            }
    }
}

/* send request */
static void mx_get_request(char **json, t_client *client) { // delete
    char *command = NULL;
    char **arr = NULL;

    mx_enter_argv(&arr, client);
    if (arr && arr[0])
        command = mx_strdup(arr[0]);
    *json = mx_request(command, &arr[1]);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}

static void mx_hash_pass(char **json) {
    char *command = mx_get_value(*json, "command");
    char **arr = mx_get_arr(*json);
    char *hash = mx_strdup(arr[1]);

    mx_strdel(&arr[1]);
    arr[1] = mx_hash(arr[0], hash);
    mx_strdel(json);
    *json = mx_request(command, arr);
    mx_strdel(&hash);
    mx_strdel(&command);
    mx_del_strarr(&arr);
}
static int mx_command(t_client *client, char **json) {
    int result = 0;

    pthread_mutex_lock(client->mutex);
    if (mx_check_json_cmd(*json, "command", "mx_error"))
        result = 1;
    if (mx_for_file(*json)) {
        mx_push_file_way(&client->list, (void *)*json);
        *json = NULL;
    }
    else {
        if (mx_check_json_cmd(*json, "command", "mx_add_new_user")
            || mx_check_json_cmd(*json, "command", "mx_check_user_pass")
            || mx_check_json_cmd(*json, "command", "mx_change_pass"))
            mx_hash_pass(json);            
        mx_bites_str(client->ssl, *json, 'T');
    }
    pthread_mutex_unlock(client->mutex);
    return result;
}
void mx_client_send(t_client *client) {
    char *json = NULL;

    log_screen(client->gtk);
    while (client->exit == 1) {
        gtk_main_iteration();
        mx_get_request(&json, client);
        if (mx_command(client, &json) == 1)
            break;
        mx_strdel(&json);
    }
    client->exit = 0;
    mx_strdel(&json);
}

/* recv callbacks */
static void mx_server_answer(char ch[], char *str, t_client *client) { // server answer
    client->status = mx_strdup(str);
    if (ch[0] == 'B')
        printf("error = %s\n", client->status);
    if (ch[0] == 'G')
        printf("good = %s\n", client->status);
}
void mx_recv_len_theme(char ch[], t_client *client) { // change lan and theme
    char *str = NULL;

    mx_static_read(ch, &str);
    if (ch[0] == 'T') {
        if (ch[1] == 'L')
            printf("switch Lan\n");
        else if (ch[1] == 'T')
            printf("switch Theme\n");
    }
    else
        mx_server_answer(ch, str, client);
    mx_strdel(&str);
}
static t_data *mx_create_data(void) {
    t_data *node = (t_data *)malloc(sizeof(t_data));
    char *str = NULL;

    node->path = NULL;
    node->name = NULL;
    node->list = NULL;
    mx_push_front(&node->list, str);
    return node;
}
static t_info *mx_create_info(void) {
    t_info *node = (t_info *)malloc(sizeof(t_info));

    node->cmd = NULL;
    node->size = NULL;
    node->list = NULL;
    return node;
}
char *mx_right_path(t_info **info, t_files *files) {
    char *path = NULL;

    if (mx_strcmp((*info)->cmd, "mx_send_list_back") == 0)
        path = mx_super_join("./source/cash/listback/", files->file_name, 0);
    else if (mx_strcmp((*info)->cmd, "mx_regular_request") == 0)
        path = mx_super_join("./source/cash/chats/", files->file_name, 0);
    else if (mx_strcmp((*info)->cmd, "mx_user_search") == 0)
        path = mx_super_join("./source/cash/search/", files->file_name, 0);
    return path;
}
void mx_recv_list_files(char ch[], t_info **info, t_files *files) {
    if (ch[1] == 'S')
        mx_static_read(ch, &files->file_size);
    else if (ch[1] == 'N') {
        char *s = NULL;

        mx_static_read(ch, &files->file_name);
        s = files->file_name;
        files->file_name = mx_right_path(info, files);
        mx_strdel(&s);
        mx_del_if_exist(files->file_name);
        files->file = fopen(files->file_name, "wb");
    }
    else if (ch[1] == 'B')
        fwrite(&ch[2], 1, 1, files->file);
    else if (ch[1] == 'C')
        mx_check_file_size(files->file, &files->file_size,
                           &files->file_name);
}
static void mx_trim_full_list(t_info **info) {
    if (!info || !*info)
        return;
    mx_strdel(&(*info)->cmd);
    mx_strdel(&(*info)->size);
    for (t_list *i = (*info)->list; i; i = i->next) {
        mx_strdel(&((t_data *)i->data)->name);
        mx_strdel(&((t_data *)i->data)->path);
        mx_del_list(&((t_data *)i->data)->list, 2);
    }
    mx_free_list(&(*info)->list);
    free(*info);
    *info = NULL;
}
static void mx_sort_recv_list(t_info **info) {
    if (mx_strcmp("mx_regular_request", (*info)->cmd) != 0)
        mx_sort_mssg(&(*info)->list, 1);
    else
        mx_sort_mssg(&(*info)->list, 0);
}
void mx_recv_list(char ch[], t_info **info, t_files *files) { // print list
    if (ch[0] == 'C')
        mx_static_read(ch, &(*info)->cmd);
    else if (ch[0] == 'S')
        mx_static_read(ch, &(*info)->size);
    else if (ch[0] == 'N') {
        if (ch[1] == 'E')
            mx_push_front(&(*info)->list, (void *)mx_create_data());
        mx_static_read(ch, &((t_data *)(*info)->list->data)->name);
    }
    else if (ch[0] == 'I')
        mx_recv_list_files(ch, info, files);
    else if (ch[0] == 'H') {
        if (ch[1] == 'E') {
            char *str = NULL;

            mx_push_front(&((t_data *)(*info)->list->data)->list, (void *)str);
        }
        mx_static_read(ch, (char **)&((t_data *)(*info)->list->data)->list->data);
    }
    else if (ch[0] == 'E' && ch[1] == 'E') {
        mx_sort_recv_list(info);
        //=========== delete ===========//
        printf("cmd = %s\n", (*info)->cmd);
        printf("size = %s\n", (*info)->size);
        for (t_list *i = (*info)->list; i; i = i->next) {
            printf("name = %s\n", ((t_data *)i->data)->name);
            for (t_list *j = ((t_data *)i->data)->list; j; j = j->next)
                if ((char *)j->data)
                    printf("mssg = %s\n", (char *)j->data);
        }
        printf("\n");
        //=========== delete ===========//
        mx_trim_full_list(info);
        *info = mx_create_info();
    }
}
void mx_client_recv_file(char ch[], t_client *client) { // move to particular dir
    if (ch[1] == 'E') {
        char *name = NULL;

        mx_static_read(ch, &name);
        client->for_files->file_name = mx_super_join("./", name, 2);
        mx_del_if_exist(client->for_files->file_name);
        client->for_files->file = fopen(client->for_files->file_name, "wb");
    }
    else if (ch[1] == 'L')
        mx_static_read(ch, &client->for_files->file_size);
    else if (client->for_files->file && ch[1] == 'B')
        fwrite(&ch[2], 1, 1, client->for_files->file);
    else if (client->for_files->file && ch[1] == 'C') {
        mx_check_file_size(client->for_files->file, &client->for_files->file_size,
                           &client->for_files->file_name);
        // move to particular dir
    }
}
static void mx_del_cash(void) {
    char *cmd = NULL;

    for (int i = 0; i < 3; i++) {
        if (i == 0)
            cmd = mx_super_join("./source/cash/", "chats", 0);
        else if (i == 1)
            cmd = mx_super_join("./source/cash/", "search", 0);
        else if (i == 2)
            cmd = mx_super_join("./source/cash/", "listback", 0);
        mx_del_files(cmd);
        mx_strdel(&cmd);
    }
}
void *mx_client_read(void *client_pointer) {
    t_client *client = (t_client *)client_pointer;
    t_info *info = mx_create_info();
    t_files file;
    char ch[SIZE_SEND];

    while (SSL_read(client->ssl, ch, SIZE_SEND) != -1) {
        if (((t_client *)client_pointer)->exit == 0)
            break;            
        else if (ch[0] == 'T' || ch[0] == 'G' || ch[0] == 'B')
            mx_recv_len_theme(ch, client);
        else if (ch[0] == 'S' || ch[0] == 'N' || ch[0] == 'I' || ch[0] == 'H' || ch[0] == 'C' || ch[0] == 'E')
            mx_recv_list(ch, &info, &file);
        else if (ch[0] == 'F')
            mx_client_recv_file(ch, client);
        mx_memset(ch, '\0', SIZE_SEND);
    }
    mx_del_file(client->for_files->file, &client->for_files->file_size,
                &client->for_files->file_name);
    mx_del_cash();
    client->exit = 0;
    return NULL;
}

/* send file */
static void mx_change_file_pass(char ***arr, char *command) {
    char **argv = *arr;
    char **pars = NULL;

    if (mx_strcmp(command, "mx_add_new_user") == 0
        || mx_strcmp(command, "mx_recv_new_mess") == 0) {
        pars = mx_strsplit(argv[2], '/');
        mx_strdel(&argv[2]);
        argv[2] = mx_strdup(pars[mx_arr_size(pars) - 1]);
    }
    else if (mx_strcmp(command, "mx_change_img") == 0) {
        pars = mx_strsplit(argv[1], '/');
        mx_strdel(&argv[1]);
        argv[1] = mx_strdup(pars[mx_arr_size(pars) - 1]);
    }
    mx_del_strarr(&pars);
}
void mx_send_command(char *json, t_client *client) {
    char *new_json = NULL;
    char *command = mx_get_value(json, "command");
    char **arr = mx_get_arr(json);

    mx_change_file_pass(&arr, command);
    new_json = mx_request(command, arr);
    mx_bites_str(client->ssl, new_json, 'T');
    mx_strdel(&command);
    mx_del_strarr(&arr);
    mx_strdel(&new_json);
}
static int mx_send_f_s(char *format, FILE *file, t_client *client) {
    char *len = NULL;
    char **split_dot = mx_strsplit(format, '.');

    fseek(file, 0, SEEK_END);
    len = mx_itoa(ftell(file));
    if (mx_atoi(len) > FILE_SIZE)
        return 1;
    fseek(file, 0, SEEK_SET);
    mx_file_format(split_dot, client->ssl, 'F', 'N');
    mx_file_size_close(client->ssl, len, 'F', 'S');
    mx_strdel(&len);
    mx_del_strarr(&split_dot);
    return 0;
}
static void mx_command_for_send(char *json, t_client *client) {
    FILE *file = NULL;
    char **arr = mx_get_arr(json);
    char *command = mx_get_value(json, "command");

    file = fopen(arr[2], "rb");
    if (file) {
        if (mx_send_f_s(arr[2], file, client) != 1) {
            mx_file_bites(file, client->ssl, 'F', 'B');
            mx_file_size_close(client->ssl, "close", 'F', 'C');
        }
        fclose(file);
    }
    mx_send_command(json, client);
    mx_del_strarr(&arr);
    mx_strdel(&command);
}
void *mx_files(void *client_pointer) {
    t_client *client = (t_client *)client_pointer;

    while (client->exit == 1) {
        if (client->list != NULL) {
            pthread_mutex_lock(client->mutex);
            mx_command_for_send((char *)client->list->data, client);
            mx_strdel((char **)&client->list->data);
            mx_unset_file_node(&client->list);
            pthread_mutex_unlock(client->mutex);
        }
    }
    return NULL;
}

static void mx_client_properties(t_client *client, char *argv[]) {
    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(mx_atoi(argv[3]));
    client->list = NULL;
    client->exit = 1;
    client->status = NULL;
    client->for_files = (t_files *)malloc(sizeof(t_files));
    client->for_files->file = NULL;
    client->for_files->file_name = NULL;
    client->for_files->file_size = NULL;
    client->gtk = malloc_main();
}
static void mx_client_sin_log(t_client client) {
    pthread_create(&(client.read), NULL, mx_client_read, &client);
    pthread_create(&(client.files), NULL, mx_files, &client);
    mx_client_send(&client);
    pthread_join(client.read, NULL);
    pthread_join(client.files, NULL);

    if (client.for_files->file)
        fclose(client.for_files->file);
    mx_strdel(&client.for_files->file_name);
    mx_strdel(&client.for_files->file_size);
    mx_strdel(&client.status);
    SSL_free(client.ssl);
    SSL_CTX_free(client.ctx);
    free(client.for_files);
    close(client.socket);
}
int mx_client(int argc, char *argv[]) {
    if (argc != 4) // add usage
        return 1;
    t_client client;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    client.mutex = &mutex;
    mx_client_properties(&client, argv);
    inet_pton(AF_INET, argv[2], &client.addr.sin_addr);
    connect(client.socket, (struct sockaddr *)&client.addr, sizeof(client.addr));
    if (mx_client_handshake(&client) == 1)
        return 1;
    mx_client_sin_log(client);
    pthread_mutex_destroy(&mutex);
    return 0;
}
