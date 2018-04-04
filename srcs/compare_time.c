#include "../includes/ft_ls.h"

static int	compare_year(char *s1, char *s2, int len)
{
	int i;
	i = len - 5;
	while (i < len)
	{
		if (s1[i] < s2[i])
			return (0);
		else if (s1[i] > s2[i])
			return (1);
		i++;
	}
	return (-1);
}

static int	find_month(char *s)
{
	if (s[4] == 'J' && s[5] != 'u')
		return (1);
	else if (s[4] == 'J' && s[5] == 'u' && s[6] == 'i')
		return (6);
	else if (s[4] == 'J' && s[5] == 'u' && s[6] == 'l')
		return (7);
	else if (s[4] == 'F')
		return (2);
	else if (s[4] == 'M' && s[6] == 'r')
		return (3);
	else if (s[4] == 'A' && s[5] == 'v')
		return (2);
	else if (s[4] == 'M')
		return (5);
	else if (s[4] == 'A')
		return (8);
	else if (s[4] == 'S')
		return (9);
	else if (s[4] == 'O')
		return (10);
	else if (s[4] == 'N')
		return (11);
	else
		return (12);
}

static int	compare_month(char *s1, char *s2)
{
	int nb;

	nb = find_month(s1) - find_month(s2);
	if (nb > 0)
		return (0);
	else if (nb < 0)
		return (1);
	return (-1);
}

static int	compare_days(char *s1, char *s2)
{
	if (s1[8] == s2[8])
	{
		if (s1[9] == s2[9])
			return (-1);
		else if (s1[9] > s2[9])
			return (0);
		else
			return (1);
	}
	else if (s1[8] > s2[8])
		return (0);
	else
		return (1);
}

static int	compare_hours(char *s1, char *s2)
{
	int i;

	i = 11;
	while (s1[i] != ' ')
	{
		if (s1[i] > s2[i])
			return (0);
		else if (s1[i] < s2[i])
			return (1);
		i++;
	}
	return (-1);
}

int			compare_time(char *s1, char *s2, t_opt *opt)
{
	int ret;

	ret = 0;
	if ((ret = compare_year(s1, s2, ft_strlen(s1))) == -1)
	{
		if ((ret = compare_month(s1, s2)) == -1)
		{
			if ((ret = compare_days(s1, s2)) == -1)
			{
				ret = compare_hours(s1, s2);
			}
		}
	}
	if (opt->has_r == 1)
	{
		if (ret == 1)
			return (0);
		return (1);
	}
	return (ret);
}
