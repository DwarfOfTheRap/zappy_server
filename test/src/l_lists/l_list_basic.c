#include <check.h>
#include "linked_lists.h"

START_TEST(l_list_basic_init_head)
{
	t_lst_head		*head;
	char			str1[] = "Trololo1";
	char			str2[] = "42";
	t_lst_elem		*elem1;
	t_lst_elem		*elem2;

	elem1 = lst_create(str1, strlen(str1) + 1);
	elem2 = lst_create(str2, strlen(str2) + 1);

	// check empty list
	head = lst_init(NULL);
	ck_assert_int_eq(0, head->size);
	free(head);

	// check size == 1
	head = lst_init(elem1);
	ck_assert_int_eq(1, head->size);
	free(head);

	// check size == 2
	elem1->next = elem2;
	elem2->prev = elem1;
	head = lst_init(elem1);
	ck_assert_int_eq(2, head->size);
	free(head);

	free(elem1);
	free(elem2);
}
END_TEST


TCase*		l_list_basic(void)
{
	TCase		*l_list_basic;

	l_list_basic = tcase_create("l_list_basic tests");
	tcase_add_test(l_list_basic, l_list_basic_init_head);
	return (l_list_basic);
}
