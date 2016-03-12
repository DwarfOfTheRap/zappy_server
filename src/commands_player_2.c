#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const char	g_ressources[7][16];

void	command_prend(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args))
		++i;
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, PREND);
	message_gfx_pgt(var, p, (i < 7) ? i : 0);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> prend %s\n", p->id, args);
}

void	command_pose(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args))
		++i;
	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, POSE);
	message_gfx_pdr(var, p, (i < 7) ? i : 0);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> pose %s\n", p->id, args);
}

void	command_broadcast(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	t.str = strdup(args);
	action_add_wrapper(var, p, &t, BROADCAST);
	message_gfx_pbc(var, p, args);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> broadcast %s\n", p->id,
				args);
}

void	command_connect_nbr(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	bzero(&t, sizeof(t_aargs));
	(void)args;
	(void)var;
	action_add_wrapper(var, p, &t, CONNECT_NBR);
	if (g_log & LOG_C)
		printf("[\033[0;32mCOMMAND\033[0m] p %d -> connect_nbr\n", p->id);
}
