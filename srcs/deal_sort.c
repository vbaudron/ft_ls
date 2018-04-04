#include "../includes/ft_ls.h"

static int	mv_first_place(t_rep *rep, t_ent *to_move)
{
	if (to_move == rep->first)
		return (1);
	if (to_move == rep->last)
	{
		rep->last = to_move->prev;
		rep->last->next = NULL;
		to_move->next = rep->first;
		rep->first->prev = to_move;
		to_move->prev = NULL;
		rep->first = to_move;
	}
	else
	{
		to_move->prev->next = to_move->next;
		to_move->next->prev = to_move->prev;
		to_move->prev = NULL;
		to_move->next = rep->first;
		rep->first->prev = to_move;
		rep->first = to_move;
	}
	return (1);
}

static int	mv_last_place(t_rep *rep, t_ent *to_move)
{
	if (to_move == rep->last)
		return (1);
	if (to_move == rep->first)
	{
		rep->last->next = to_move;
		to_move->prev = rep->last;
		rep->first = to_move->next;
		rep->first->prev = NULL;
		to_move->next = NULL;
		rep->last = to_move;
	}
	else
	{
		to_move->prev->next = to_move->next;
		to_move->next->prev = to_move->prev;
		to_move->prev = rep->last->prev;
		rep->last->next = to_move;
		to_move->next = NULL;
		rep->last = to_move;
	}
	return (1);
}

static int	mv_in_the_middle(t_ent *to_move, t_ent *after_it)
{
	if (to_move == after_it->next)
		return (1);
	if (to_move->next == NULL)
		to_move->prev->next = NULL;
	else
	{
		to_move->next->prev = to_move->prev;
		to_move->prev->next = to_move->next;
	}
	to_move->next = after_it->next;
	after_it->next->prev = to_move;
	after_it->next = to_move;
	to_move->prev = after_it;
	return (1);
}

static int	mv_only_two(t_rep *rep, t_ent *to_move, t_ent *after_it)
{
	if (after_it == NULL && to_move == rep->last)
	{
		to_move->next = rep->first;
		to_move->prev = NULL;
		rep->first->next = NULL;
		rep->first->prev = to_move;
		rep->last = rep->first;
		rep->first = to_move;
	}
	else if (after_it == rep->last && to_move == rep->first)
	{
		to_move->next = NULL;
		to_move->prev = rep->last;
		rep->last->prev = NULL;
		rep->last->next = to_move;
		rep->first = rep->last;
		rep->last = to_move;
	}
	return (1);
}

int			deal_sort(t_rep *rep, t_ent *to_move, t_ent *after_it)
{
	if (rep->first->next == rep->last)
		mv_only_two(rep, to_move, after_it);
	else if (after_it == NULL)
		mv_first_place(rep, to_move);
	else if (after_it == rep->last)
		mv_last_place(rep, to_move);
	else
		mv_in_the_middle(to_move, after_it);
	return (1);
}
