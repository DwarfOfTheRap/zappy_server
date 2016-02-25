#include <string.h>
#include "serveur.h"

void	command_pre_bct(t_zappy *var, t_player *p, char *arg)
{
	char	*end_arg[2];
	int		pos[2];

	(void)p;
	bzero(end_arg, sizeof(void *) * 2);
	pos[1] = (int)strtol(arg, &end_arg[1], 10);
	if (end_arg[1] == arg)
		; // return wrong format command
	pos[0] = (int)strtol(end_arg[1], &end_arg[0], 10);
	if (end_arg[0] == end_arg[1])
		; // return wrong format
	if (0 >= pos[0] || pos[0] > var->board_size[0] ||
			0 >= pos[1] || pos[1] > var->board_size[1])
		; // return wrong format
}
