#include <string.h>
#include "serveur.h"

int		rearrange_message_queue(t_player *p, size_t len, int buffer)
{
	char		*str;
	t_lst_head	tmp_head;
	t_lst_elem	*tmp;

	if (buffer)
	{
		str = p->snd.buf[p->snd.read];
		memmove(str, &(str[len]), SND_SIZE - len);
		if (p->snd.read == p->snd.write && !p->snd.full)
			p->snd.pos = &str[strlen(str)];
	}
	if (!p->snd.full && p->snd.lst.size)
	{
		memcpy(&tmp_head, &p->snd.lst, sizeof(t_lst_head));
		bzero(&p->snd.lst, sizeof(t_lst_head));
		while (tmp_head.size)
		{
			tmp = lst_pop(&tmp_head, 0);
			add_msg_to_player(p, tmp->content, 0, 0);
			lst_delete_elem(&tmp, free);
		}
	}
	return (1);
}

void	message_unknown_command(t_player *p)
{
	if (p->status == FD_CLIENT)
		add_msg_to_player(p, "Unrecognised command", 0, 1);
	else if (p->status == FD_GFX)
		add_msg_to_player(p, "suc", 3, 1);
}

void	message_command_format_error(t_player *p)
{
	if (p->status == FD_CLIENT)
		add_msg_to_player(p, "Command format error", 0, 1);
	else if (p->status == FD_GFX)
		add_msg_to_player(p, "sbp", 3, 1);
}

void	message_unsupported_command(t_player *p)
{
	if (p->status == FD_CLIENT)
		add_msg_to_player(p, "Unsupported command", 0, 1);
	else if (p->status == FD_GFX)
		add_msg_to_player(p, "suc", 3, 1);
}

void	message_unauthorised_command(t_player *p)
{
	if (p->status == FD_CLIENT)
		add_msg_to_player(p, "Unauthorised command", 0, 1);
	else if (p->status == FD_GFX)
		add_msg_to_player(p, "suc", 3, 1);
}
