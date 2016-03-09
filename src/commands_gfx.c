#include <string.h>
#include <stdio.h>
#include "serveur.h"

void	command_msz(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_msz(var);
	printf("[COMMAND] msz\n");
}

void	command_bct(t_zappy *var, t_player *p, char *arg)
{
	char	*end_arg[2];
	int		pos[2];

	(void)p;
	bzero(end_arg, sizeof(void *) * 2);
	pos[1] = (int)strtol(arg, &end_arg[1], 10);
	if (end_arg[1] == arg)
		return (message_gfx_sbp(var));
	pos[0] = (int)strtol(end_arg[1], &end_arg[0], 10);
	if (end_arg[0] == end_arg[1])
		return (message_gfx_sbp(var));
	if (pos[0] < 0 || var->board_size[0] <= pos[0] ||
			pos[1] < 0 || var->board_size[1] <= pos[1])
		return (message_gfx_sbp(var));
	message_gfx_bct(var, pos);
	printf("[COMMAND] bct %s\n", arg);
}

void	command_mct(t_zappy *var, t_player *p, char *arg)
{
	t_action	*new;
	t_tstmp		time;
	long	square;

	(void)p;
	(void)arg;
	square = 0;
	message_gfx_mct(var, &square);
	if (square != -1)
	{
		time = var->start_time;
		++time.tv_usec;
		new = action_create((char *)square, &action_gfx_mct, NULL, time);
		action_add(new, var);
	}
	printf("[COMMAND] mct\n");
}

void	command_tna(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_tna(var);
	printf("[COMMAND] tna\n");
}

void	command_sgt(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_sgt(var);
	printf("[COMMAND] sgt\n");
}
