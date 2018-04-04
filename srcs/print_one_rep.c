#include "../includes/ft_ls.h"

static void	go_normal_recurs(t_opt *opt, t_rep *rep)
{
	t_ent	*elem;
	int		i;

	elem = rep->first;
	i = 0;
	while (i < rep->nb_ent)
	{
		if (elem->type == 'd' && ft_strcmp(elem->name, ".") != 0 &&
		ft_strcmp(elem->name, "..") != 0 && to_display(elem, opt) == 1)
		{
			ft_printf("\n%s:\n", elem->path);
			print_one_rep(opt, elem->new_rep);
		}
		elem = elem->next;
		i++;
	}
}

int	print_one_rep(t_opt *opt, t_rep *rep)
{
	t_ent	*elem;
	int		i;

	elem = rep->first;
	i = 0;
	if (opt->has_l == 1)
	{
		print_l(opt, rep);
		return (1);
	}
	while (i < rep->nb_ent)
	{
		if (to_display(elem, opt) == 1)
			put_name_colored(elem, 1);
		elem = elem->next;
		i++;
	}
	if (opt->has_R == 1)
		go_normal_recurs(opt, rep);
	return (1);
}
