#include <check.h>
#include "test_connexion.h"

Suite*	suite_connexion(void)
{
	Suite	*s;

	s = suite_create("connexion");
	suite_add_tcase(s, connexion_test());
	return (s);
}
