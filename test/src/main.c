#include <stdlib.h>
#include <check.h>
#include "tests.h"

int		main(void)
{
	int		nb_failed;
	SRunner	*sr;

	sr = srunner_create(arg());
	srunner_add_suite(sr, cleanup());
	srunner_add_suite(sr, l_list());
	srunner_run_all(sr, CK_NORMAL);
	nb_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	if (nb_failed > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
