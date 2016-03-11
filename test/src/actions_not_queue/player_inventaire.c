#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_inventaire_test_1)
{

}
END_TEST

TCase*	action_player_inventaire_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_inventaire");
	tcase_add_test(tc, action_player_inventaire_test_1);
	return (tc);
}
