#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_gfx_multiple_)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	t_player	*gfx2 = &var.players[7];
	char		str[] = "msz 2 1\ntna toto\ntna tutu\n";
	char		str2[] = "msz 2 1\nsgt 4\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player_gfx(&var, gfx2);
	var.gfx_client[1] = gfx;
	message_gfx_msz(&var, NULL);
	message_gfx_tna(&var, gfx);
	message_gfx_sgt(&var, gfx2);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	ck_assert_str_eq(gfx2->snd.buf[gfx2->snd.read], str2);
	clean_msg_queue(gfx);
	clean_msg_queue(gfx2);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_gfx_multiple(void)
{
	TCase	*tc;

	tc = tcase_create("multiple gfx");
	tcase_add_test(tc, message_gfx_multiple_);
	return (tc);
}
