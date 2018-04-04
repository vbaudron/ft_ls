#include "../includes/ft_ls.h"

void	put_name_colored(t_ent *ent, int endl)
{
	if (ent->type == 'd')
		ft_putstr(B_CYAN);
	else if (ent->type == 'b')
		ft_putstr(GREEN);
	else if (ent->type == 'l')
		ft_putstr(MAGENT);
	else if (ent->type == 'c')
		ft_putstr(YELLOW);
	else if (ent->type == 'p')
		ft_putstr(BLUE);
	else if (ent->type == 's')
		ft_putstr(WHITE);
	else if (ent->type == '-' && ent->rights[8] == 'x')
		ft_putstr(RED);
	if (endl == 1)
		ft_putendl(ent->name);
	else
		ft_putstr(ent->name);
	ft_putstr("\e[0m");
}
