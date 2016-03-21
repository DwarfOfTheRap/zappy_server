#include "serveur.h"

void	add_ressource_on_random_square(t_zappy *var, int res)
{
	int		pos[2];

	pos[0] = rand() % var->board_size[0];
	pos[1] = rand() % var->board_size[1];
	++var->board[pos[0]][pos[1]][res];
	message_gfx_bct(var, pos);
}

void	add_ressource(t_zappy *var, int res, int nb)
{
	while (nb)
	{
		add_ressource_on_random_square(var, res);
		--nb;
	}
}

void	init_ressources(t_zappy *var)
{
	int		nb_square;

	nb_square = var->board_size[0] * var->board_size[1];
	add_ressource(var, 0, nb_square * FOOD_RATIO / 100);
	add_ressource(var, 1, nb_square * RES_RATIO / 100 * 9 / 39);
	add_ressource(var, 2, nb_square * RES_RATIO / 100 * 8 / 39);
	add_ressource(var, 3, nb_square * RES_RATIO / 100 * 10 / 39);
	add_ressource(var, 4, nb_square * RES_RATIO / 100 * 5 / 39);
	add_ressource(var, 5, nb_square * RES_RATIO / 100 * 6 / 39);
	add_ressource(var, 6, nb_square * RES_RATIO / 100 / 39);
}

void	dispatch_incantation_ressources(t_zappy *var, t_player *p,
			const int *res)
{
	int		i;
	int		j;
	int		*square;

	i = 1;
	square = var->board[p->coord[0]][p->coord[1]];
	while (i < 7)
	{
		j = res[i];
		while (j && square[i])
		{
			--square[i];
			add_ressource_on_random_square(var, i);
			--j;
		}
		++i;
	}
}

void	drop_ressource_on_death(t_zappy *var, t_player *p)
{
	int		i;

	i = 1;
	while (i < 7)
	{
		var->board[p->coord[0]][p->coord[1]][i] += p->inv[i - 1];
		++i;
	}
	message_gfx_bct(var, p->coord);
}
