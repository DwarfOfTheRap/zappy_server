#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "serveur.h"

extern int	g_continue;

void	int_handler(int dummy)
{
	(void)dummy;
	g_continue = 0;
}

void	pre_select(t_zappy *var, t_server *serv)
{
	int		i;

	i = 3;
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

	time.tv_sec = 0;
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
				do_read(var, serv, i);
		}
		if (FD_ISSET(i, &serv->fd_write))
			do_write(var, serv, i);
		if ((FD_ISSET(i, &serv->fd_read)) || (FD_ISSET(i, &serv->fd_write)))
			serv->fd_sel--;
		i++;
	}
}

void	main_loop(t_zappy *var, t_server *serv)
{
	while (g_continue)
	{
		signal(SIGINT, int_handler);
		gettimeofday(&var->start_time, NULL);
		check_eggs(var);
		check_players_life(var);
		pre_select(var, serv);
		do_select(serv);
		post_select(var, serv);
		process_actions(var);
		check_if_team_win(var, serv);
	}
}
