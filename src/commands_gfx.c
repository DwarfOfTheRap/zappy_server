#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	command_msz(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_msz(var);
	if (g_log & LOG_C)
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
	if (g_log & LOG_C)
		printf("[COMMAND] bct %s\n", arg);
}

void	command_mct(t_zappy *var, t_player *p, char *arg)
{
	t_aargs		t;
	t_action	*new;
	t_tstmp		time;

	(void)p;
	(void)arg;
	bzero(&t, sizeof(t_aargs));
	message_gfx_mct(var, &t.nb);
	if (t.nb != -1)
	{
		time = var->start_time;
		++time.tv_usec;
		new = action_create(&t, &action_gfx_mct, NULL, time);
		action_add(new, var);
	}
	if (g_log & LOG_C)
		printf("[COMMAND] mct\n");
}

void	command_tna(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_tna(var);
	if (g_log & LOG_C)
		printf("[COMMAND] tna\n");
}

void	command_sgt(t_zappy *var, t_player *p, char *arg)
{
	(void)p;
	(void)arg;
	message_gfx_sgt(var);
	if (g_log & LOG_C)
		printf("[COMMAND] sgt\n");
}
