#include <stdlib.h>
#include <check.h>
#include "server.h"

START_TEST(arg_get_opt_p)
{
	ck_assert_int_eq(0, get_opt("-p"));
}
END_TEST

START_TEST(arg_get_opt_x)
{
	ck_assert_int_eq(1, get_opt("-x"));
}
END_TEST

START_TEST(arg_get_opt_y)
{
	ck_assert_int_eq(2, get_opt("-y"));
}
END_TEST

START_TEST(arg_get_opt_c)
{
	ck_assert_int_eq(3, get_opt("-c"));
}
END_TEST

START_TEST(arg_get_opt_t)
{
	ck_assert_int_eq(4, get_opt("-t"));
}
END_TEST

START_TEST(arg_get_opt_n)
{
	ck_assert_int_eq(5, get_opt("-n"));
}
END_TEST

TCase*	arg_get_opt(void)
{
	TCase	*get_opt;

	get_opt = tcase_create("get_opt");
	tcase_add_test(get_opt, arg_get_opt_p);
	tcase_add_test(get_opt, arg_get_opt_x);
	tcase_add_test(get_opt, arg_get_opt_y);
	tcase_add_test(get_opt, arg_get_opt_c);
	tcase_add_test(get_opt, arg_get_opt_t);
	tcase_add_test(get_opt, arg_get_opt_n);
	return (get_opt);
}
