#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_incantation_test)
{
	int			i;
	int			fd_max = 13;
	int			pl[MAX_FD];
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p;
	t_aargs		a;
	char		str[] = "niveau actuel : 2\n";
	char		gstr[] = "pie 0 0 1\nplv 6 2\nplv 7 2\nplv 8 2\nplv 9 2\n"
		"plv 10 2\nplv 11 2\nplv 12 2\nplv 13 2\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_player_gfx(&var, gfx);
	bzero(&a, sizeof(t_aargs));
	bzero(pl, sizeof(int) * MAX_FD);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		dummy_t_player(&var, p);
		p->level = 1;
		pl[i] = 1;
		++i;
	}
	a.pl = pl;
	pl[0] = 1;
	action_player_incantation(&var, p, &a);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		ck_assert_int_eq(p->level, 2);
		clean_msg_queue(p);
		++i;
	}
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	pl[0] = 0;
	action_player_incantation(&var, p, &a);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		ck_assert_int_eq(p->level, 2);
		clean_msg_queue(p);
		++i;
	}
	gstr[8] = '0';
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_life_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_life");
	tcase_add_test(tc, action_player_incantation_test);
	return (tc);
}
