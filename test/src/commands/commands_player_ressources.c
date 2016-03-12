#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(command_player_voir_test)
{
	t_zappy		var;
	t_player	*p = &var.players[6];
	t_action	*action;

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	command_voir(&var, p, NULL);
	action = p->actions->first->content;
	ck_assert_ptr_eq(action->run, &action_player_voir);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_inventaire_test)
{
	t_zappy		var;
	t_player	*p = &var.players[6];
	t_action	*action;

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	command_inventaire(&var, p, NULL);
	action = p->actions->first->content;
	ck_assert_ptr_eq(action->run, &action_player_inventaire);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_prend_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_prend(&var, p, "linemate");
	action = p->actions->first->content;
	ck_assert_ptr_eq(action->run, &action_player_prend);
	clean_msg_queue(gfx);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_player_ressources_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_voir");
	tcase_add_test(tc, command_player_voir_test);
	tcase_add_test(tc, command_player_inventaire_test);
	tcase_add_test(tc, command_player_prend_test);
	return (tc);
}
