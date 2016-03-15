#include <sys/time.h>
#include "serveur.h"

long long	time_elapsed(t_tstmp time1, t_tstmp time2)
{
	return ((time2.tv_sec - time1.tv_sec) * 1000000 \
			+ ((int)time2.tv_usec - (int)time1.tv_usec));
}
