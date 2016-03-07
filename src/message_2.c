#include "serveur.h"

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
