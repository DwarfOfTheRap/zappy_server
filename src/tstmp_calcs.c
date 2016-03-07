#include <sys/time.h>
#include "serveur.h"

int				time_compare(t_tstmp *time1, t_tstmp *time2)
{
	if (!(time1 && time2))
		return (0);
	if ((long)time1->tv_sec < (long)time2->tv_sec)
		return (-1);
	else if ((long)time1->tv_sec > (long)time2->tv_sec)
		return (1);
	else if (time1->tv_usec < time2->tv_usec)
		return (-1);
	else if (time1->tv_usec > time2->tv_usec)
		return (1);
	return (0);
}

t_tstmp			time_create(double seconds)
{
	t_tstmp	result;

	result.tv_sec = seconds;
	result.tv_usec = ((seconds - (double) result.tv_sec) * 1000000000.0);
	return (result);
}

t_tstmp			time_generate(double ref, t_zappy *var)
{
	t_tstmp	real_time;
	t_tstmp new_time;

	real_time = time_create(ref / (double)var->tick);
	new_time = *(var->start_time);
	time_add(&new_time, &real_time);
	return (new_time);
}

double			time_double(t_tstmp *time)
{
	return (time->tv_sec + (time->tv_usec / 1000000000.0));
}

void			time_add(t_tstmp *time1, t_tstmp *time2)
{
	time1->tv_sec += time2->tv_sec;
	time1->tv_usec += time2->tv_usec;
	while (time1->tv_usec >= 1000000000L)
	{
		time1->tv_sec++;
		time1->tv_usec -= 1000000000L;
	}
}
