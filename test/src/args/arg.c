#include <stdlib.h>
#include <check.h>
#include "server.h"
#include "arg.h"

Suite*	arg(void)
{
	Suite	*s;

	s = suite_create("arg");
	suite_add_tcase(s, arg_get_opt());
	suite_add_tcase(s, arg_get_opt_string());
	suite_add_tcase(s, arg_get_opt_int());
	return (s);
}
