#ifndef SERVEUR_H
# define SERVEUR_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
** server constants
*/
# define MAX_FD		256
# define MIN_CLIENT	6
# define MIN_PORT	1024
# define MAX_PORT	65535
# define MIN_MAP	10
# define MAX_MAP	50
# define MIN_TICK	1
# define MAX_TICK	500

/*
** client status
*/
# define FD_FREE	0
# define FD_SERVER	1
# define FD_CLIENT	2
# define FD_GFX		3

# include "structs.h"

/*
** src/check_arguments.c
*/
int		check_arguments(t_arguments *args, int error);

/*
** src/cleanup.c
*/
void	rm_teams(t_team **teams, int *nb_team);
void	rm_board(int ****board, int board_size[2], int i, int j);
void	cleanup_game(t_zappy *var, t_server *serv);

/*
** src/do_accept.c
*/
void	init_client(t_zappy *var, int client);
int		do_accept(t_zappy *var, t_server *serv);

/*
** src/exit.c
*/
void	exit_arg_error(int error, t_arguments *args);

/*
** src/init.c
*/
int		init_board(int ****board, int board_size[2], int i, int j);
int		init_game_var(t_zappy *var, t_arguments *args);
int		init_server(t_zappy *var, t_server *serv, t_arguments *args);
int		init(t_zappy *var, t_server *serv, t_arguments *args);

/*
** src/main_loop.c
*/
void	pre_select(t_zappy *var, t_server *serv);
void	do_select(t_server *serv);
void	post_select(t_zappy *var, t_server *serv);
int		main_loop(t_zappy *var, t_server *serv);

/*
** src/read_arguments.c
*/
int		z_error(char *str);
int		get_opt(const char *str);
int		get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args);
int		get_opt_int(t_main_arg const m_arg, int *i, int arg, t_arguments *args);
int		read_arguments(int ac, const char **av, t_arguments *args);

/*
** src/usage.c
*/
void	usage(void);

#endif
