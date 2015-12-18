#include <check.h>
#include "linked_lists.h"

t_lst_head	*new_sample_list()
{	
	t_lst_head	*head;

	head = lst_init(NULL);
	lst_pushback(head, lst_create("Bonjour", 8));
	lst_pushback(head, lst_create("Salut", 6));
	lst_pushback(head, lst_create("Ca va ?", 8));
	lst_pushback(head, lst_create("Au revoir", 10));
	return (head);
}

void	free_simple(void *simple)
{
	free(simple);
}

START_TEST(delete_elem)
{
	t_lst_elem	*elem;

	elem = NULL;
	lst_delete_elem(&elem, free_simple);
	ck_assert_ptr_eq(NULL, elem);

	elem = lst_create("Bonjour", 8);
	lst_delete_elem(&elem, free_simple);
	ck_assert_ptr_eq(NULL, elem);
}
END_TEST

START_TEST(test_remove)
{
	t_lst_head	*head;
	t_lst_elem	*removed;
	t_lst_elem	*second;
	t_lst_elem	*third;
	t_lst_elem	*last;

	head = new_sample_list();
	second = head->first->next;
	third = head->first->next->next;

	ck_assert_ptr_eq(NULL, lst_remove(NULL, NULL));
	removed = lst_remove(head, second);
	ck_assert_str_eq((char*)removed->content, "Salut");
	ck_assert_str_eq((char*)head->first->next->content, "Ca va ?");
	ck_assert_ptr_eq(third->prev, head->first);
	ck_assert_int_eq(3, head->size);
	lst_delete_elem(&removed, free_simple);

	last = head->last;
	removed = lst_remove(head, head->last);
	ck_assert_ptr_eq(removed, last);
	ck_assert_ptr_eq(head->last, third);
	ck_assert_ptr_eq(head->last->prev, head->first);
	ck_assert_ptr_eq(head->first->next, third);
	ck_assert_int_eq(2, head->size);
	lst_delete_elem(&removed, free_simple);

	removed = lst_remove(head, third);
	ck_assert_ptr_eq(removed, third);
	ck_assert_ptr_eq(head->last, head->first);
	ck_assert_ptr_eq(head->last->next, NULL);
	ck_assert_int_eq(1, head->size);
	lst_delete_elem(&removed, free_simple);

	removed = lst_remove(head, head->first);
	ck_assert_ptr_eq(head->first, NULL);
	ck_assert_ptr_eq(head->last, NULL);
	ck_assert_int_eq(0, head->size);
	lst_delete_elem(&removed, free_simple);
	free(head);
}
END_TEST

TCase*	l_list_remove(void)
{
	TCase		*l_list_remove;

	l_list_remove = tcase_create("LINKED LISTS REMOVE");
	tcase_add_test(l_list_remove, delete_elem);
	tcase_add_test(l_list_remove, test_remove);
	return (l_list_remove);
}
