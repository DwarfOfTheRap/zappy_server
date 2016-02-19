#include <check.h>
#include <unistd.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_do_read_normal)
{
	int			pipe_fd[2];
	t_zappy		var;
	t_server	serv;
	t_player	*p;
	char		str[10] = "prend\n";

	ck_assert(pipe(pipe_fd) == 0);
	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_serv(&serv);
	p = &var.players[pipe_fd[0]];
	dummy_t_player(&var, p);
	write(pipe_fd[1], str, strlen(str));
	write(pipe_fd[1], str, strlen(str));
	write(pipe_fd[1], "pre", 3);
	ck_assert_int_eq(do_read(&var, &serv, pipe_fd[0]), 0);
	ck_assert_ptr_ne(p->rcv.remain, NULL);
	ck_assert_str_eq(p->rcv,remain. "pre");
	ck_assert_str_eq(p->snd.buf[p->snd.write], "Command format error\nCommand format error\n");
	write(pipe_fd[1], "nd\n", 3);
	ck_assert_int_eq(do_read(&var, &serv, p), 0);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.write], "Command format error\nCommand format error\nCommand format error\n");
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_do_read(void)
{
	TCase	*tc;

	tc = tcase_create("do_read");
	tcase_add_test(tc, connexion_do_read_noraml);
	return (tc);
}
