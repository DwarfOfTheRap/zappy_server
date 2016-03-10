#include <sys/time.h>
#include "serveur.h"

t_tstmp		time_sub(t_tstmp *time1, t_tstmp *time2)
{
	double		microseconds;

	microseconds = (time2->tv_sec - time->tv_sec) * 1000000 + ((int)time2->tv_usec - (int)time->tv_usec);
	return (time_create(microseconds));
}

double		time_elapsed(t_tstmp *time1, t_tstmp *time2)
{
	return ((time2->tv_sec - time->tv_sec) * 1000000 + ((int)time2->tv_usec - (int)time->tv_usec));
}
