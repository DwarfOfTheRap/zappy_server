#include "serveur.h"
#include <stdio.h>
#include <unistd.h>

t_cmd const	*get_cmd_list(void)
{
	static t_cmd const	cmd[21] = {
		{"avance", FD_CLIENT, 0, NULL},
		{"droite", FD_CLIENT, 0, NULL},
		{"gauche", FD_CLIENT, 0, NULL},
		{"voir", FD_CLIENT, 0, NULL},
		{"inventaire", FD_CLIENT, 0, NULL},
		{"prend", FD_CLIENT, 1, NULL},
		{"pose", FD_CLIENT, 1, NULL},
		{"expulse", FD_CLIENT, 0, NULL},
		{"broadcast", FD_CLIENT, 1, NULL},
		{"incantation", FD_CLIENT, 0, NULL},
		{"fork", FD_CLIENT, 0, NULL},
		{"connect_nbr", FD_CLIENT, 0, NULL},
		{"msz", FD_GFX, 0, &command_pre_msz},
		{"bct", FD_GFX, 1, &command_pre_bct},
		{"mct", FD_GFX, 0, &command_pre_mct},
		{"tna", FD_GFX, 0, &command_pre_tna},
		{"ppo", FD_GFX, 1, &command_pre_ppo},
		{"plv", FD_GFX, 1, &command_pre_plv},
		{"pin", FD_GFX, 1, &command_pre_pin},
		{"sgt", FD_GFX, 0, &command_pre_sgt},
		{"sst", FD_GFX, 1, &command_pre_sst}};

	return (cmd);
}

int			command_match(t_cmd const cmd, char *str)
{
	int		i;

	i = 0;
	while (cmd.cmd[i] && cmd.cmd[i] == str[i])
		++i;
	if ((cmd.cmd[i] == str[i] && !cmd.arg) ||
		(!cmd.cmd[i] && str[i] == ' ' && cmd.arg))
		return (i);
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
				add_msg_to_player(p, "Command format error", 0, 1);
			else if (!cmd[i].run)
				add_msg_to_player(p, "Unsupported command", 0, 1);
			else if (cmd[i].status != p->status)
				add_msg_to_player(p, "Unauthorised command", 0, 1);
			else
				cmd[i].run(var, p, str + ret);
			return ;
		}
		++i;
	}
	if (i == 21)
		add_msg_to_player(p, "Unrecognised command", 0, 1);
}
