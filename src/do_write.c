#include <string.h>
#include <unistd.h>
#include "serveur.h"

int		do_write_extended_buffer(t_player *p)
{
	char	*str;
	size_t	len;
	size_t	ret;

	while (p->snd.lst.size)
	{
		str = pop_msg(&p->snd.lst);
		len = strlen(str);
		ret = write(p->id, str, len);
		if (ret != len)
			return (rearrange_message_queue(p, ret, 0));
		free(str);
	}
	return (0);
}

int		do_write_normal_buffer(t_player *p)
{
	size_t	len;
	size_t	ret;

	while (p->snd.full || p->snd.read != p->snd.write ||
			p->snd.buf[p->snd.write] != p->snd.pos)
	{
		len = strlen(p->snd.buf[p->snd.read]);
		ret = write(p->id, p->snd.buf[p->snd.read], len);
		if (len != ret)
			return (rearrange_message_queue(p, ret, 1));
		p->snd.full = 0;
		if (p->snd.read == p->snd.write)
			update_pos_pointer(&p->snd);
		p->snd.read = (p->snd.read + 1 == NB_SND) ? 0 : p->snd.read + 1;
	}
	return (0);
}

void	do_write(t_zappy *var, t_server *serv, int fd)
{
	int			ret_normal_buffer;
	int			ret_extended_buffer;
	t_player	*p;

	p = &var->players[fd];
	if (!(ret_normal_buffer = do_write_normal_buffer(p)))
		ret_extended_buffer = do_write_extended_buffer(p);
	if (!ret_normal_buffer && !ret_extended_buffer && p->status == FD_CLOSE)
		close_client(var, serv, fd);
}
