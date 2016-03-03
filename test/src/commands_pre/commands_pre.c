#include <check.h>
#include "commands_pre_test.h"

Suite*	suite_commands_pre_test(void)
{
	Suite	*s;

	s = suite_create("commands_pre");
	suite_add_tcase(s, commands_pre_gfx());
	return (s);
}
