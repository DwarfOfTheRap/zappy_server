#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_process_input_)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "toto\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	p->status = FD_USED;
	p->team = NULL;
	process_input(&var, p, str);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "");
	ck_assert_ptr_eq(p->team, &var.teams[0]);
}
END_TEST

TCase*	connexion_process_input(void)
{
	TCase	*tc;

	tc = tcase_create("process_input");
	tcase_add_test(tc, connexion_process_input_);
	return (tc);
}
