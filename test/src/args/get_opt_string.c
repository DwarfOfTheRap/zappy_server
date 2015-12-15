#include <stdlib.h>
#include <check.h>
#include "server.h"

START_TEST(arg_get_opt_string_two_team)
{
	int					i = 0;
	t_arguments			args;
	const t_main_arg	dummy = {3, {"-n", "toto", "tutu", "-p"}};

	ck_assert_int_eq(0, get_opt_string(dummy, &i, &args));
	ck_assert_int_eq(2, args.nb_team);
}
END_TEST

TCase*	arg_get_opt_string(void)
{
	TCase	*get_opt;

	get_opt = tcase_create("get_opt_string");
	return (get_opt_string);
}
