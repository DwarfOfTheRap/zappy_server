#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

typedef struct	s_lst_elem
{
	void			*content;
	t_lst_elem		*next;
	t_lst_elem		*prev;
}				t_lst_elem;

typedef struct	s_lst_head
{
	t_lst_elem		*first;	
	t_lst_elem		*last;
}				t_lst_head;

t_lst_head		*lst_init(t_lst_elem *first, t_lst_elem *last);
t_lst_elem		*lst_create(void *content, size_t content_size);
void			lst_pushfront(t_lst_head *head, t_lst_elem *new);
void			lst_pushback(t_lst_head *head, t_lst_elem *new);

#endif
