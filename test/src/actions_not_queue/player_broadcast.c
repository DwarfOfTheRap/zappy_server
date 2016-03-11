#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_broadcast_test_1)
{
	int			i = 1;
	int			fd_max = 13;
	t_aargs		a;
	t_zappy		var;
	t_player	*p0 = &var.players[5];
	t_player	*p1 = &var.players[6];
	t_player	*p2 = &var.players[7];
	t_player	*p3 = &var.players[8];
	t_player	*p4 = &var.players[9];
	t_player	*p5 = &var.players[10];
	t_player	*p6 = &var.players[11];
	t_player	*p7 = &var.players[12];
	t_player	*p8 = &var.players[13];
	t_player	*p;
	char		broadcast[] = "LEERROOYYYY JJEEENNNKKIINNSSSSS";
	char		ret[] = "message 1,LEERROOYYYY JJEEENNNKKIINNSSSSS\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	var.fd_max = &fd_max;
	dummy_t_player(&var, p0);
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	dummy_t_player(&var, p3);
	dummy_t_player(&var, p4);
	dummy_t_player(&var, p5);
	dummy_t_player(&var, p6);
	dummy_t_player(&var, p7);
	dummy_t_player(&var, p8);
	a.str = broadcast;
	/*
	p0 {2, 2}
	p1 {0, 1} -> 1
	p2 {9, 5} -> 2
	p3 {2, 7} -> 3
	p4 {4, 4} -> 4
	p5 {0, 6} -> 5
	p6 {5, 9} -> 6
	p7 {3, 9} -> 7
	p8 {9, 9} -> 8
	*/
	p0->coord[0] = 2;
	p0->coord[1] = 2;

	p1->coord[1] = 1;

	p2->coord[0] = 9;
	p2->coord[1] = 5;

	p3->coord[0] = 2;
	p3->coord[1] = 7;

	p4->coord[0] = 4;
	p4->coord[1] = 4;

	p5->coord[0] = 6;

	p6->coord[0] = 5;
	p6->coord[1] = 9;

	p7->coord[0] = 3;
	p7->coord[1] = 9;

	p8->coord[0] = 9;
	p8->coord[1] = 9;
	action_player_broadcast(&var, p0, &a);
	while (i < 9)
	{
		p = &var.players[i + 5];
		printf("=== p %d {%d, %d} ===\n", i, p->coord[0], p->coord[1]);
		ret[8] = i + '0';
		ck_assert_str_eq(p->snd.buf[p->snd.read], ret);
		++i;
	}
}
END_TEST

TCase*	action_player_broadcast_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, action_player_broadcast_test_1);
	return (tc);
}

/*
 * 9|     2   8
 * 8|
 * 7|
 * 6|5
 * 5|         6
 * 4|    4
 * 3|         7
 * 2|  0    3
 * 1|
 * 0| 1
 *  +----------
 *   0123456789
*/
