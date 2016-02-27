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
	size_t	i = 3;

	while (i < MAX_FD && &var->players[i] != p)
		++i;
	bzero(p, sizeof(t_player));
	p->status = FD_CLIENT;
	p->snd.pos = p->snd.buf[p->snd.write];
	p->team = &(var->teams[0]);
	p->id = i;
}

void	dummy_t_player_gfx(t_zappy *var, t_player *p)
{
	dummy_t_player(var, p);
	var->gfx_client = p;
	p->status = FD_GFX;
}

void	dummy_t_player_fill_buffer(t_player *p)
{
	p->snd.lst.first = lst_create("caca", 5);
	p->snd.lst.last = p->snd.lst.first;
	p->rcv.remain = (char *)malloc(16);
	p->snd.lst.size = 1;
	strcpy(p->rcv.remain, "caca");
}

void	dummy_t_player_default(t_player *p)
{
	p->level = 1;
	p->facing = 2;
	p->coord[0] = 3;
	p->coord[1] = 4;
	p->inv[0] = 5;
	p->inv[1] = 6;
	p->inv[2] = 7;
	p->inv[3] = 8;
	p->inv[4] = 9;
	p->inv[5] = 10;
	p->inv[6] = 11;
}
