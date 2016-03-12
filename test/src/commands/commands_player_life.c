#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(command_player_broadcast_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		message[] = "They see me rollin', They hatin'";
	char		gstr[] = "pbc 6 They see me rollin', They hatin'\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_broadcast(&var, p, message);
	action = p->actions->first->content;
	ck_assert_ptr_eq(action->run, &action_player_broadcast);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	action_player_clear(p, &var);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_incantation_test)
{
	int			i;
	int			fd_max = 10;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p;
	char		stop_action_incant_start[] = "ko\nelevation en cours\n";
	char		incant_start[] = "elevation en cours\n";
	char		g_str[] = "ppo 9 0 1 1\nppo 9 0 0 1\npic 0 0 1 8 6 7 9 10\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 2;
	dummy_t_zappy_add_board(&var);
	var.fd_max = &fd_max;
	dummy_t_player_gfx(&var, gfx);
	i = 6;
	while (i <= fd_max)
	{
		dummy_t_player(&var, &var.players[i]);
		var.players[i].level = 1;
		++i;
	}
	command_avance(&var, &var.players[9], NULL);
	command_incantation(&var, &var.players[8], NULL);
	i = 6;
	while (i <= fd_max)
	{
		p = &var.players[i];
		if (i == 9)
			ck_assert_str_eq(p->snd.buf[p->snd.read], stop_action_incant_start);
		else
			ck_assert_str_eq(p->snd.buf[p->snd.read], incant_start);
		action_player_clear(&var.players[i], &var);
		clean_msg_queue(&var.players[i]);
		++i;
	}
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], g_str);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_player_life(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, command_player_broadcast_test);
	tcase_add_test(tc, command_player_incantation_test);
	return (tc);
}
