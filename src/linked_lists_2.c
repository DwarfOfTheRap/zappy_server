#include <stdlib.h>
#include "linked_lists.h"

t_lst_elem	*lst_remove(t_lst_head *head, t_lst_elem *elem_to_remove)
{
	if (!(head && elem_to_remove))
		return (NULL);
	if (elem_to_remove == head->first)
		head->first = elem_to_remove->next;
	if (elem_to_remove == head->last)
		head->last = elem_to_remove->prev;
	if (elem_to_remove->prev)
		elem_to_remove->prev->next = elem_to_remove->next;
	if (elem_to_remove->next)
		elem_to_remove->next->prev = elem_to_remove->prev;
	elem_to_remove->next = NULL;
	elem_to_remove->prev = NULL;
	head->size--;
	return (elem_to_remove);
}

t_lst_elem	*lst_pop(t_lst_head *head, unsigned int index_to_remove)
{
	t_lst_elem	*cursor;

	if (!head)
		return (NULL);
	cursor = head->first;
	while (cursor && index_to_remove--)
		cursor = cursor->next;
	if (cursor)
		cursor = lst_remove(head, cursor);
	return (cursor);
}

void		lst_delete_elem(t_lst_elem **elem, void (*del)(void*))
{
	if (elem && *elem)
	{
		del((*elem)->content);
		free(*elem);
		*elem = NULL;
	}
}

void		lst_free_match(t_lst_head *hd, void *dt
								, int *(*cmp)(void*, void*), void (*del)(void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*elem_to_remove;

	elem_to_remove = NULL;
	if (!hd)
		return ;
	cursor = hd->first;
	while (cursor)
	{
		if (cmp(cursor->content, dt))
		{
			elem_to_remove = lst_remove(hd, cursor);
			lst_delete_elem(&elem_to_remove, del);
		}
		cursor = cursor->next;
	}
}

void		lst_delete(t_lst_head *head, void (*del)(void*))
{
	t_lst_elem	*cursor;
	t_lst_elem	*elem_to_remove;

	if (!head)
		return ;
	cursor = head->first;
	while (cursor)
	{
		elem_to_remove = lst_remove(head, cursor);
		lst_delete_elem(&elem_to_remove, del);
		cursor = cursor->next;
	}
}
