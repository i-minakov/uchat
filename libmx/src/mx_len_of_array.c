#include "../inc/libmx.h"

int mx_len_of_array(char **a) {
    int sum = 0;
    
    if (a) {
        for (int i = 0; a[i]; i++)
            sum++;
    }
    return sum;
}
