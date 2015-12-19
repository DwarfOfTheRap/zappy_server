#include <stdlib.h>
#include <check.h>
#include "server.h"

START_TEST(arg_check_arguments_valid)
{
	t_arguments		args = {1234, 20, 30, 40, 50, 2, NULL};

	args.teams = (t_team*)malloc(sizeof(t_team)*2);
	args.teams[0].name = (char *)malloc(10);
	args.teams[1].name = (char *)malloc(10);
	strcpy(args.teams[0].name, "toto");
	strcpy(args.teams[1].name, "tutu");
	ck_assert_int_eq(0, check_arguements(&args, 0));
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_uint_eq(2, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	rm_teams(&args.teams, &args.nb_team);
}
END_TEST

START_TEST(arg_check_arguments_too_much)
{
	t_arguments		args = {123411, 120, 130, 340, 550, 112, NULL};

	ck_assert_int_eq(6, check_arguements(&args, 0));
}
END_TEST

START_TEST(arg_check_arguments_too_few)
{
	t_arguments		args = {1, 2, 3, 4, 0, 0, NULL};

	ck_assert_int_eq(6, check_arguements(&args, 0));
}
END_TEST

TCase*	arg_check_arguments(void)
{
	TCase	*check_arguements;

	check_arguements = tcase_create("check_arguements");
	tcase_add_test(check_arguements, arg_check_arguments_valid);
	tcase_add_test(check_arguements, arg_check_arguments_too_much);
	tcase_add_test(check_arguements, arg_check_arguments_too_few);
	return (check_arguements);
}
