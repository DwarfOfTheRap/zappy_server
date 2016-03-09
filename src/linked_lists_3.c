#include "linked_lists.h"

void	lst_insert(t_lst_head *head, t_lst_elem *new, int (*f)(void*, void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*previous;

	if (!head)
		return ;
	cursor = head->first;
	while (cursor && !f(new->content, cursor->content))
		cursor = cursor->next;
	if (!cursor)
		return (lst_pushback(head, new));
	else
	{
		previous = cursor->prev;
		if (!previous)
			head->first = new;
		else
		{
			previous->next = new;
			new->prev = previous;
		}
		cursor->prev = new;
		new->next = cursor;
	}
	head->size++;
}
