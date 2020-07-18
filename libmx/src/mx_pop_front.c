#include "libmx.h"

void mx_pop_front(t_list **head) {
	if (!head || !*head) return;
	t_list *node = *head;
	t_list *new_head = node->next;
	node->data = NULL;
	node->next = NULL;
	free(node);
	node = NULL;
	*head = new_head;
}
