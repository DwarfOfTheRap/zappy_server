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
	return (1);
}

t_tstmp			time_create(double microseconds)
{
	t_tstmp	result;

	result.tv_sec = microseconds / 1000000;
	result.tv_usec = (long long)microseconds % 1000000;
	return (result);
}

t_tstmp			time_generate(int ref, t_tstmp start, t_zappy *var)
{
	t_tstmp	real_time;
	t_tstmp new_time;

	real_time = time_create((ref / (double)var->tick) * 1000000);
	new_time = start;
	time_add(&new_time, &real_time);
	return (new_time);
}

double			time_double(t_tstmp time)
{
	return (time.tv_sec + (time.tv_usec / 1000000.0));
}

void			time_add(t_tstmp *time1, t_tstmp *time2)
{
	time1->tv_sec += time2->tv_sec;
	time1->tv_usec += time2->tv_usec;
	while (time1->tv_usec >= 1000000)
	{
		time1->tv_sec++;
		time1->tv_usec -= 1000000;
	}
}
