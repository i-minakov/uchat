#ifndef SSL_H
#define SSL_H

#include <openssl/opensslconf.h>
#include <openssl/opensslv.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/ssl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <resolv.h>

#include "../libmx/inc/libmx.h"

typedef struct s_way {
    void *data;
    struct s_way *next;
    struct s_way *back;
}              t_way;

typedef struct s_files{
    FILE *file;
    char *file_name;
    char *file_size;
}              t_files;

/* Users' info*/
typedef struct s_data{
    char *path;
    char *name;
    t_list *list;
}              t_data;

typedef struct s_info{
    char *cmd;
    char *size;
    t_list *list;
}              t_info;

typedef struct s_client {
    char *user;
    SSL *ssl;
    SSL_CTX *ctx;
    pthread_t send;
    pthread_t read;
    pthread_t files;
    pthread_mutex_t *mutex;
    t_way *list;
    t_files *for_files;
    char *status;
    int exit;
    int enter;
    int socket;
    struct sockaddr_in addr;
    struct s_main *gtk;
}              t_client;

typedef struct s_node {
    SSL *ssl;
    SSL_CTX *ctx;
    pthread_t thread;
    pthread_mutex_t *mutex;
    pthread_t files;
    pthread_mutex_t files_mutex;
    t_way *list;
    t_files *for_files;
    char *json;
    char *user;
    char *chat;
    char *size;
    char *history;
    int flag;
    int exit;
    int client;
    struct sockaddr_in client_addr;
}              t_node;

typedef struct s_server {
    pthread_mutex_t mutex;
    int server;
    struct sockaddr_in server_addr;
    t_way *list;
}              t_server;

int mx_client_handshake(t_client *client);
int mx_server_handshake(t_server *list);

#endif
