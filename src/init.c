#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <time.h>
#include "serveur.h"
#include "linked_lists.h"

int		init_board(int ****board, int board_size[2], int i, int j)
{
	while (i < board_size[0])
	{
		j = 0;
		if (!((*board)[i] = (int **)malloc(sizeof(int *) * board_size[1])))
		{
			rm_board(board, board_size, i - 1, board_size[1]);
			return (1);
		}
		while (j < board_size[1])
		{
			if (!((*board)[i][j] = (int *)malloc(sizeof(int) * 7)))
			{
				rm_board(board, board_size, i, j - 1);
				return (1);
			}
			bzero((*board)[i][j], sizeof(int) * 7);
			++j;
		}
		++i;
	}
	return (0);
}

int		init_game_var(t_zappy *var, t_arguments *args)
{
	int		i;

	bzero(var, sizeof(t_zappy));
	var->board_size[0] = args->height;
	var->board_size[1] = args->width;
	var->team_size = (MAX_FD - 4) / (int)args->nb_team;
	var->tick = args->tick;
	var->nb_team = (int)args->nb_team;
	var->teams = args->teams;
	bzero(&var->actions, sizeof(t_lst_head));//
	if ((var->board = (int ***)malloc(sizeof(int **) * var->board_size[0])))
		init_board(&(var->board), var->board_size, 0, 0);
	if (!var->board)
	{
		rm_teams(&(var->teams), &(var->nb_team));
		return (1);
	}
	i = 0;
	while (i < var->nb_team)
		var->teams[i++].remain = args->nb_clients;
	return (0);
}

int		init_server(t_zappy *var, t_server *serv, t_arguments *args)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	bzero(serv, sizeof(t_server));
	serv->port = args->port;
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
	serv->fd_max = serv->sock;
	var->fd_max = &serv->fd_max;
	printf("Listening for maximum %d clients, on port %d\n",
		MAX_FD - serv->sock, serv->port);
	return (0);
}

int		init(t_zappy *var, t_server *serv, t_arguments *args)
{
	srand(time(NULL));
	if (init_game_var(var, args))
		return (1);
	if (init_server(var, serv, args))
	{
		cleanup_game(var, serv);
		return (1);
	}
	init_ressources(var);
	return (0);
}
