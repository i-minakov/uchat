#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
	if (lst == NULL) return lst;
	int flag = 1;
	while (flag) {
		flag = 0;
		for (t_list *i = lst; i->next != NULL; i = i->next) {
			if (cmp(i->data, i->next->data)) {
				char *temp = i->data;
				i->data = i->next->data;
				i->next->data = temp;
				flag = 1;
			}
		}
	}
	return lst;
}
