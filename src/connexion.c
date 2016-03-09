#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

int		close_client(t_zappy *var, t_server *serv, int fd)
{
	t_player	*p;

	p = &var->players[fd];
	close(fd);
	if (p->status == FD_GFX)
	{
		++p->team->remain;
		var->gfx_client = NULL;
	}
	p->status = FD_FREE;
	clean_msg_queue(p);
	if (g_log & LOG_I)
		printf("[INFO] Client %d disconnected\n", fd);
	// need to clean action of this player from action queue
	if (fd == serv->fd_max)
		--serv->fd_max;
	return (1);
}

void	client_error(t_player *p, char *str)
{
	add_msg_to_player(p, str, 0, 1);
	if (g_log & LOG_W)
		printf("[WARNING] Client %d: %s\n", p->id, str);
	p->status = FD_CLOSE;
}

void	init_client(t_zappy *var, t_player *p)
{
	char	str[128];
	size_t	len;

	p->status = FD_CLIENT;
	len = sprintf(str, "%d\n%d %d", p->team->remain, var->board_size[1],
			var->board_size[0]);
	if (p->team->remain)
	{
		--p->team->remain;
		if (g_log & LOG_I)
			printf("[INFO] Client %d: team %s\n", p->id, p->team->name);
	}
	else
		p->status = FD_CLOSE;
	add_msg_to_player(p, str, len, 1);
}

void	affect_team(t_zappy *var, t_player *p, char *str, size_t len)
{
	int		i;

	i = 0;
	while (i < var->nb_team && p->status == FD_USED)
	{
		if (!strncmp(var->teams[i].name, str, len))
		{
			p->team = &(var->teams[i]);
			//if (!var->teams[i].remain)
			//	client_error(p, "EQUIPE PLEINE");
			//else if (i == var->nb_team - 1)
			if (i == var->nb_team - 1)
				init_gfx(var, p);
			else
				init_client(var, p);
		}
		++i;
	}
	if (p->status == FD_USED)
		client_error(p, "EQUIPE INCONNUE");
}
