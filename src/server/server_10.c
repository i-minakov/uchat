#include "../../inc/header.h"

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

static void mx_server_properties(t_server *server, char *argv[], int argc) {
    int auditor = 0;

    auditor = argc;
    server->server = socket(AF_INET, SOCK_STREAM, 0);
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(mx_atoi(argv[2]));
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->list = NULL;
    pthread_mutex_init(&(server->mutex), NULL);
    signal(SIGPIPE, SIG_IGN);
}

static void mx_server_sin_log(t_server server) {
    pthread_create(&((t_node *)server.list->data)->thread,
                   NULL, mx_server_handel, &server.list);
    pthread_create(&((t_node *)server.list->data)->files,
                   NULL, mx_server_files, &server.list);
}

int mx_server(int argc, char *argv[]) {
    t_server server;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    mx_server_properties(&server, argv, argc);
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

