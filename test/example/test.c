#include <stdlib.h>
#include <check.h>
#include <stdio.h>

START_TEST(addition)
{
	ck_assert_int_eq(2, 1 + 1);
}
END_TEST

START_TEST(subtraction)
{
	ck_assert_int_eq(0, 1 - 1);
}
END_TEST

START_TEST(hello_world)
{
	char	str[20];

	sprintf(str, "Hello %s\n", "world!");
	ck_assert_str_eq("Hello wordl!", str);
}
END_TEST

Suite*	basic(void)
{
	Suite	*s;
	TCase	*tc_basic;
	TCase	*tc_string;

	s = suite_create("basic");
	tc_basic = tcase_create("basic test case");
	tcase_add_test(tc_basic, addition);
	tcase_add_test(tc_basic, subtraction);
	suite_add_tcase(s, tc_basic);
	tc_string = tcase_create("string test case");
	suite_add_tcase(s, tc_string);
	return (s);
}

int main(int ac, const char **av)
{
	int		nb_failed;
	SRunner	*sr;

	sr = srunner_create(basic());
	srunner_run_all(sr, CK_NORMAL);
	nb_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	if (nb_failed > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
