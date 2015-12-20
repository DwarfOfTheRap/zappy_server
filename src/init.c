#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include "serveur.h"

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
				rm_board(board, board_size, i, j - 1);
				return (1);
			}
		}
		else
		{
			rm_board(board, board_size, i - 1, board_size[1]);
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
	if ((var->board = (int ***)malloc(sizeof(int **) * var->board_size[0])))
		init_board(&(var->board), var->board_size, 0, 0);
	if (!var->board)
	{
		rm_teams(&(var->teams), &(var->nb_team));
		return (1);
	}
	return (0);
}

int		init_server(t_zappy *var, t_server *serv, t_arguments *args)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	bzero(serv, sizeof(t_server));
	serv->port = args->port;
	serv->fd_max = 4;
	if (!(proto = getprotobyname("tcp")))
		return (z_error("tcp: Unsupported protocol\n"));
	serv->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(serv->port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serv->sock, (const struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		dprintf(2, "Bind error on port %d\n", serv->port);
		return (1);
	}
	listen(serv->sock, MAX_FD);
	var->players[serv->sock].status = FD_SERVER;
	printf("Listening for maximum %d clients, on port %d\n",
		MAX_FD - serv->sock, serv->port);
	return (0);
}

int		init(t_zappy *var, t_server *serv, t_arguments *args)
{
	if (init_game_var(var, args))
		return (1);
	if (init_server(var, serv, args))
	{
		cleanup_game(var, serv);
		return (1);
	}
	return (0);
}
