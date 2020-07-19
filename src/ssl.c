#include "../inc/ssl.h"

// change fprintf

SSL_CTX *mx_get_client_context(void) {
    SSL_CTX *ctx;

    if (!(ctx = SSL_CTX_new(SSLv23_client_method()))) {
        fprintf(stderr, "Cannot create a client context\n");
        return NULL;
    }
    if (SSL_CTX_load_verify_locations(ctx, "./keys/ca/ca_cert.pem", NULL) != 1) {
        fprintf(stderr, "Cannot load client's CA file\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (SSL_CTX_use_certificate_file(ctx, "./keys/client/client_cert.pem", SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot load client's certificate file\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "./keys/client/private/client_key.pem", SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot load client's key file\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (SSL_CTX_check_private_key(ctx) != 1) {
        fprintf(stderr, "Client's certificate and key don't match\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    SSL_CTX_set_verify_depth(ctx, 1);
    return ctx;
}

int mx_client_handshake(t_client *client) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    if (!(client->ctx = mx_get_client_context()))
        return 1;
    client->ssl = SSL_new(client->ctx);
    SSL_set_fd(client->ssl, client->socket);
    if (!SSL_connect(client->ssl)) {
        SSL_CTX_free(client->ctx);
        return 1;
    }
    if (SSL_do_handshake(client->ssl) != 1) {
        SSL_CTX_free(client->ctx);
        SSL_free(client->ssl);
        return 1;
    }
    if (SSL_get_verify_result(client->ssl) != X509_V_OK) {
        SSL_CTX_free(client->ctx);
        SSL_free(client->ssl);
        return 1;
    }
    return 0;
}

SSL_CTX *get_server_context() {
    SSL_CTX *ctx;

    if (!(ctx = SSL_CTX_new(SSLv23_server_method()))) {
        fprintf(stderr, "SSL_CTX_new failed\n");
        return NULL;
    }
    if (SSL_CTX_load_verify_locations(ctx, "./keys/ca/ca_cert.pem", NULL) != 1) {
        fprintf(stderr, "Cannot set the CA file location\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file("./keys/ca/ca_cert.pem"));
    if (SSL_CTX_use_certificate_file(ctx, "./keys/server/server_cert.pem", SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot set the server's certificate\n");
        SSL_CTX_free(ctx);
        return NULL;
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "./keys/server/private/server_key.pem", SSL_FILETYPE_PEM) != 1) {
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
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    SSL_CTX_set_verify_depth(ctx, 1);
    return ctx;
}

int mx_server_handshake(t_server *server) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    if (!(((t_node *)server->list->data)->ctx = get_server_context()))
        return 1;
    ((t_node *)server->list->data)->ssl = SSL_new(((t_node *)server->list->data)->ctx);
    SSL_set_fd(((t_node *)server->list->data)->ssl, ((t_node *)server->list->data)->client);
    if (SSL_accept(((t_node *)server->list->data)->ssl) != 1) {
        SSL_free(((t_node *)server->list->data)->ssl);
        SSL_CTX_free(((t_node *)server->list->data)->ctx);
        return 1;
    }
    return 0;
}
