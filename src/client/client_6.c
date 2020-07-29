#include "../../inc/header.h"

static void mx_server_answer_adt(char ch[], t_client *client) {
    if (ch[0] == 'B') {
        if (client->gtk->cmd == BLACK_LIST
            && !mx_strcmp(client->status, "mx_send_list_back")) {
            client->gtk->cmd = DEF;
            return;
        }
        if (mx_strcmp(client->status, "Wrong pass or user name") == 0)
            bad_act(client->gtk->log_in, 1, 2);
        if (mx_strcmp(client->status, "User already exist") == 0)
            bad_act(client->gtk->log_in, 8, 2);
        mx_idle_hide(false, client->gtk->log_in->wait_gif);
        client->gtk->cmd = DEF;
    }
}

static void mx_server_answer(char ch[], char *str, t_client *client) {
    client->status = mx_strdup(str);
    mx_server_answer_adt(ch, client);
    if (ch[0] == 'G') {
        if (mx_strcmp("mx_add_new_user", client->status) == 0)
            client->gtk->cmd = SIG_UP;
        if (mx_strcmp("mx_check_user_pass", client->status) == 0) {
            mx_del_strarr(&client->gtk->command);
            client->gtk->cmd = LANG;
        }
    }
}

void mx_recv_lan_theme(char ch[], t_client *client) {
    char *str = NULL;
    int tmp;

    mx_static_read(ch, &str);
    if (ch[0] == 'T') {
        if (ch[1] == 'L') {
            tmp = mx_atoi(&ch[2]);
            client->gtk->style->lang = tmp + 1;
            client->gtk->cmd = THEME;
        }
        else if (ch[1] == 'T')  {
            tmp = mx_atoi(&ch[2]);
            client->gtk->style->color = tmp + 1;
            client->gtk->cmd = SIG_IN;
        }
    }
    else
        mx_server_answer(ch, str, client);
    mx_strdel(&str);
}

