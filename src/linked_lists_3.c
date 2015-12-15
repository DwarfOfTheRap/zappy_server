#include "linked_lists.h"

void	lst_insert(t_lst_head *head, t_lst_elem *new, int (*f)(void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*previous;

	if (!head)
		return ;
	cursor = head->first;
	while (cursor && !f(cursor->content))
		cursor = cursor->next;
	if (!cursor)
		return ;
	previous = cursor->prev;
	if (!previous)
		head->first = new;
	else
		previous->next = new;
	new->prev = previous;
	new->next = cursor->next;
	if (cursor->next)
		cursor->next->prev = new;
	head->size++;
}
