#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int max = size - 1, min = 0, mid; 
	if (!s) return -1;
 	while(min <= max) {  
	mid = min + (max - min) / 2;
		if(mx_strcmp(arr[mid], s) == 0) {
			*count += 1;
			return mid;
		}
		else {
			if(mx_strcmp(arr[mid], s) < 0) {
				*count += 1;
				min = mid + 1;
			}
			else {
				*count += 1;
				max = mid - 1;
			}
		}
	}
	*count = 0;
	return -1;
}
