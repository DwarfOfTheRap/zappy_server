#include <stdlib.h>
#include <string.h>
#include "server.h"

int		init_board_inventory(int **row, int j_max, int *j)
{
	while (*j < j_max)
	{
		if ((row[*j] = (int *)malloc(sizeof(int) * 7)))
			bzero(row[*j], sizeof(int) * 7);
		else
			return (1);
		++(*j);
	}
	return (0);
}

int		init_board(int ****board, int board_size[2], int i, int j)
{
	while (i < board_size[0])
	{
		if (((*board)[i] = (int **)malloc(sizeof(int *) * board_size[1])))
		{
			j = 0;
			if (init_board_inventory((*board)[i], board_size[1], &j))
			{
				rm_board(board, board_size, i, j);
				return (1);
			}
		}
		else
		{
			rm_board(board, board_size, i, j);
			return (1);
		}
		++i;
	}
	return (0);
}

int		init_game_var(t_zappy *var, t_arguments *args)
{
	var->board_size[0] = args->height;
	var->board_size[1] = args->width;
	var->team_size = args->nb_clients / (int)args->nb_team;
	var->tick = args->tick;
	var->nb_team = (int)args->nb_team;
	var->teams = args->teams;
	var->actions = NULL;
	if (!(var->board = (int ***)malloc(sizeof(int **) * var->board_size[0])))
		rm_board(&(var->board), var->board_size, 0, var->board_size[1]);
	else
		init_board(&(var->board), var->board_size, 0, var->board_size[1]);
	if (!var->board)
	{
		rm_teams(&(var->teams), &(var->nb_team));
		return (1);
	}
	return (0);
}

int		init(t_zappy *var, t_arguments *args)
{
	if (init_game_var(var, args))
		return (1);
	return (0);
}
