#include "../includes/ft_ls.h"

static int	find_gab_size(off_t size)
{
	int	i;

	i = 0;
	while (size >= 10)
	{
		size = size / 10;
		i++;
	}
	return (i + 1);
}

static void	deal_gab(t_rep *rep)
{
	t_ent	*elem;
	char	*s;
	int		i;

	elem = rep->first;
	rep->gab_size = 0;
	rep->gab_link = 0;
	elem->gab_size = 0;
	elem->gab_link = 0;
	i = 0;
	s = NULL;
	while (i < rep->nb_ent)
	{
		elem->gab_size = find_gab_size(elem->size);
		s = ft_itoa((int)elem->nb_links);
		elem->gab_link = ft_strlen(s);
		free(s);
		s = NULL;
		if (rep->gab_size < elem->gab_size)
			rep->gab_size = elem->gab_size;
		if (rep->gab_link < elem->gab_link)
			rep->gab_link = elem->gab_link;
		elem = elem->next;
		i++;
	}
}

static void	put_time_right_format(char **time, char **s)
{
		(*s)[0] = (*time)[8];
		(*s)[1] = (*time)[9];
		(*s)[2] = ' ';
		(*s)[3] = (*time)[4] + 32;
		(*s)[4] = (*time)[5];
		(*s)[5] = (*time)[6];
		(*s)[6] = ' ';
		(*s)[7] = (*time)[11];
		(*s)[8] = (*time)[12];
		(*s)[9] = (*time)[13];
		(*s)[10] = (*time)[14];
		(*s)[11] = (*time)[15];
		(*s)[12] = '\0';
		free(*time);
		*time = NULL;
		*time = ft_strdup(*s);
		free(*s);
		*s = NULL;
}

static int	puts_hours_for_l(t_rep *rep, t_opt *opt)
{
	char	*s;
	t_ent	*elem;
	int		i;

	elem = rep->first;
	i = 0;
	while (i < rep->nb_ent)
	{
		s = malloc(sizeof(char) * 13);
		if (opt->has_u == 1)
			put_time_right_format(&(elem->time_access), &s);
		else if (opt->has_U == 1)
			put_time_right_format(&(elem->time_creation), &s);
		else
			put_time_right_format(&(elem->time_modif), &s);
		elem = elem->next;
		i++;
	}
	return (1);
}

t_rep		*create_entities(char *path, t_opt *opt, int is_parent_hide)
{
	t_rep	*rep;
	DIR		*dir;

	rep = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror("Error ");
		return (NULL);
	}
	rep = malloc(sizeof(t_rep));
	if (rep == NULL)
		perror("Error ");
	rep->path = ft_strdup(path);
	if (rep->path[ft_strlen(rep->path) - 1] != '/')
		rep->path = ft_stradd_c_end(rep->path, '/');
	rep->nb_ent = 0;
	rep->total = 0;
	rep = deal_one_dir(opt, rep, dir, is_parent_hide);
	deal_gab(rep);
	if (opt->has_l == 1)
		puts_hours_for_l(rep, opt);
	closedir(dir);
	return (rep);
}
