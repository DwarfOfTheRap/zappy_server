#include <sys/time.h>
#include "serveur.h"

int				time_compare(t_tstmp time1, t_tstmp time2)
{
	if (time1.tv_sec < time2.tv_sec)
		return (1);
	else if (time1.tv_sec > time2.tv_sec)
		return (0);
	else if (time1.tv_usec < time2.tv_usec)
		return (1);
	else if (time1.tv_usec > time2.tv_usec)
		return (0);
	return (0);
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

t_tstmp			time_generate(int ref, t_tstmp start, t_zappy *var)
{
	long long	real;
	long long	new;

	real = ref * 1000000 / var->tick;
	new = time_long(start) + real;
	return (time_long_create(new));
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
