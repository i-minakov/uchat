#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
	if (!arr) return -1;
	int count = 0;
    if (left < right) {
        int first = left, last = right; 
        char *middle = arr[(first + last) / 2];
        
        while (mx_strlen(arr[first]) < mx_strlen(middle)) first++;
        while (mx_strlen(arr[last]) > mx_strlen(middle)) last--;
        if (first <= last) {
            if (arr[first] != arr[last]) count++;
            char *tmp = arr[first];
            arr[first] = arr[last];
            arr[last] = tmp;
            first++;
            last--;
        }

        while (first <= last) {
        	while (mx_strlen(arr[first]) < mx_strlen(middle)) first++;
            while (mx_strlen(arr[last]) > mx_strlen(middle)) last--;
            if (first <= last) {
                if (arr[first] != arr[last]) count++;
                char *tmp = arr[first];
                arr[first] = arr[last];
                arr[last] = tmp;
                first++;
                last--;
            }
        }
        count += mx_quicksort(arr, left, last);
        count += mx_quicksort(arr, first, right);
    }
    return count;
}
