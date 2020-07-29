#include "../../inc/ssl.h"

static int mx_get_client_context_adt(SSL_CTX **ctx) {
    if (!(*ctx = SSL_CTX_new(SSLv23_client_method()))) {
        fprintf(stderr, "Cannot create a client context\n");
        return 1;
    }
    if (SSL_CTX_load_verify_locations(*ctx, CA_CERT, NULL) != 1) {
        fprintf(stderr, "Cannot load client's CA file\n");
        SSL_CTX_free(*ctx);
        return 1;
    }
    if (SSL_CTX_use_certificate_file(*ctx, CLIENT_CERT,
                                     SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "Cannot load client's certificate file\n");
        SSL_CTX_free(*ctx);
        return 1;
    }
    return 0;
}

SSL_CTX *mx_get_client_context(void) {
    SSL_CTX *ctx;

    if (mx_get_client_context_adt(&ctx) == 1)
        return NULL;
    if (SSL_CTX_use_PrivateKey_file(ctx, CLIENT_KEY, SSL_FILETYPE_PEM) != 1) {
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

static int mx_client_handshake_adt(t_client *client) {
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

int mx_client_handshake(t_client *client) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    if (!(client->ctx = mx_get_client_context()))
        return 1;
    client->ssl = SSL_new(client->ctx);
    SSL_set_fd(client->ssl, client->socket);
    if (mx_client_handshake_adt(client) == 1)
        return 1;
    return 0;
}
