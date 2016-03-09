#include <stdio.h>
#include "serveur.h"

extern int	g_log;

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, AVANCE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> avance\n", p->id);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, DROITE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> droite\n", p->id);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, GAUCHE);
	message_gfx_ppo(var, p);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> gauche\n", p->id);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, VOIR);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> voir\n", p->id);
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, INVENTAIRE);
	if (g_log & LOG_C)
		printf("[COMMAND] p %d -> inventaire\n", p->id);
}
