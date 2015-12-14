#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

# include <stdlib.h>

typedef struct	s_lst_elem
{
	void					*content;
	struct s_lst_elem		*next;
	struct s_lst_elem		*prev;
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
t_lst_head		*lst_map(t_lst_head *hd, t_lst_elem *(*f)(t_lst_elem *e) \
																, size_t s);

#endif
