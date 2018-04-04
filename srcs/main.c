#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	t_opt	*opt;
	char	*path;
	t_rep	*rep;

	opt = malloc(sizeof(t_opt));
	path = find_start_path(ac, av);
	if (opt == NULL)
	{
		free(path);
		path = NULL;
		return (-1);
	}
	create_option(ac, av, opt);
	rep = create_entities(path, opt, 0);
	if (rep != NULL)
	{
		print_one_rep(opt, rep);
		free_rep(rep);
	}
	free(path);
	free(opt);
	return (1);
}
