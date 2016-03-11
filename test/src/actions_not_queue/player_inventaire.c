#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_inventaire_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "{nourriture 10, linemate 5, deraumere 6, sibur 7, "
					"mendiane 8, phiras 9, thystame 10}\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	action_player_inventaire(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_prend_test)
{
	int			i = 0;
	int			j = 0;
	t_aargs		a;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame"};

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_player(&var, p);
	while (i < 6)
	{
		a.str = ressources[i + 1];
		action_player_prend(&var, p, &a);
		ck_assert_str_eq(p->snd.buf[p->snd.read], "ok\n");
		clean_msg_queue(p);
		j = 0;
		while (j < 6)
		{
			ck_assert_int_eq(p->inv[j], (j <= i) ? 1 : 0);
			ck_assert_int_eq(var.board[0][0][j + 1], (j <= i) ? j + 1 : j + 2);
			++j;
		}
		++i;
	}
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_pose_test)
{
	int			i = 0;
	int			j = 0;
	t_aargs		a;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame"};

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	bzero(p->coord, sizeof(int) * 2);
	while (i < 6)
	{
		a.str = ressources[i + 1];
		action_player_pose(&var, p, &a);
		ck_assert_str_eq(p->snd.buf[p->snd.read], "ok\n");
		clean_msg_queue(p);
		j = 0;
		while (j < 6)
		{
			ck_assert_int_eq(p->inv[j], (j <= i) ? j + 4 : j + 5);
			ck_assert_int_eq(var.board[0][0][j + 1], (j <= i) ? 1 : 0);
			++j;
		}
		++i;
	}
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_ressources_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, action_player_inventaire_test);
	tcase_add_test(tc, action_player_prend_test);
	tcase_add_test(tc, action_player_pose_test);
	return (tc);
}
