#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_add_msg_to_player_)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0);
	add_msg_to_player(p, "caca boudin", 0);
	add_msg_to_player(p, "crotte", 6);
	add_msg_to_player(p, "crotte de chien", 15);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "caca\ncaca boudin\ncrotte\ncrotte de chien\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_buffer_overflow)
{
	char		str[SND_SIZE + 1];
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	add_msg_to_player(p, str, SND_SIZE - 4);
	add_msg_to_player(p, "caca", 0);
	strcpy(str + SND_SIZE - 3, "\nca");
	ck_assert_int_eq(p->snd.read + 1, p->snd.write);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(p->snd.buf[p->snd.read + 1], "ca\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_all_buffer_overflow)
{
	u_int		i = 0;
	char		str[SND_SIZE + 1];
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	clean_msg_queue(p);
	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	while (i < NB_SND - 1)
	{
		add_msg_to_player(p, str, SND_SIZE - 1);
		++i;
	}
	add_msg_to_player(p, str, SND_SIZE - 4);
	add_msg_to_player(p, "caca", 0);
	while (p->snd.read < NB_SND - 1)
	{
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		++p->snd.read;
		p->snd.full = 0;
	}
	strcpy(str + SND_SIZE - 3, "\nca");
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(p->snd.lst.first->content, "ca\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_add_msg_to_player(void)
{
	TCase	*tc;

	tc = tcase_create("add_msg_to_player");
	tcase_add_test(tc, message_add_msg_to_player_);
	tcase_add_test(tc, message_add_msg_to_player_buffer_overflow);
	tcase_add_test(tc, message_add_msg_to_player_all_buffer_overflow);
	return (tc);
}
