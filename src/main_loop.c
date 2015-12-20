#include <stdlib.h>
#include "serveur.h"

void	pre_select(t_zappy *var, t_server *serv)
{
	int		i;

	i = 0;
	FD_ZERO(&serv->fd_read);
	FD_ZERO(&serv->fd_write);
	while (i < serv->fd_max + 1)
	{
		if (var->players[i].status != FD_FREE)
		{
			FD_SET(i, &serv->fd_read);
			if (i && var->players[i].status != FD_SERVER)
				FD_SET(i, &serv->fd_write);
		}
		i++;
	}
}

void	do_select(t_server *serv)
{
	struct timeval	time;

	time.tv_sec = 1;
	time.tv_usec = 0;
	serv->fd_sel = select(serv->fd_max + 1, &serv->fd_read,
		&serv->fd_write, NULL, &time);
}

void	post_select(t_zappy *var, t_server *serv)
{
	int		i;

	i = 0;
	while ((i <= serv->fd_max) && (serv->fd_sel))
	{
		if (FD_ISSET(i, &serv->fd_read))
		{
			if (var->players[i].status == FD_SERVER)
				do_accept(var, serv);
			else
				(void)i; //do_read(...);
		}
		if (FD_ISSET(i, &serv->fd_write))
			(void)i; //do_write(...);
		if ((FD_ISSET(i, &serv->fd_read)) || (FD_ISSET(i, &serv->fd_write)))
			serv->fd_sel--;
		i++;
	}
}

int		main_loop(t_zappy *var, t_server *serv)
{
	while (1)
	{
		pre_select(var, serv);
		do_select(serv);
		post_select(var, serv);
		// place loop throttle here
	}
}