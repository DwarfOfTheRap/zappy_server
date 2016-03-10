#include "linked_lists.h"

void	lst_insert(t_lst_head *head, t_lst_elem *new, int (*f)(void*, void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*previous;

	if (!head)
		return ;
	if (!(cursor = head->first))
		return (lst_pushfront(head, new));
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

void*	lst_first_match(t_lst_head *hd, void *dt, int (*cmp)(void*, void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*prev_save;
	t_lst_elem	*elem_to_remove;

	elem_to_remove = NULL;
	if (!hd)
		return (NULL);
	cursor = hd->first;
	while (cursor)
	{
		prev_save = cursor;
		cursor = cursor->next;
		if (cmp(prev_save->content, dt))
			return (prev_save->content);
	}
	return (NULL);
}
