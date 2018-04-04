#include "../includes/ft_ls.h"

void	free_ent(t_ent *elem)
{
	free(elem->stat);
	free(elem->rights);
	if (elem->new_rep != NULL)
		free_rep(elem->new_rep);
	free(elem->name);
	free(elem->path);
	free(elem->user);
	free(elem->group);
	if (elem->lk_name != NULL)
		free(elem->lk_name);
	free(elem->parent_path);
	free(elem->time_modif);
	free(elem->time_creation);
	free(elem->time_access);
}

void	free_rep(t_rep *rep)
{
	int		i;
	t_ent	*elem;

	i = 0;
	elem = rep->first;
	while (i < rep->nb_ent)
	{
		elem = rep->first;
		free_ent(elem);
		rep->first = elem->next;
		elem->next = NULL;
		elem->prev = NULL;
		free(elem);
		i++;
	}
	free(rep->path);
	rep->path = NULL;
	rep->first = NULL;
	rep->last = NULL;
	free(rep);
	rep = NULL;
}
