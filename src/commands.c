#include "serveur.h"
#include <stdio.h>
#include <unistd.h>

t_cmd const	*get_cmd_list(void)
{
	static t_cmd const	cmd[21] = {
		{"avance", FD_CLIENT, 0, &command_avance},
		{"droite", FD_CLIENT, 0, &command_droite},
		{"gauche", FD_CLIENT, 0, &command_gauche},
		{"voir", FD_CLIENT, 0, &command_voir},
		{"inventaire", FD_CLIENT, 0, &command_inventaire},
		{"prend", FD_CLIENT, 1, &command_prend},
		{"pose", FD_CLIENT, 1, &command_pose},
		{"expulse", FD_CLIENT, 0, &command_expulse},
		{"broadcast", FD_CLIENT, 1, &command_broadcast},
		{"incantation", FD_CLIENT, 0, &command_incantation},
		{"fork", FD_CLIENT, 0, &command_fork},
		{"connect_nbr", FD_CLIENT, 0, &command_connect_nbr},
		{"msz", FD_GFX, 0, &command_msz},
		{"bct", FD_GFX, 1, &command_bct},
		{"mct", FD_GFX, 0, &command_mct},
		{"tna", FD_GFX, 0, &command_tna},
		{"ppo", FD_GFX, 1, &command_ppo},
		{"plv", FD_GFX, 1, &command_plv},
		{"pin", FD_GFX, 1, &command_pin},
		{"sgt", FD_GFX, 0, &command_sgt},
		{"sst", FD_GFX, 1, &command_sst}};

	return (cmd);
}

int			command_match(t_cmd const cmd, char *str)
{
	int		i;

	i = 0;
	while (cmd.cmd[i] && cmd.cmd[i] == str[i])
		++i;
	if (cmd.cmd[i] == str[i] && !cmd.arg)
		return (i);
	else if (!cmd.cmd[i] && str[i] == ' ' && cmd.arg)
		return (i + 1);
	else if (cmd.cmd[i] == str[i] && cmd.arg)
		return (-1);
	else if (!cmd.cmd[i] && str[i] == ' ' && !cmd.arg)
		return (-2);
	return (0);
}

void		find_command(t_zappy *var, t_player *p, char *str, size_t len)
{
	int				i;
	int				ret;
	t_cmd const		*cmd = get_cmd_list();

	i = 0;
	str[len] = '\0';
	while (i < 21)
	{
		if ((ret = command_match(cmd[i], str)))
		{
			if (ret < 0)
				message_command_format_error(p, str, NULL);
			else if (!cmd[i].run)
				message_unsupported_command(p, str, NULL);
			else if (cmd[i].status != p->status)
				message_unauthorised_command(p, str, NULL);
			else
				cmd[i].run(var, p, str + ret);
			return ;
		}
		++i;
	}
	if (i == 21)
		message_unknown_command(p, str);
}
