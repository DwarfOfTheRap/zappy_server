#include "serveur.h"

void	add_ressource(t_zappy *var, int res, int nb)
{
	int		pos[2];

	while (nb)
	{
		pos[0] = rand() % var->board_size[0];
		pos[1] = rand() % var->board_size[1];
		++var->board[pos[0]][pos[1]][res];
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
