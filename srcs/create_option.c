#include "../includes/ft_ls.h"

static void	initialize_option(t_opt *opt)
{
	opt->has_a = 0;
	opt->has_l = 0;
	opt->has_r = 0;
	opt->has_R = 0;
	opt->has_t = 0;
	opt->has_u = 0;
	opt->has_A = 0;
	opt->has_f = 0;
	opt->has_U = 0;
}

static int	handle_two_u(char **av, t_opt *opt, int i, int u)
{
	int	U;

	U = 0;
	while (av[i][0] == '-')
	{
		if (ft_strchr(av[i], 'U') != NULL && ft_strchr(av[i], 'u') != NULL)
		{
			while (av[i][u] != 'u')
				u++;
			while (av[i][U] != 'U')
				U++;
			if (u > U)
				opt->has_U = 0;
			else
				opt->has_u = 0;
		}
		else if (ft_strchr(av[i], 'U') != NULL)
			opt->has_U = 0;
		else if (ft_strchr(av[i], 'u') != NULL)
			opt->has_u = 0;
		if (opt->has_U == 0 || opt->has_u == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	what_option(char **av, int i, t_opt *opt)
{
	if (ft_strchr(av[i], 'a') != NULL || ft_strchr(av[i], 'f') != NULL
	|| ft_strchr(av[i], 'A') != NULL)
		opt->has_a = 1;
	if (ft_strchr(av[i], 'l') != NULL)
		opt->has_l = 1;
	if (ft_strchr(av[i], 'r') != NULL)
		opt->has_r = 1;
	if (ft_strchr(av[i], 'R') != NULL)
		opt->has_R = 1;
	if (ft_strchr(av[i], 't') != NULL)
		opt->has_t = 1;
	if (ft_strchr(av[i], 'u') != NULL)
		opt->has_u = 1;
	if (ft_strchr(av[i], 'U') != NULL)
		opt->has_U = 1;
	if (ft_strchr(av[i], 'f') != NULL)
		opt->has_f = 1;
	if (ft_strchr(av[i], 'A') != NULL)
		opt->has_A = 1;
}

void		create_option(int ac, char **av, t_opt *opt)
{
	int	i;

	i = 1;
	initialize_option(opt);
	while (i < ac && av[i][0] == '-')
	{
		what_option(av, i, opt);
		i++;
	}
	if (opt->has_u == 1 && opt->has_U == 1)
		handle_two_u(av, opt, 1, 0);
}
