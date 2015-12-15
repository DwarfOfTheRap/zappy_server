#ifndef SERVER_H
# define SERVER_H
# include <sys/select.h>
# include <sys/types.h>
# include <sys/time.h>

/*
 * server constants
 */
# define MAX_FD		256

/*
** src/read_arguments.c
*/
int		z_error(char *str);
int		get_opt(const char *str);
int		get_opt_string(t_main_arg const m_arg, int *i, t_arguments *args);
int		get_opt_int(t_main_arg const m_arg, int *i, int arg, t_arguments *args);
int		read_arguments(int ac, const char **av, t_arguments *args);

#endif
