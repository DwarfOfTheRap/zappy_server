#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "serveur.h"

int		close_client(t_zappy *var, t_server *serv, int fd)
{
	t_player	*p;

	p = &var->players[fd];
	close(fd);
	p->status = FD_FREE;
	clean_msg_queue(p);
	printf("[Deconnexion] Client %d disconnected\n", fd);
	// need to clean action of this player from action queue
	if (fd == serv->fd_max)
		--serv->fd_max;
	return (1);
}

void	client_error(t_player *p, char *str)
{
	add_msg_to_player(p, str, 0);
	p->status = FD_CLOSE;
}

void	init_gfx(t_zappy *var, t_player *p)
{
	(void)var;
	p->status = FD_GFX;
	--p->team->remain;
	// need to send the map
}

void	init_client(t_zappy *var, t_player *p)
{
	char	str[128];
	size_t	len;

	p->status = FD_CLIENT;
	--p->team->remain;
	len = sprintf(str, "%d\n%d %d", p->team->remain, var->board_size[1],
			var->board_size[0]);
	add_msg_to_player(p, str, len);
}

void	affect_team(t_zappy *var, t_player *p, char *str, size_t len)
{
	int		i;

	i = 0;
	while (i < var->nb_team && p->status == FD_USED)
	{
		if (!strncmp(var->teams[i].name, str, len))
		{
			p->team = &var->teams[i];
			if (!var->teams[i].remain)
				client_error(p, "EQUIPE PLEINE");
			else if (i == var->nb_team - 1)
				init_gfx(var, p);
			else
				init_client(var, p);
		}
		++i;
	}
	if (p->status == FD_USED)
		client_error(p, "EQUIPE INCONNUE");
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
			start = i;
		}
		++i;
	}
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
		ret = (p->rcv.buf[p->rcv.write][ret - 1] == '\n') ? 1 : 0;
		p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
		if (p->rcv.read == p->rcv.write)
			p->rcv.full = 1;
	}
	if (p->rcv.full || p->rcv.read != p->rcv.write)
		read_buffer(var, p);
	return (0);
}
