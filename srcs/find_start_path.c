#include "../includes/ft_ls.h"

static char	*here_path(char *path)
{
	path = malloc(sizeof(char) * 3);
	if (path == NULL)
		return (NULL);
	path[0] = '.';
	path[1] = '/';
	path[2] = '\0';
	return (path);
}

static char	*what_path(char *av, char *path)
{
	int	len;
	int	add;

	add = 0;
	len = ft_strlen(av);
	if (av[len - 1] != '/')
		add = 1;
	path = malloc(sizeof(char) * (len + 1 + add));
	if (path == NULL)
		return (NULL);
	path = ft_strcpy(path, av);
	if (add == 1)
	{
		path[len] = '/';
		path[len + add] = '\0';
	}
	return (path);
}

char		*find_start_path(int ac, char **av)
{
	int		i;
	char	*path;

	i = 1;
	path = NULL;
	while (i < ac && av[i][0] == '-')
		i++;
	if (i == ac  || ft_strcmp(av[i], ".") == 0)
		path = here_path(path);
	else
		path = what_path(av[i], path);
	return (path);
}
