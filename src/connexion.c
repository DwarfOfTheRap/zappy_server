#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "serveur.h"

extern		 int	g_log;
extern const char	g_log_level[7][24];

int					close_client(t_zappy *var, t_server *serv, int fd)
{
	t_player	*p;

	p = &var->players[fd];
	close(fd);
	if (p->team == &var->teams[var->nb_team - 1])
	{
		++p->team->remain;
		var->gfx_client = NULL;
	}
	else if (p->team)
		message_gfx_pdi(var, p);
	drop_ressource_on_death(var, p);
	p->status = FD_FREE;
	clean_msg_queue(p);
	if (g_log & LOG_I)
		printf("[%s] Client %d (%d) disconnected\n", g_log_level[3], fd,
				p->unique_id);
	action_player_clear(p, var);
	if (fd == serv->fd_max)
		--serv->fd_max;
	return (1);
}

void				client_error(t_player *p, char *str)
{
	add_msg_to_player(p, str, 0, 1);
	if (g_log & LOG_W)
		printf("[%s] Client %d: %s\n", g_log_level[1], p->id, str);
	p->status = FD_CLOSE;
}

void				player_hatched(t_player *p, t_zappy *var)
{
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_egg		*egg;

	list = &var->eggs_hatched;
	cursor = list->first;
	while (cursor && (egg = (t_egg*)cursor->content) && egg->team != p->team)
		cursor = cursor->next;
	if (!(cursor && egg))
	{
		p->status = FD_CLOSE;
		p->team = NULL;
		return ;
	}
	lst_remove(list, cursor);
	--p->team->egg_slot_number;
	player_spawn(p, var, egg->coord);
	message_gfx_ebo(var, egg);
	message_gfx_pnw(var, p);
	if (g_log & LOG_I)
		printf("[%s] Client %d (%d): team %s on egg %d\n", g_log_level[3],
			p->id, p->unique_id, p->team->name, egg->id);
	lst_delete_elem(&cursor, free);
}

void				init_client(t_zappy *var, t_player *p)
{
	char	str[128];
	size_t	len;

	p->status = FD_CLIENT;
	len = sprintf(str, "%d\n%d %d", p->team->remain + p->team->egg_slot_number
					, var->board_size[1], var->board_size[0]);
	if (p->team->remain)
	{
		--p->team->remain;
		player_spawn(p, var, NULL);
		message_gfx_pnw(var, p);
		if (g_log & LOG_I)
			printf("[%s] Client %d (%d): team %s\n", g_log_level[3], p->id,
					p->unique_id, p->team->name);
	}
	else if (p->team->egg_slot_number)
		player_hatched(p, var);
	else
	{
		p->status = FD_CLOSE;
		p->team = NULL;
	}
	add_msg_to_player(p, str, len, 1);
}

void				affect_team(t_zappy *var, t_player *p, char *str,
		size_t len)
{
	int		i;

	i = 0;
	while (i < var->nb_team && p->status == FD_USED)
	{
		if (!strncmp(var->teams[i].name, str, len))
		{
			p->team = &(var->teams[i]);
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
