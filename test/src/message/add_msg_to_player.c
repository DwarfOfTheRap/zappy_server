#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_add_msg_to_plater_)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0);
	add_msg_to_player(p, "caca boudin", 0);
	add_msg_to_player(p, "crotte", 6);
	add_msg_to_player(p, "crotte de chien", 15);
	ck_assert_str_eq(p->snd.buf[p->snd.write], "caca\ncaca boudin\ncrotte\ncrotte de chien\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_add_msg_to_plater(void)
{
	TCase	*tc;

	tc = tcase_create("add_msg_to_player");
	tcase_add_test(tc, message_add_msg_to_plater_);
	return (tc);
}
