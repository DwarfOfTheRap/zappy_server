#include <check.h>
#include "commands_test.h"

Suite*	suite_commands_test(void)
{
	Suite	*s;

	s = suite_create("commands");
	suite_add_tcase(s, commands_command_match());
//	suite_add_tcase(s, commands_find_command());
	return (s);
}
