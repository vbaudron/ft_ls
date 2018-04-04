#include "../includes/ft_ls.h"

int	to_display(t_ent *ent, t_opt *opt)
{
	if (ent->is_hide == 0)
		return (1);
	if (ent->is_hide == 1 && opt->has_a == 0)
		return (0);
	if (opt->has_a == 1 && opt->has_A == 0)
		return (1);
	if (opt->has_a == 1 && opt->has_A == 1)
	{
		if (ft_strcmp(ent->name, ".") == 0 || ft_strcmp(ent->name, "..") == 0)
			return (0);
		return (1);
	}
	return (0);
}
