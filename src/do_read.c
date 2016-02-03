#include <string.h>
#include <unistd.h>
#include "serveur.h"

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
		{"broadcast", FD_CLIENT, 0, NULL},
		{"incantation", FD_CLIENT, 0, NULL},
		{"fork", FD_CLIENT, 0, NULL},
		{"connect_nbr", FD_CLIENT, 0, NULL},
		{"msz", FD_GFX, 0, NULL},
		{"bct", FD_GFX, 1, NULL},
		{"mct", FD_GFX, 0, NULL},
		{"tna", FD_GFX, 0, NULL},
		{"ppo", FD_GFX, 1, NULL},
		{"plv", FD_GFX, 1, NULL},
		{"pin", FD_GFX, 1, NULL},
		{"sgt", FD_GFX, 0, NULL},
		{"sst", FD_GFX, 1, NULL}};

	return (cmd);
}

int		command_match(t_cmd const *cmd, char *str)
{
	int		i;

	i = 0;
	while (cmd->cmd[i] && cmd->cmd[i] == str[i])
		++i;
	if ((cmd->cmd[i] == str[i] && !cmd->arg) ||
		(!cmd->cmd[i] && str[i] == ' ' && cmd->arg))
		return (i);
	else if (cmd->cmd[i] == str[i] && cmd->arg)
		return (-1);
	else if (!cmd->cmd[i] && str[i] == ' ' && !cmd->arg)
		return (-2);
	return (0);
}

void	find_command(t_zappy *var, t_player *p, char *str, size_t len)
{
	int				i;
	int				ret;
	t_cmd const		*cmd = get_cmd_list();

	i = 0;
	str[len] = '\0';
	while (i < 21)
	{
		if ((ret = command_match(&cmd[i], str)))
		{
			if (ret < 0)
				add_msg_to_player(p, "Command format error", 0);
			else if (!cmd[i].run)
				add_msg_to_player(p, "Unsupported command", 0);
			else if (cmd[i].status != p->status)
				add_msg_to_player(p, "Unauthorised command", 0);
			else
				cmd[i].run(var, p, str + ret);
			return ;
		}
		++i;
	}
	if (i == 21)
		add_msg_to_player(p, "Unrecognised command", 0);
}

char	*process_input(t_zappy *var, t_player *p, char *str)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (p->status == FD_USED)
				affect_team(var, p, str + start, i);
			else
				find_command(var, p, str + start, i);
			start = i + 1;
		}
		++i;
	}
	if (start != i)
		return (str + start);
	return (NULL);
}

void	read_buffer(t_zappy *var, t_player *p)
{
	char	*buf;
	char	*ret;
	char	*tmp;

	ret = p->rcv.remain;
	tmp = p->rcv.remain;
	while (p->rcv.full || p->rcv.read != p->rcv.write)
	{
		buf = (ret) ? strjoin(ret, p->rcv.buf[p->rcv.read]) :
			p->rcv.buf[p->rcv.read];
		if (tmp)
			strdel(&tmp);
		if ((ret = process_input(var, p, buf)))
			tmp = (buf == p->rcv.buf[p->rcv.read]) ? NULL : buf;
		p->rcv.full = 0;
		p->rcv.read = (p->rcv.read + 1 == NB_RCV) ? 0 : p->rcv.read + 1;
	}
	if (ret)
		p->rcv.remain = strdup(ret);
	if (tmp)
		free(tmp);
}

int		do_read(t_zappy *var, t_server *serv, int fd)
{
	int			ret;
	t_player	*p;

	ret = 1;
	p = &var->players[fd];
	while (!p->rcv.full && ret)
	{
		if ((ret = read(fd, p->rcv.buf[p->rcv.write], RCV_SIZE)) <= 0)
			return (close_client(var, serv, fd));
		p->rcv.buf[p->rcv.write][ret] = '\0';
		ret = (p->rcv.buf[p->rcv.write][ret - 1] != '\n') ? 1 : 0;
		p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
		if (p->rcv.read == p->rcv.write)
			p->rcv.full = 1;
	}
	if (p->rcv.full || p->rcv.read != p->rcv.write)
		read_buffer(var, p);
	return (0);
}
