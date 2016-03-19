#include <string.h>
#include "serveur.h"

extern int	g_log;

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "avance");
	bzero(&t, sizeof(t_aargs));
	if (!p->pending_actions)
		pre_action_avance(var, p, NULL);
	action_add_wrapper(var, p, &t, AVANCE);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "droite");
	bzero(&t, sizeof(t_aargs));
	if (!p->pending_actions)
		pre_action_droite(var, p, NULL);
	action_add_wrapper(var, p, &t, DROITE);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "gauhe");
	bzero(&t, sizeof(t_aargs));
	if (!p->pending_actions)
		pre_action_gauche(var, p, NULL);
	action_add_wrapper(var, p, &t, GAUCHE);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "voir");
	bzero(&t, sizeof(t_aargs));
	action_add_wrapper(var, p, &t, VOIR);
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	t_aargs		t;

	(void)args;
	if (g_log & LOG_C)
		log_simple_message(p, LOG_C, "inventaire");
	bzero(&t, sizeof(t_aargs));
	if (!p->pending_actions)
		pre_action_inventaire(var, p, NULL);
	action_add_wrapper(var, p, &t, INVENTAIRE);
}
