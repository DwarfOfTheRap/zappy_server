#include <check.h>
#include "serveur.h"

t_cmd const	*get_cmd_list(void);
int			command_match(t_cmd const *cmd, char *str);

START_TEST(commands_command_match_valid)
{
	ck_assert_int_eq(command_match(get_cmd_list()[0], "avance"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[1], "droite"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[2], "gauche"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[3], "voir"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[4], "inventaire"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[5], "prend"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[6], "pose"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[7], "expulse"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[8], "broadcast"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[9], "incantation"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[10], "fork"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[11], "connect_nbr"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[12], "msz"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[13], "bct"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[14], "mct"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[15], "tna"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[16], "ppo"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[17], "plv"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[18], "pin"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[19], "sgt"), 0);
	ck_assert_int_eq(command_match(get_cmd_list()[20], "sst"), 0);
}
END_TEST

TCase*	commands_command_match(void)
{
	TCase	*tc;

	tc = tcase_create("init_game_var");
	tcase_add_test(tc, commands_command_match_valid);
	return (tc);
}
