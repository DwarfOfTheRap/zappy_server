#include <check.h>
#include "l_list_test.h"

Suite*	l_list(void)
{
	Suite	*s;

	s = suite_create("l_list");
	suite_add_tcase(s, l_list_basic());
//	suite_add_tcase(s, l_list_add());
//	suite_add_tcase(s, l_list_remove());
	return (s);
}
