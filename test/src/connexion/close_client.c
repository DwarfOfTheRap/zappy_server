#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(connexion_close_client)
{
	t_zappy		var;
	t_server	serv;
	t_player	*p = &var.players[7];

	var.board = (int ***)0xdeadbeaf;
	var.board_size[0] = 1;
	var.board_size[1] = 2;
	var.team_size = 3;
	var.tick = 4;
	var.teams = (t_team *)0xd1ceca5e;
	bzero(&var.actions.size, sizeof(t_lst_head));
	serv.sock = 5;
	serv.port = 6;
	serv.fd_max = 7;
	serv.fd_sel = 8;
	p->status = FD_CLIENT;
	p->snd.lst.size = 1;
	p->snd.lst.first = lst_create("caca", 4);
	p->snd.lst.last = p->snd.lst.first;
	p->rcv.remain = (char *)malloc(16);
	strcpy(p->rcv.remain, "caca");
	ck_assert_int_eq(1, close_client(&var, &serv, 7));
	ck_assert_ptr_eq((void *)0xdeadbeaf, (void *)var.board);
	ck_assert_int_eq(1, var.board_size[0]);
	ck_assert_int_eq(2, var.board_size[1]);
	ck_assert_int_eq(3, var.team_size);
	ck_assert_int_eq(4, var.tick);
	ck_assert_ptr_eq((void *)0xd1ceca5e, (void *)var.teams);
	ck_assert_int_eq(5, serv.sock);
	ck_assert_int_eq(6, serv.port);
	ck_assert_int_eq(6, serv.fd_max);
	ck_assert_int_eq(8, serv.fd_sel);
	ck_assert_int_eq(FD_FREE, p->status);
	ck_assert_int_eq(0, p->snd.lst.size);
	ck_assert_ptr_eq(NULL, p->snd.lst.first);
	ck_assert_ptr_eq(NULL, p->snd.lst.last);
	ck_assert_ptr_eq(NULL, p->rcv.remain);
}
END_TEST

TCase*	connexion_test(void)
{
	TCase	*tc;

	tc = tcase_create("close_client");
	tcase_add_test(tc, connexion_close_client);
	return (tc);
}
