#include "libmx.h"

char **mx_strsplit(char const *s, char c) {
    if (!s || !mx_strlen(s))
        return NULL;
    int len = mx_count_words(s, c);
    char **arr = (char **) malloc((len + 1) * sizeof(char *));

    for (int i = 0; i < len; i++) {
        if (*s == c && *s != '\0')
            for ( ; *s == c && *s != '\0'; s++);
        if (*s != c && *s != '\0') {
            int k = 0;

            for ( ; s[k] != c && s[k] != '\0'; k++);
            arr[i] = (char *) malloc(k + 1 * sizeof(char));
            for (int j = 0; *s != c && *s != '\0'; s++, j++)
                arr[i][j] = *s;
            arr[i][k] = '\0';
        }
    }
    arr[len] = NULL;
    return arr;
}
