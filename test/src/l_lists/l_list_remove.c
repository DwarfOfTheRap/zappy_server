#include <check.h>
#include "linked_lists.h"

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

TCase*	l_list_remove(void)
{
	TCase		*l_list_remove;

	l_list_remove = tcase_create("LINKED LISTS REMOVE");
	tcase_add_test(l_list_remove, delete_elem);
	return (l_list_remove);
}
