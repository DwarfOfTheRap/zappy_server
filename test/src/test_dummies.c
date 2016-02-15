#include <stdlib.h>
#include <check.h>
#include "serveur.h"

void	dummy_t_zappy_without_board(t_zappy *var)
{
	var->board = (int ***)0xdeadbeaf;
	var->board_size[0] = 1;
	var->board_size[1] = 2;
	var->team_size = 3;
	var->tick = 4;
	var->nb_team = 3;
	var->teams = (t_team *)malloc(sizeof(t_team) * 3);
	bzero(var->teams, sizeof(t_team) * 3);
	var->teams[0].name = strdup("toto");
	var->teams[0].remain = 0;
	var->teams[1].name = strdup("tutu");
	var->teams[1].remain = 0;
	var->teams[2].name = strdup("GRAPHIC");
	var->teams[2].remain = 0;
	bzero(&var->actions.size, sizeof(t_lst_head));
}

void	dummy_t_zappy_add_remaining_in_team(t_zappy *var)
{
	int	i = 0;

	while (i < var->nb_team)
	{
		++var->teams[i].remain;
		++i;
	}
}

void	dummy_t_serv(t_server *serv)
{
	serv->sock = 5;
	serv->port = 6;
	serv->fd_max = 7;
	serv->fd_sel = 8;
}

void	dummy_t_player(t_zappy *var, t_player *p)
{
	bzero(p, sizeof(t_player));
	p->status = FD_CLIENT;
	p->snd.pos = p->snd.buf[p->snd.write];
	p->snd.lst.size = 1;
	p->snd.lst.first = lst_create("caca", 5);
	p->snd.lst.last = p->snd.lst.first;
	p->team = &(var->teams[0]);
	p->rcv.remain = (char *)malloc(16);
	strcpy(p->rcv.remain, "caca");
}
