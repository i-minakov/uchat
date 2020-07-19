#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
	if (!head || !*head) return;
	t_list *current = *head;
	if (current->next == NULL) {
		current->data = NULL;
		free(current);
		current = NULL;
	}
	else {
		t_list *p = *head;
		while (p->next->next == NULL) p = p->next;
		free(p->next->next);
		p->next->next = NULL;
	}
}
