#include "serveur.h"

void	command_avance(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, AVANCE);
	message_gfx_ppo(var, p);
}

void	command_droite(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, DROITE);
	message_gfx_ppo(var, p);
}

void	command_gauche(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, GAUCHE);
	message_gfx_ppo(var, p);
}

void	command_voir(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, VOIR);
}

void	command_inventaire(t_zappy *var, t_player *p, char *args)
{
	action_add_wrapper(var, p, args, INVENTAIRE);
}
