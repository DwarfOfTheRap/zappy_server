#include <check.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_process_input_normal)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "toto\n";
	char		str2[128];
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	sprintf(str2, "%d\n%d %d\n", p->team->remain, var.board_size[1], var.board_size[0]);
	p->status = FD_USED;
	p->team = NULL;
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, &var.teams[0]);
	ck_assert_int_eq(p->status, FD_CLIENT);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_process_input_gfx)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "GRAPHIC\n";
	char		str2[128] = "";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	p->status = FD_USED;
	p->team = NULL;
	ret = process_input(&var, p, str);
	// this test need to be completed when we would have a proper gfx client
	// initialisation management. Though we won't be able to do advance test due
	// to random food location on map.
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, &var.teams[var.nb_team - 1]);
	ck_assert_int_eq(p->status, FD_GFX);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_process_input_unkown)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "lol\n";
	char		str2[128] = "EQUIPE INCONNUE\n";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	p->status = FD_USED;
	p->team = NULL;
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, NULL);
	ck_assert_int_eq(p->status, FD_CLOSE);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

// This test will evolve when command will be supported
START_TEST(connexion_process_input_multiple_commands)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[30] = "avance\ngauche\navance\n";
	char		str2[128] = "Unsupported command\nUnsupported command\nUnsupported command\n";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_process_input_incomplete_command)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "toto";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_str_eq(ret, str);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_process_input(void)
{
	TCase	*tc;

	tc = tcase_create("process_input");
	tcase_add_test(tc, connexion_process_input_normal);
	tcase_add_test(tc, connexion_process_input_gfx);
	tcase_add_test(tc, connexion_process_input_unkown);
	tcase_add_test(tc, connexion_process_input_multiple_commands);
	tcase_add_test(tc, connexion_process_input_incomplete_command);
	return (tc);
}
