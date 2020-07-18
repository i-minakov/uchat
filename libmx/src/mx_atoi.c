#include "libmx.h"

int mx_atoi(const char *str) {
    if (!str)
        return 0;
    int numb = 0;
    
    for (int i = 0; str[i] ; i++)
        if (mx_isdigit(str[i])) 
            numb = (numb * 10) + str[i] - '0';
    return numb;
}
