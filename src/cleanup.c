#include <stdlib.h>
#include <unistd.h>
#include "serveur.h"

void	rm_teams(t_team **teams, int *nb_team)
{
	if (!*teams)
	{
		*nb_team = 0;
		return ;
	}
	while (*nb_team > 0)
	{
		--(*nb_team);
		free(((*teams)[*nb_team]).name);
	}
	free(*teams);
	*teams = NULL;
}

void	rm_board(int ****board, int board_size[2], int i, int j)
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

void	cleanup_game(t_zappy *var, t_server *serv)
{
	rm_teams(&(var->teams), &(var->nb_team));
	rm_board(&(var->board), var->board_size, var->board_size[0],
			var->board_size[1]);
	// cleanup action lists
	if (serv->sock > 0)
		close(serv->sock);
}
