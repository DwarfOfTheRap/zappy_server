#include <stdlib.h>
#include <check.h>
#include "server.h"
#include "cleanup.h"

Suite*	cleanup(void)
{
	Suite	*s;

	s = suite_create("cleanup");
	suite_add_tcase(s, cleanup_rm_teams());
	return (s);
}
