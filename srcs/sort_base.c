#include "../includes/ft_ls.h"

static int		is_smaller_or_more_recent(t_ent *base, t_ent *tested, t_opt *opt)
{
	if (opt->has_t == 0)
	{
		if (ft_strcmp(base->name, tested->name) > 0)
		{
			if (opt->has_r == 1)
				return (0);
			return (1);
		}
		if (opt->has_r == 1)
			return (1);
		return (0);
	}
	else
	{
		if (opt->has_u == 0 && opt->has_U == 0)
			return (compare_time(base->time_modif, tested->time_modif, opt));
		else if (opt->has_u == 1)
			return (compare_time(base->time_access, tested->time_access, opt));
		else
			return (compare_time(base->time_access, tested->time_creation, opt));
	}
}

static t_ent	*find_min(t_rep *rep, t_opt * opt)
{
	t_ent *elem;
	t_ent *min;

	elem = rep->first;
	min = rep->last;
	if (elem == min)
		return (elem);
	while (elem->next != NULL)
	{
		if (is_smaller_or_more_recent(min, elem, opt) == 1)
			min = elem;
		elem = elem->next;
	}
	 return (min);
}

static t_ent	*find_max(t_rep *rep, t_opt *opt)
{
	t_ent *elem;
	t_ent *max;

	elem = rep->first;
	max = rep->last;
	if (elem == max)
		return (elem);
	while (elem->next != NULL)
	{
		if (is_smaller_or_more_recent(max, elem, opt) == 0)
			max = elem;
		elem = elem->next;
	}
	 return (max);
}

static t_ent	*find_next_min(t_rep*rep, t_ent *min, t_opt *opt)
{
	t_ent	*max;
	t_ent	*elem;

	max = rep->last;
	elem = min->next;
	while (elem->next != NULL)
	{
		if (is_smaller_or_more_recent(max, elem, opt) == 1)
			max = elem;
		elem = elem->next;
	}
	return (max);
}

int			sort_base(t_rep *rep, t_opt *opt)
{
	t_ent *min;
	t_ent *max;

	min = find_min(rep, opt);
	max = find_max(rep, opt);
	if (rep->first == rep->last)
		return (1);
	deal_sort(rep, min, NULL);
	deal_sort(rep, max, rep->last);
	if (min->next == max->prev)
		return (1);
	while (min->next != NULL)
	{
		deal_sort(rep, find_next_min(rep, min, opt), min);
		min = min->next;
	}
	return (1);
}
