#include <check.h>
#include "commands_test.h"

Suite*	suite_commands_test(void)
{
	Suite	*s;

	s = suite_create("commands");
	//suite_add_tcase(s, init_init_game_var());
	//suite_add_tcase(s, init_init_server());
	return (s);
}
