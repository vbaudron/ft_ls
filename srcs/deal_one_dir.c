#include "../includes/ft_ls.h"

static t_ent	*deal_link(t_ent *ent)
{
	if (ent->type == 'l')
	{
		ent->lk_name = ft_strnew(1024);
		readlink(ent->path, ent->lk_name, 1024);
	}
	else
		ent->lk_name = NULL;
	return (ent);
}

static t_ent	*malloc_fullfill(t_ent *ent, t_dirent *dirent, char *path, int is_p_hide)
{
	ent = malloc(sizeof(t_ent));
	if (ent == NULL)
		return (NULL);
	ent->dirent = dirent;
	ent->stat = malloc(sizeof(t_stat));
	ent->name = ft_strdup(ent->dirent->d_name);
	ent->path = ft_strjoin(path, ent->name);
	lstat(ent->path, ent->stat);
	ent->type = find_type(ent);
	deal_link(ent);
	ent->user = ft_strdup(getpwuid(ent->stat->st_uid)->pw_name);
	ent->group = ft_strdup(getgrgid(ent->stat->st_gid)->gr_name);
	if (ent->name[0] == '.' || is_p_hide == 1)
		ent->is_hide = 1;
	else
		ent->is_hide = 0;
	ent->parent_path = ft_strdup(path);
	ent->time_modif = ft_strdup(ctime(&ent->stat->st_mtime));
	ent->time_access = ft_strdup(ctime(&ent->stat->st_atime));
	ent->time_creation = ft_strdup(ctime(&ent->stat->st_birthtime));
	ent->size = ent->stat->st_size;
	ent->rights = rights_in_char(ent->stat->st_mode);
	return (ent);
}

static t_ent	*link_it(int *is_first, t_rep *rep, t_ent *ent)
{
	if (*is_first == 0)
	{
		*is_first = 1;
		rep->first = ent;
		ent->prev = NULL;
	}
	else
	{
		rep->last->next = ent;
		ent->prev = rep->last;
	}
	rep->last = ent;
	ent->next = NULL;
	return (ent);
}

t_rep			*go_or_nogo_recur(t_ent *ent, t_opt *opt)
{
	if (ent->type == 'd' && opt->has_R == 1 && ft_strcmp(ent->name, ".") != 0
	&& ft_strcmp(ent->name, "..") != 0)
		return (create_entities(ent->path, opt, ent->is_hide));
	else
		return (NULL);
}

t_rep			*deal_one_dir(t_opt *opt, t_rep *rep, DIR *dir, int is_p_hide)
{
	t_ent		*ent;
	t_dirent	*dirent;
	t_ent		*prev;
	int			is_first;

	ent = NULL;
	dirent = NULL;
	prev = NULL;
	rep->first = NULL;
	is_first = 0;
	while ((dirent = readdir(dir)) != NULL)
	{
		rep->nb_ent++;
		ent = malloc_fullfill(ent, dirent, rep->path, is_p_hide);
		if (ent == NULL)
			perror("Error ");
		ent->nb_links = (unsigned int)(ent->stat->st_nlink);
		ent = link_it(&is_first, rep, ent);
		ent->new_rep = go_or_nogo_recur(ent, opt);
		rep->total += ent->stat->st_blocks;
		ent = ent->next;
	}
	if (opt->has_f == 0)
		sort_base(rep, opt);
	return (rep);
}
