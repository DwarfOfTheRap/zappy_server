#include <check.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_read_buffer_normal)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	//char		str[10] = "toto\n";
	//char		str2[128];
	//char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	strcpy(p->rcv.buf[p->rcv.write], "prend");
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_read_buffer(void)
{
	TCase	*tc;

	tc = tcase_create("read_buffer");
	tcase_add_test(tc, connexion_read_buffer_normal);
	return (tc);
}
