#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
	t_list *current = list;
	int count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}
