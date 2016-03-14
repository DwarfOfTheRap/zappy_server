#include <string.h>
#include <stdio.h>
#include "serveur.h"

extern int			g_log;
extern const char	g_ressources[7][16];

void	pre_action_prend(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args->str))
		++i;
	message_gfx_pgt(var, p, (i < 7) ? i : 0);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> prend %s\n", p->id,
				args->str);
}

void	pre_action_pose(t_zappy *var, t_player *p, t_aargs *args)
{
	int		i;

	i = 0;
	while (i < 7 && strcmp(g_ressources[i], args->str))
		++i;
	message_gfx_pdr(var, p, (i < 7) ? i : 0);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> pose %s\n", p->id,
				args->str);
}

void	pre_action_broadcast(t_zappy *var, t_player *p, t_aargs *args)
{
	message_gfx_pbc(var, p, args->str);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> broadcast %s\n", p->id,
				args->str);
}

void	pre_action_fork(t_zappy *var, t_player *p, t_aargs *args)
{
	(void)args;
	message_gfx_pfk(var, p);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> fork\n", p->id);
}

void	pre_action_incantation(t_zappy *var, t_player *p, t_aargs *args)
{
	if (!(args->pl = (int *)malloc(sizeof(int) * MAX_FD)))
		return (message_player_ko(p));
	args->nb = command_incantation_count_player(var, p, args->pl);
	args->pl[0] = command_incantation_can_incant(var, p, args->nb);
	command_incantation_notification(var, p, args->pl);
	message_gfx_pic(var, p, args->pl);
	if (g_log & LOG_P)
		printf("[\033[0;36mPRE-ACTION\033[0m] p %d -> incantation\n", p->id);
}
