#include <check.h>
#include "linked_lists.h"

START_TEST(insert)
{


}
END_TEST

TCase*	l_list_iter(void)
{
	TCase		*l_list_iter;

	l_list_iter = tcase_create("LINKED LISTS ITER");
	tcase_add_test(l_list_iter, insert);
	return (l_list_iter);
}

