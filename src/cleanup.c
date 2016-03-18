#include <stdlib.h>
#include <unistd.h>
#include "serveur.h"

void		rm_teams(t_team **teams, int *nb_team)
{
	*nb_team = 0;
	if (!*teams)
		return ;
	free(*teams);
	*teams = NULL;
}

void		rm_board(int ****board, int board_size[2], int i, int j)
{
	if (!*board)
		return ;
	if (i == board_size[0])
		--i;
	if (j == board_size[1])
		--j;
	while (i >= 0)
	{
		while (j >= 0)
		{
			free((*board)[i][j]);
			(*board)[i][j] = NULL;
			--j;
		}
		j = board_size[1] - 1;
		free((*board)[i]);
		(*board)[i] = NULL;
		--i;
	}
	free(*board);
	*board = NULL;
}

static void	cleanup_client(t_zappy *var, int sockfd)
{
	int			i;
	t_player	*p;

	i = sockfd + 1;
	while (i < MAX_FD)
	{
		p = &var->players[i];
		if (p->status == FD_CLIENT)
			write(var->players[i].id, "mort\n", 5);
		if (p->status != FD_FREE && p->status != FD_SERVER)
			close(var->players[i].id);
		clean_msg_queue(p);
		++i;
	}
}

void		cleanup_game(t_zappy *var, t_server *serv)
{
	rm_teams(&(var->teams), &(var->nb_team));
	rm_board(&(var->board), var->board_size, var->board_size[0],
			var->board_size[1]);
	lst_delete(&var->actions, action_free);
	lst_delete(&var->eggs, free);
	lst_delete(&var->eggs_hatched, free);
	cleanup_client(var, serv->sock);
	if (serv->sock > 0)
		close(serv->sock);
}

void		action_free(void *action)
{
	t_action	*a;

	if (!action)
		return ;
	a = (t_action*)action;
	if (a->arg.str)
	{
		free(a->arg.str);
		a->arg.str = NULL;
	}
	if (a->arg.pl)
	{
		free(a->arg.pl);
		a->arg.pl = NULL;
	}
	free(action);
}
