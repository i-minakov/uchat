#include "../../inc/ssl.h"

static int mx_get_server_context_adt(SSL_CTX **ctx) {
    if (!(*ctx = SSL_CTX_new(SSLv23_server_method()))) {
        fprintf(stderr, "SSL_CTX_new failed\n");
        return 1;
    }
    if (SSL_CTX_load_verify_locations(*ctx, CA_CERT, NULL) != 1) {
        fprintf(stderr, "Cannot set the CA file location\n");
        SSL_CTX_free(*ctx);
        return 1;
    }
    SSL_CTX_set_client_CA_list(*ctx, SSL_load_client_CA_file(CA_CERT));
    if (SSL_CTX_use_certificate_file(*ctx, SERVER_CERT,
                                     SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot set the server's certificate\n");
        SSL_CTX_free(*ctx);
        return 1;
    }
    return 0;
}

SSL_CTX *mx_get_server_context(void) {
    SSL_CTX *ctx;

    if (mx_get_server_context_adt(&ctx) == 1)
        return NULL;
    if (SSL_CTX_use_PrivateKey_file(ctx, SERVER_KEY, SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot set the server's key\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (SSL_CTX_check_private_key(ctx) != 1) {
        fprintf(stderr, "Server's certificate and the key don't match\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER
                       | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    SSL_CTX_set_verify_depth(ctx, 1);
    return ctx;
}

int mx_server_handshake(t_server *server) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    if (!(((t_node *)server->list->data)->ctx = mx_get_server_context()))
        return 1;
    ((t_node *)server->list->data)->ssl =
        SSL_new(((t_node *)server->list->data)->ctx);
    SSL_set_fd(((t_node *)server->list->data)->ssl,
               ((t_node *)server->list->data)->client);
    if (SSL_accept(((t_node *)server->list->data)->ssl) != 1) {
        SSL_free(((t_node *)server->list->data)->ssl);
        SSL_CTX_free(((t_node *)server->list->data)->ctx);
        return 1;
    }
    return 0;
}
