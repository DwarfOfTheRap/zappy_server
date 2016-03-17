#include <string.h>
#include "serveur.h"

static int		cmp(void *data_list, void *new_data)
{
	t_egg	*egg_list;
	t_egg	*egg_new;

	egg_list = (t_egg*)data_list;
	egg_new = (t_egg*)new_data;
	return (time_compare(egg_list->hatching_time, egg_new->hatching_time));
}

static t_egg	*get_last_egg(t_lst_head *list)
{
	t_lst_elem	*elem;

	if (!list)
		return (NULL);
	if ((elem = list->last))
		return ((elem->content) ? (t_egg*)elem->content : NULL);
	return (NULL);
}

int				egg_add(t_egg *egg, t_zappy *var)
{
	t_lst_elem	*new;
	t_egg		*last_egg;

	if ((new = lst_create_no_malloc(egg)))
	{
		last_egg = get_last_egg(&var->eggs);
		if (!last_egg || time_compare(last_egg->hatching_time, egg->hatching_time))
			lst_pushback(&var->eggs, new);
		else
			lst_insert(&var->actions, new, cmp);
		return (1);
	}
	return (0);
}

t_egg			*egg_create(t_player *p, t_zappy *var, t_tstmp *time)
{
	t_egg	*new_egg;

	if (!(new_egg = (t_egg*)malloc(sizeof(t_egg))))
		return (NULL);
	bzero(new_egg, sizeof(t_egg));
	new_egg->id = var->egg_id_index++;
	new_egg->coord[0] = p->coord[0];
	new_egg->coord[1] = p->coord[1];
	new_egg->mother = p;
	new_egg->laying_time = time[0];
	new_egg->hatching_time = time[1];
	return (new_egg);
}

void			egg_add_wrapper(t_zappy *var, t_player *p)
{
	t_egg		*new_egg;
	t_tstmp		time[2];

	time[0] = var->start_time;
	time[1] = time_generate(600, time[0], var);
	new_egg = egg_create(p, var, time);
	if (!egg_add(new_egg, var))
		free(new_egg);
}