#ifndef SERVEUR_H
# define SERVEUR_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
** server constants
*/
# define MAX_FD		256
# define MIN_CLIENT	1
# define MIN_PORT	1024
# define MAX_PORT	65535
# define MIN_MAP	10
# define MAX_MAP	50
# define MIN_TICK	1
# define MAX_TICK	500
# define FOOD_RATIO	100
# define RES_RATIO	100
# define TEAM_LEN	32

/*
** client status
*/
# define FD_FREE	0
# define FD_SERVER	1
# define FD_USED	2
# define FD_CLIENT	3
# define FD_GFX		4
# define FD_CLOSE	5

/*
** buffer constants
*/
# define NB_RCV		5
# define RCV_SIZE	128
# define NB_SND		20
# define SND_SIZE	1024

# include "linked_lists.h"
# include "structs.h"

/*
** src/check_arguments.c
*/
int			check_arguments(t_arguments *args, int error);

/*
** src/cleanup.c
*/
void		rm_teams(t_team **teams, int *nb_team);
void		rm_board(int ****board, int board_size[2], int i, int j);
void		cleanup_game(t_zappy *var, t_server *serv);

/*
** src/commands.c
*/
t_cmd const	*get_cmd_list(void);
int			command_match(t_cmd const cmd, char *str);
void		find_command(t_zappy *var, t_player *p, char *str, size_t len);

/*
** src/connexion.c
*/
int			close_client(t_zappy *var, t_server *serv, int fd);
void		client_error(t_player *p, char *str);
void		init_gfx(t_zappy *var, t_player *p);
void		init_client(t_zappy *var, t_player *p);
void		affect_team(t_zappy *var, t_player *p, char *str, size_t len);

/*
** src/do_accept.c
*/
void		accept_client(t_player *p, int client);
int			do_accept(t_zappy *var, t_server *serv);

/*
** src/do_read.c
*/
char		*process_input(t_zappy *var, t_player *p, char *str);
void		read_buffer(t_zappy *var, t_player *p);
int			do_read(t_zappy *var, t_server *serv, int fd);

/*
** src/do_write.c
*/
void		do_write(t_zappy *var, t_server *serv, int fd);

/*
** src/exit.c
*/
void		exit_arg_error(int error, t_arguments *args);

/*
** src/init.c
*/
int			init_board(int ****board, int board_size[2], int i, int j);
int			init_game_var(t_zappy *var, t_arguments *args);
int			init_server(t_zappy *var, t_server *serv, t_arguments *args);
int			init(t_zappy *var, t_server *serv, t_arguments *args);

/*
** src/main_loop.c
*/
void		pre_select(t_zappy *var, t_server *serv);
void		do_select(t_server *serv);
void		post_select(t_zappy *var, t_server *serv);
int			main_loop(t_zappy *var, t_server *serv);

/*
** src/message.c
*/
void		update_pos_pointer(t_snd_buf *buf);
void		add_msg_to_player_lst(t_player *p, const char *msg, size_t len,
				int cr);
void		add_msg_to_player(t_player *p, const char *msg, size_t len, int cr);
void		clean_msg_queue(t_player *p);
char		*pop_msg(t_lst_head *head);

/*
** src/message_2.c
*/
int			rearrange_message_queue(t_player *p, size_t len, int buffer);
void		message_unknown_command(t_player *p);
void		message_command_format_error(t_player *p);
void		message_unsupported_command(t_player *p);
void		message_unauthorised_command(t_player *p);

/*
** src/read_arguments.c
*/
int			z_error(char *str);
int			get_opt(const char *str);
int			get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args);
int			get_opt_int(t_main_arg const m_arg, int *i, int arg,
				t_arguments *args);
int			read_arguments(int ac, const char **av, t_arguments *args);

/*
** src/ressources_management.c
*/
void		add_ressource_on_random_square(t_zappy *var, int res);
void		add_ressource(t_zappy *var, int res, int nb);
void		init_ressources(t_zappy *var);
void		dispatch_incantation_ressources(t_zappy *var, t_player *p,
				const int *res);

/*
** src/tools
*/
char		*strjoin(char *str1, char *str2);
void		strdel(char **str);

/*
** src/usage.c
*/
void		usage(void);

/*
** src/tstmp_calcs.c
*/
int			time_compare(t_tstmp *time1, t_tstmp *time2);
t_tstmp		time_create(double seconds);
t_tstmp		time_generate(double ref, t_zappy *var);
double		time_double(t_tstmp *time);
void		time_add(t_tstmp *time1, t_tstmp *time2);

/*
** src/action_queue.c
*/
void		process_actions(t_tstmp *start, t_zappy *var);
int			action_add(t_action *action, t_zappy *var);
t_action	*action_create(char *arg, void (*f)(t_zappy*, t_player*, char*arg)
						, t_player *player, t_tstmp time);
void		action_add_wrapper(t_zappy *var, t_player *p, char *args, int act);

/*
** src/action_queue_2.c
*/
void		action_player_clear(t_player *player, t_zappy *var);
#endif
