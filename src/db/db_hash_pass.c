#include "../../inc/header.h"

/* hash pass */
static void mx_hash_adt(unsigned char md[], char **hash) {
    for (int i = 0; i < 64; i++) {
        if ((int)md[i] >= 0 && (int)md[i] <= 15) {
            *hash = mx_super_join(*hash, "0", 1);
            if ((int)md[i] == 0)
                *hash = mx_super_join(*hash, "0", 1);
        }
        char *add = mx_nbr_to_hex((unsigned long)md[i]);

        *hash = mx_super_join(*hash, add, 1);
        mx_strdel(&add);
    }
}

char *mx_hash(char *salt, char *pass) {
    if (!salt || !pass)
        return NULL;
    char *hash = NULL;
    char *full = mx_super_join(salt, pass, 0);
    unsigned char md[64];
    SHA512_CTX ctx;

    SHA512_Init(&ctx);
    SHA512_Update(&ctx, full, mx_strlen(full));
    SHA512_Final(md, &ctx);
    mx_strdel(&full);
    mx_hash_adt(md, &hash);
    hash[128] = '\0';
    return hash;
}

