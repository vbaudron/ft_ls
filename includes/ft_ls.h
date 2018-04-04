#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"
# include <pwd.h>
# include <grp.h>

# include <stdio.h>

# define YELLOW			"\e[33m"
# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define BLUE			"\e[34m"
# define MAGENT			"\e[35m"
# define CYAN			"\e[36m"
# define WHITE			"\e[37m"
# define BLACK			"\e[30m"

# define B_CYAN			"\e[36;1m"

typedef struct	dirent	t_dirent;

typedef struct stat		t_stat;

typedef struct passwd	t_passwd;

typedef struct			s_ent
{
	t_dirent		*dirent;
	t_stat			*stat;
//	t_passwd		*uid;
	char			*name;
	char			*parent_path;
	char			*path;
	char			type;
	char			*lk_name;
	int				is_dir;
	struct s_rep	*new_rep;
	int				is_hide;
	char			*rights;
	char			*time_modif;
	char			*time_access;
	char			*time_creation;
	char			*user;
	char			*group;
	unsigned int	nb_links;
	off_t			size; // printf(%jd)
	int				gab_size;
	int				gab_link;
	struct s_ent	*next;
	struct s_ent	*prev;
}					t_ent;

typedef struct			s_rep
{
	t_ent	*first;
	t_ent	*last;
	int		total;
	char	*path;
	int		gab_size;
	int		gab_link;
	int		nb_ent;
}						t_rep;

typedef struct			s_opt
{
	int	has_a;
	int	has_l;
	int	has_t;
	int	has_r;
	int	has_R;
	int	has_u;
	int	has_U;
	int	has_A;
	int	has_f;
}						t_opt;

void			create_option(int ac, char **av, t_opt *opt);
char			*find_start_path(int ac, char **av);
t_rep			*create_entities(char *path, t_opt *opt, int is_parent_hide);
char			*rights_in_char(mode_t mode);
t_rep			*deal_one_dir(t_opt *opt, t_rep *rep, DIR *dir, int is_p_hide);
int				print_one_rep(t_opt *opt, t_rep *rep);
int				sort_base(t_rep *rep, t_opt *opt);
int				deal_sort(t_rep *rep, t_ent *to_move, t_ent *after_it);
int				compare_time(char *s1, char *s2, t_opt *opt);
void			free_rep(t_rep *rep);
char			find_type(t_ent *ent);
void			put_name_colored(t_ent *ent, int endl);
int				to_display(t_ent *ent, t_opt *opt);
void			print_l(t_opt *opt, t_rep *rep);

#endif
