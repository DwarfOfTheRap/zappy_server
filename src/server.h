#ifndef SERVER_H
# define SERVER_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
 * server constants
 */
# define MAX_FD		256
# define MIN_CLIENT	6
# define MIN_PORT	1024
# define MAX_PORT	65535
# define MIN_MAP	10
# define MAX_MAP	100
# define MIN_TICK	1
# define MAX_TICK	500

# include "structs.h"

/*
** src/cleanup.c
*/
void	rm_teams(t_team **teams, u_int *nb_team);

/*
** src/check_arguements.c
*/
int		check_arguements(t_arguments *args, int error);

/*
** src/exit.c
*/
void	exit_arg_error(int error, t_arguments *args);

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
