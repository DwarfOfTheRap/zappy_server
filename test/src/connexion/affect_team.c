#include <stdlib.h>
#include <check.h>
#include "serveur.h"

void	dummy_t_zappy(t_zappy *var, t_player *p)
{
	bzero(var, sizeof(t_zappy));
	var->board_size[0] = 10;
	var->board_size[1] = 20;
	var->teams = (t_team *)malloc(sizeof(t_team) * 3);
	bzero(var->teams, sizeof(t_team) * 3);
	strcpy(var->teams[0].name, "toto");
	strcpy(var->teams[1].name, "tutu");
	strcpy(var->teams[2].name, "GRAPHIC");
	var->nb_team = 3;
	var->teams[0].remain = 1;
	var->teams[1].remain = 1;
	var->teams[2].remain = 1;
	p->snd.pos = p->snd.buf[0];
	p->status = FD_USED;
}

START_TEST(connexion_affect_team_valid)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy(&var, p);
	affect_team(&var, p, "tutu", 4);
	ck_assert_ptr_eq(&var.teams[1], p->team);
	ck_assert_int_eq(0, var.teams[1].remain);
	ck_assert_int_eq(FD_CLIENT, p->status);
	ck_assert_str_eq("1\n20 10\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_full)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy(&var, p);
	var.teams[1].remain = 0;
	affect_team(&var, p, "tutu", 4);
	ck_assert_ptr_eq(&var.teams[1], p->team);
	ck_assert_int_eq(0, var.teams[1].remain);
	ck_assert_int_eq(FD_CLOSE, p->status);
	ck_assert_str_eq("0\n20 10\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_unknow)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy(&var, p);
	affect_team(&var, p, "caca", 4);
	ck_assert_ptr_eq(NULL, p->team);
	ck_assert_int_eq(1, var.teams[1].remain);
	ck_assert_str_eq("EQUIPE INCONNUE\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_gfx)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy(&var, p);
	affect_team(&var, p, "GRAPHIC", 7);
	ck_assert_ptr_eq(&var.teams[2], p->team);
	ck_assert_int_eq(0, var.teams[2].remain);
	ck_assert_int_eq(FD_GFX, p->status);
	ck_assert_str_eq("", p->snd.buf[p->snd.write]);
	ck_assert_ptr_eq(var.gfx_client, p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_affect_team(void)
{
	TCase	*tc;

	tc = tcase_create("affect_team");
	tcase_add_test(tc, connexion_affect_team_valid);
	tcase_add_test(tc, connexion_affect_team_full);
	tcase_add_test(tc, connexion_affect_team_unknow);
	tcase_add_test(tc, connexion_affect_team_gfx);
	return (tc);
}
