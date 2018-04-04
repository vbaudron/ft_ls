#include "../includes/ft_ls.h"

static void	print_it_2(t_ent *elem, t_rep *rep, t_opt *opt)
{
	int size_rest;

	size_rest = rep->gab_size - elem->gab_size;
	ft_putchar(' ');
	ft_putchar(' ');
	while (size_rest-- > 0)
		ft_putchar (' ');
	ft_printf("%jd ", elem->size);
	if (opt->has_u == 1)
		ft_printf("%s ", elem->time_access);
	else if (opt->has_U == 1)
		ft_printf("%s ", elem->time_creation);
	else
		ft_printf("%s ", elem->time_modif);
	put_name_colored(elem, 0);
	if (elem->type == 'l')
		ft_printf(" --> %s", elem->lk_name);
	ft_putchar('\n');
}

static void	print_it(t_ent *elem, t_rep *rep, t_opt *opt, int *is_first)
{
	int links_rest;

	links_rest = rep->gab_link - elem->gab_link;
	if (*is_first == 0)
	{
		ft_printf("total %d\n", rep->total);
		*is_first = 1;
	}
	ft_putchar(elem->type);
	ft_putstr(elem->rights);
	ft_putchar(' ');
	ft_putchar(' ');
	while (links_rest-- > 0)
		ft_putchar(' ');
	ft_putnbr((int)elem->nb_links);
	ft_putchar(' ');
	ft_putstr(elem->user);
	ft_putchar(' ');
	ft_putchar(' ');
	ft_putstr(elem->group);
	print_it_2(elem, rep, opt);
}

static void	go_recurs(t_opt *opt, t_rep *rep)
{
	t_ent	*elem;
	int		i;

	elem = rep->first;
	i = 0;
	while (i < rep->nb_ent)
	{
		if (elem->type == 'd' && to_display(elem, opt) == 1 && ft_strcmp(elem->name, ".") != 0 && ft_strcmp(elem->name, "..") != 0)
		{
			ft_printf("\n%s:\n", elem->path);
			print_l(opt, elem->new_rep);
		}
		elem = elem->next;
		i++;
	}
}

void		print_l(t_opt *opt, t_rep *rep)
{
	t_ent	*elem;
	int		i;
	int		is_first;

	elem = rep->first;
	i = 0;
	is_first = 0;
	while (i < rep->nb_ent)
	{
		if (to_display(elem, opt) == 1)
			print_it(elem, rep, opt, &is_first);
		elem = elem->next;
		i++;
	}
	if (opt->has_R == 1)
		go_recurs(opt, rep);
}
