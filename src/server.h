#ifndef SERVER_H
# define SERVER_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
 * server constants
 */
# define MAX_FD		256

typedef struct timeval	t_tstmp;

typedef struct			s_list
{
	void		*content;
}						t_list;

typedef struct			s_msg
{
	char		*content;
}						t_msg;

typedef struct			s_server
{
	int			port;
	int			fd_max;
	int			fd_sel;
	fd_set		fd_read;
	fd_set		fd_write;
}						t_server;

typedef struct			s_team
{
	char		*name;
	int			remain;
}						t_team;

typedef struct			s_player
{
	int			id;
	int			inv[6];
	int			coord[2];
	int			fov;
	int			pending_actions;
	t_team		*team;
	t_tstmp		timeofdeath;
	u_char		facing:2;
	u_char		status:2;
	u_char		level:4;
	t_list		*msg;
}						t_player;

typedef struct			s_action
{
	char		*arg;
	char		*(*run)(t_player *);
	t_player	*player;
	t_tstmp		time;
}						t_action;

typedef struct			s_zappy
{
	int			***board;
	int			board_size[2];
	int			team_size;
	int			tick;
	t_team		*teams;
	t_list		*actions;
	t_player	players[MAX_FD];
}						t_zappy;

typedef struct			s_arguments
{
	int		port;
	int		width;
	int		height;
	int		nb_clients;
	int		tick;
	t_team	*teams;
}						t_arguments;

typedef struct			s_main_arg
{
	int			ac;
	const char	**av;
}						t_main_arg;

# include "headers.h"

#endif
