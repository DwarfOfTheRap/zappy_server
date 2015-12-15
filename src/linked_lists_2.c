#include <stdlib.h>
#include "linked_lists.h"

t_lst_elem		*lst_pop(t_lst_head *head, unsigned int index_to_remove)
{
	t_lst_elem	*cursor;
	t_lst_elem	*result;

	if (!head)
		return (NULL);
	cursor = head->first;
	while (cursor && index_to_remove--)
		cursor = cursor->next;
	if (cursor)
	{
		if (!cursor->prev)
			head->first = cursor->next;
		else
			cursor->prev->next = cursor->next;
		if (!cursor->next)
			head->last = cursor->prev;
		else
			cursor->next->prev = cursor->prev;
		cursor->next = NULL;
		cursor->prev = NULL;
		head->size--;
	}
	return (cursor);
}
