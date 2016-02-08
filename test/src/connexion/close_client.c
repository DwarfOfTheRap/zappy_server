#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_close_client_)
{
	t_zappy		var;
	t_server	serv;
	t_player	*p = &var.players[5];

	connexion_dummy_t_zappy(&var);
	connexion_dummy_t_serv(&serv);
	connexion_dummy_t_player(&var, p);

	ck_assert_int_eq(1, close_client(&var, &serv, 5));
	ck_assert_ptr_eq((void *)0xdeadbeaf, (void *)var.board);
	ck_assert_int_eq(1, var.board_size[0]);
	ck_assert_int_eq(2, var.board_size[1]);
	ck_assert_int_eq(3, var.team_size);
	ck_assert_int_eq(4, var.tick);
	ck_assert_ptr_eq((void *)&(var.teams[0]), (void *)var.teams);
	ck_assert_int_eq(var.teams[0].remain, 0);
	ck_assert_int_eq(5, serv.sock);
	ck_assert_int_eq(6, serv.port);
	ck_assert_int_eq(7, serv.fd_max);
	ck_assert_int_eq(8, serv.fd_sel);
	ck_assert_int_eq(FD_FREE, p->status);
	ck_assert_int_eq(0, p->snd.lst.size);
	ck_assert_ptr_eq(NULL, p->snd.lst.first);
	ck_assert_ptr_eq(NULL, p->snd.lst.last);
	ck_assert_ptr_eq(NULL, p->rcv.remain);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_close_client_fd_max)
{
	t_zappy		var;
	t_server	serv;
	t_player	*p = &var.players[7];

	connexion_dummy_t_zappy(&var);
	connexion_dummy_t_serv(&serv);
	connexion_dummy_t_player(&var, p);

	ck_assert_int_eq(1, close_client(&var, &serv, 7));
	ck_assert_ptr_eq((void *)0xdeadbeaf, (void *)var.board);
	ck_assert_int_eq(1, var.board_size[0]);
	ck_assert_int_eq(2, var.board_size[1]);
	ck_assert_int_eq(3, var.team_size);
	ck_assert_int_eq(4, var.tick);
	ck_assert_ptr_eq((void *)&(var.teams[0]), (void *)var.teams);
	ck_assert_int_eq(var.teams[0].remain, 0);
	ck_assert_int_eq(5, serv.sock);
	ck_assert_int_eq(6, serv.port);
	ck_assert_int_eq(6, serv.fd_max);
	ck_assert_int_eq(8, serv.fd_sel);
	ck_assert_int_eq(FD_FREE, p->status);
	ck_assert_int_eq(0, p->snd.lst.size);
	ck_assert_ptr_eq(NULL, p->snd.lst.first);
	ck_assert_ptr_eq(NULL, p->snd.lst.last);
	ck_assert_ptr_eq(NULL, p->rcv.remain);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_close_client_gfx)
{
	t_zappy		var;
	t_server	serv;
	t_player	*p = &var.players[5];

	connexion_dummy_t_zappy(&var);
	connexion_dummy_t_serv(&serv);
	connexion_dummy_t_player(&var, p);

	p->team = &(var.teams[2]);
	p->status = FD_GFX;
	ck_assert_int_eq(1, close_client(&var, &serv, 5));
	ck_assert_ptr_eq((void *)0xdeadbeaf, (void *)var.board);
	ck_assert_int_eq(1, var.board_size[0]);
	ck_assert_int_eq(2, var.board_size[1]);
	ck_assert_int_eq(3, var.team_size);
	ck_assert_int_eq(4, var.tick);
	ck_assert_ptr_eq((void *)&(var.teams[0]), (void *)var.teams);
	ck_assert_int_eq(var.teams[2].remain, 1);
	ck_assert_int_eq(5, serv.sock);
	ck_assert_int_eq(6, serv.port);
	ck_assert_int_eq(7, serv.fd_max);
	ck_assert_int_eq(8, serv.fd_sel);
	ck_assert_int_eq(FD_FREE, p->status);
	ck_assert_int_eq(0, p->snd.lst.size);
	ck_assert_ptr_eq(NULL, p->snd.lst.first);
	ck_assert_ptr_eq(NULL, p->snd.lst.last);
	ck_assert_ptr_eq(NULL, p->rcv.remain);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_close_client(void)
{
	TCase	*tc;

	tc = tcase_create("close_client");
	tcase_add_test(tc, connexion_close_client_);
	tcase_add_test(tc, connexion_close_client_fd_max);
	tcase_add_test(tc, connexion_close_client_gfx);
	return (tc);
}
