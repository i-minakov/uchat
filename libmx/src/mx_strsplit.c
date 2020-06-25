#include "../inc/libmx.h"

// char **mx_strsplit(const char *s, char c) {
//     int words_count = mx_count_words(s, c);
//     char **arr = NULL;
//     int word_len = 0;
//     int i = 0;
//     int j = 0;

//     if (!s)
//         return NULL;
//     arr = (char**) malloc(sizeof(char*) * (words_count + 1));
//     arr[words_count] = NULL;
//     if (!words_count)
//         return arr;
//     while (s[i]) {
//         if ((word_len = mx_skip_untilchar_ncount(s, c, &i)))
//             arr[j++] = mx_strndup(s + i - word_len, word_len);
//         if (s[i])
//             mx_skipchar(s, c, &i);
//     }
//     return arr;
// }
char **mx_strsplit(const char *s, char c) {
    char **result = NULL;
    int size = 0;
    int index = 0;
    int counter = 0;

    if (!s)
        return NULL;
    size = mx_count_words(s, c);
    result = malloc(sizeof(char*) * (size + 1));
    while (*s) {
        index = mx_get_char_index(s, c);
        index = index == -1 ? mx_strlen(s) : index;
        if (index) {
            result[counter] = mx_strndup(s, index);
            s += mx_strlen(result[counter++]) - 1;
        }
        s++;
    }
    result[size] = NULL;
    return result;
}
