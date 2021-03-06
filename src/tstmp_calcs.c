#include <sys/time.h>
#include "serveur.h"

int				time_compare(long long time1, long long time2)
{
	return (time1 <= time2);
}

t_tstmp			time_long_create(long long ms)
{
	t_tstmp result;

	result.tv_sec = ms / 1000000;
	result.tv_usec = ms % 1000000;
	return (result);
}

long long		time_long(t_tstmp time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

long long		time_generate(int ref, long long start, t_zappy *var)
{
	long long	real;
	long long	new;

	real = ref * 1000000 / var->tick;
	new = start + real;
	return (new);
}

void			time_add(t_tstmp *time1, t_tstmp *time2)
{
	time1->tv_sec += time2->tv_sec;
	time1->tv_usec += time2->tv_usec;
	while (time1->tv_usec >= 1000000L)
	{
		time1->tv_sec++;
		time1->tv_usec -= 1000000L;
	}
}
