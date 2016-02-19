#include <string.h>
#include <unistd.h>
#include "serveur.h"

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
				affect_team(var, p, str + start, i - start);
			else
				find_command(var, p, str + start, i - start);
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
	p->rcv.remain = (ret && ret[0] != '\0') ? strdup(ret) : NULL;
	if (tmp)
		free(tmp);
}

int		do_read(t_zappy *var, t_server *serv, int fd)
{
	int			ret;
	t_player	*p;

	ret = RCV_SIZE;
	p = &var->players[fd];
	while (!p->rcv.full && ret == RCV_SIZE)
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
