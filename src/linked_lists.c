#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"

t_lst_head	*lst_init(t_lst_elem *first)
{
	t_lst_head		*head;

	if (!(head = (t_lst_head*)malloc(sizeof(t_lst_head))))
		return (NULL);
	head->size = 0;
	head->first = first;
	head->last = NULL;
	while (first)
	{
		head->size++;
		if (!(first->next))
			head->last = first;
		first = first->next;
	}
	return (head);
}

t_lst_elem	*lst_create(void *content, size_t content_size)
{
	t_lst_elem		*new;

	if (!(new = (t_lst_elem *)malloc(sizeof(t_lst_elem))))
		return (NULL);
	if (!content)
		new->content = NULL;
	else
	{
		if (!(new->content = malloc(content_size)))
		{
			free(new);
			return (NULL);
		}
		bzero(new->content, content_size);
		memcpy(new->content, content, content_size);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		lst_pushfront(t_lst_head *head, t_lst_elem *new)
{
	if (head)
	{
		if (!head->first)
			head->last = new;
		new->next = head->first;
		head->first = new;
		head->size++;
	}
}

void		lst_pushback(t_lst_head *head, t_lst_elem *new)
{
	if (!head)
		return ;
	if (!head->first)
	{
		head->first = new;
		head->last = new;
	}
	else
		head->last = new;
	head->size++;
}

t_lst_head	*lst_map(t_lst_head *hd, t_lst_elem *(*f)(t_lst_elem *e), size_t s)
{
	t_lst_head		*new_head;
	t_lst_elem		*cursor;
	t_lst_elem		*new_elem;

	if (!hd || !(new_head = lst_init(NULL)))
		return (NULL);
	cursor = hd->first;
	while (cursor)
	{
		if (!(new_elem = lst_create(cursor->content, s)))
			return (NULL);
		new_elem = f(new_elem);
		lst_pushback(new_head, new_elem);
	}
	return (new_head);
}
