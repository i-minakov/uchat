#include "../../inc/header.h"

static void mx_client_properties(t_client *client, char *argv[]) {
    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    client->addr.sin_family = AF_INET;
    client->addr.sin_port = htons(mx_atoi(argv[3]));
    client->list = NULL;
    client->user = NULL;
    client->exit = 1;
    client->status = NULL;
    client->for_files = (t_files *)malloc(sizeof(t_files));
    client->for_files->file = NULL;
    client->for_files->file_name = NULL;
    client->for_files->file_size = NULL;
    client->gtk = malloc_main();
    client->gtk->cmd = DEF;
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
    mx_strdel(&client.user);
    SSL_free(client.ssl);
    SSL_CTX_free(client.ctx);
    free(client.for_files);
    close(client.socket);
}

int mx_client(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: uchat IP PORT\n");
        return 1;
    }
    t_client client;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    client.mutex = &mutex;
    mx_client_properties(&client, argv);
    inet_pton(AF_INET, argv[2], &client.addr.sin_addr);
    connect(client.socket, (struct sockaddr *)&client.addr, sizeof(client.addr));
    if (mx_client_handshake(&client) == 1) {
        fprintf(stderr, "Client's certificate and key don't match\n");
        return 1;
    }
    mx_client_sin_log(client);
    pthread_mutex_destroy(&mutex);
    return 0;
}
